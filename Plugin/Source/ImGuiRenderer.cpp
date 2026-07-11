// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2021-2026 by Agustin L. Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "ImGuiRenderer.hpp"
#include <Zyphryon.Math/Matrix4x4.hpp>
#include <Zyphryon.Content/Service.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Plugin
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::Initialize(Ref<Engine::Subsystem::Host> Host)
    {
        ConstRetainer<Content::Service> Content = Host.GetService<Content::Service>();
        mTechnique = Content->Load<Graphic::Technique>("Engine://Technique/Basic/Basic2D.vfx");
        mGraphics = Host.GetService<Graphic::Service>();

        // Set maximum texture size limits for the renderer backend.
        Ref<ImGuiPlatformIO> PlatformIO = ImGui::GetPlatformIO();
        PlatformIO.Renderer_TextureMaxWidth  = mGraphics->GetDescription().Capabilities.MaxTextureDimension;
        PlatformIO.Renderer_TextureMaxHeight = PlatformIO.Renderer_TextureMaxWidth;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::Dispose()
    {
        for (const Ptr<ImTextureData> Texture : ImGui::GetPlatformIO().Textures)
        {
            if (Texture->RefCount == 1)
            {
                DeleteTexture(Texture);
            }
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::Submit(ConstRef<ImDrawData> Commands)
    {
        // Abort drawing if the technique has not finished loading or compiling.
        if (!mTechnique->HasCompleted())
        {
            return;
        }

        // Handle all pending texture operations.
        if (Commands.Textures != nullptr)
        {
            for (const Ptr<ImTextureData> Texture : * Commands.Textures)
            {
                switch (Texture->Status)
                {
                case ImTextureStatus_WantCreate:
                    CreateTexture(Texture);
                    break;
                case ImTextureStatus_WantUpdates:
                    UpdateTexture(Texture);
                    break;
                case ImTextureStatus_WantDestroy:
                    DeleteTexture(Texture);
                    break;
                default:
                    break;
                }
            }
        }

        Graphic::Slice<ImDrawVert> VtxSlice = mGraphics->AllocateTransientVertices<ImDrawVert>(Commands.TotalVtxCount);
        Graphic::Slice<ImDrawIdx>  IdxSlice = mGraphics->AllocateTransientIndices<ImDrawIdx>(Commands.TotalIdxCount);

        Graphic::Slice<Matrix4x4> UboSlice = mGraphics->AllocateTransientUniforms<Matrix4x4>(1);
        UboSlice[0] = Matrix4x4::CreateOrthographic(
                Commands.DisplayPos.x,
                Commands.DisplayPos.x + Commands.DisplaySize.x,
                Commands.DisplayPos.y + Commands.DisplaySize.y,
                Commands.DisplayPos.y,
                -1.0f,
                +1.0f);

        UInt32 VtxOffset = 0;
        UInt32 IdxOffset = 0;

        for (const ConstPtr<ImDrawList> CommandList : Commands.CmdLists)
        {
            VtxSlice.Copy(ConstSpan(CommandList->VtxBuffer.Data, CommandList->VtxBuffer.Size), VtxOffset);
            IdxSlice.Copy(ConstSpan(CommandList->IdxBuffer.Data, CommandList->IdxBuffer.Size), IdxOffset);

            Span<Graphic::Command> GfxCommands = mGraphics->AllocateTransientCommands(CommandList->CmdBuffer.Size);

            for (SInt32 Element = 0; Element < CommandList->CmdBuffer.Size; ++Element)
            {
                ConstRef<ImDrawCmd> Command = CommandList->CmdBuffer[Element];

                if (Command.UserCallback)
                {
                    Command.UserCallback(CommandList, AddressOf(Command));
                }
                else
                {
                    // Apply scissor/clipping rectangle
                    const Graphic::Scissor Scissor(
                        static_cast<UInt16>(Command.ClipRect.x - Commands.DisplayPos.x),
                        static_cast<UInt16>(Command.ClipRect.y - Commands.DisplayPos.y),
                        static_cast<UInt16>(Command.ClipRect.z - Command.ClipRect.x),
                        static_cast<UInt16>(Command.ClipRect.w - Command.ClipRect.y));
                    if (Scissor.Width == 0 || Scissor.Height == 0)
                    {
                        continue;
                    }

                    Ref<Graphic::Command> GfxCommand = GfxCommands[Element];

                    GfxCommand.Scissor = Scissor;
                    GfxCommand.Vertices.Append(VtxSlice.GetDescriptor());
                    GfxCommand.Indices = IdxSlice.GetDescriptor();
                    GfxCommand.Uniforms[Enum::Cast(Graphic::UniformScope::Global)] = UboSlice.GetDescriptor();
                    GfxCommand.Pipeline = mTechnique->GetHandle();
                    GfxCommand.Textures.Append(Command.GetTexID());
                    GfxCommand.Samplers.Append(Graphic::Sampler()); // TODO: Move to Technique's Static Sampler
                    GfxCommand.Parameters = {
                        .Count     = Command.ElemCount,
                        .Base      = static_cast<SInt32>(Command.VtxOffset + VtxOffset),
                        .Offset    = Command.IdxOffset + IdxOffset,
                        .Instances = 1
                    };
                }
            }

            VtxOffset += CommandList->VtxBuffer.Size;
            IdxOffset += CommandList->IdxBuffer.Size;
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::CreateTexture(Ptr<ImTextureData> Texture)
    {
        const Graphic::Object ID = mGraphics->CreateTexture(
            Graphic::TextureLayout::Texture2D,
            Graphic::TextureFormat::RGBA8UIntNorm,
            Graphic::Storage::Stream,
            Graphic::Usage::Sample,
            Texture->Width,
            Texture->Height,
            1,
            Graphic::Multisample::X1,
            Blob::Borrow<Byte>(static_cast<ConstPtr<Byte>>(Texture->GetPixels()), Texture->Width * Texture->Height * 4));
        Texture->SetTexID(ID);
        Texture->SetStatus(ImTextureStatus_OK);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::DeleteTexture(Ptr<ImTextureData> Texture)
    {
        if (const Graphic::Object Handle = Texture->GetTexID(); Handle)
        {
            mGraphics->DeleteTexture(Handle);

            // Invalidate texture ID.
            Texture->SetTexID(ImTextureID_Invalid);
        }
        Texture->SetStatus(ImTextureStatus_Destroyed);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::UpdateTexture(Ptr<ImTextureData> Texture)
    {
        for (const auto [X, Y, W, H] : Texture->Updates)
        {
            mGraphics->UpdateTexture(
                Texture->GetTexID(),
                0,
                X,
                Y,
                W,
                H,
                Texture->GetPitch(),
                Blob::Borrow<Byte>(static_cast<ConstPtr<Byte>>(Texture->GetPixelsAt(X, Y)), Texture->Width * Texture->Height * 4));
        }
        Texture->SetStatus(ImTextureStatus_OK);
    }
}