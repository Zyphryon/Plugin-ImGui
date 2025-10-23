// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2021-2025 by Agustin L. Alvarez. All rights reserved.
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

    void ImGuiRenderer::Initialize(Ref<Service::Host> Host)
    {
        ConstTracker<Content::Service> Content = Host.GetService<Content::Service>();
        mPipeline = Content->Load<Graphic::Pipeline>("Engine://Pipeline/UI.effect");
        mGraphics = Host.GetService<Graphic::Service>();

        // Set maximum texture size limits for the renderer backend.
        Ref<ImGuiPlatformIO> PlatformIO = ImGui::GetPlatformIO();
        PlatformIO.Renderer_TextureMaxWidth  = mGraphics->GetCapabilities().MaxTextureDimension;
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
        // Abort drawing if the pipeline has not finished loading or compiling.
        if (!mPipeline->HasCompleted())
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

        auto [VtxPtr, VtxStream] = mGraphics->Allocate<ImDrawVert>(Graphic::Usage::Vertex, Commands.TotalVtxCount);
        auto [IdxPtr, IdxStream] = mGraphics->Allocate<ImDrawIdx>(Graphic::Usage::Index, Commands.TotalIdxCount);

        const Matrix4x4 Projection = Matrix4x4::CreateOrthographic(
                Commands.DisplayPos.x,
                Commands.DisplayPos.x + Commands.DisplaySize.x,
                Commands.DisplayPos.y + Commands.DisplaySize.y,
                Commands.DisplayPos.y,
                -1.0f,
                +1.0f);
        const auto Uniforms = mGraphics->Allocate(Graphic::Usage::Uniform, ConstSpan(&Projection, 1));

        UInt32 VtxOffset = 0;
        UInt32 IdxOffset = 0;

        for (ConstPtr<ImDrawList> CommandList : Commands.CmdLists)
        {
            std::memcpy(VtxPtr, CommandList->VtxBuffer.Data, CommandList->VtxBuffer.Size * sizeof(ImDrawVert));
            std::memcpy(IdxPtr, CommandList->IdxBuffer.Data, CommandList->IdxBuffer.Size * sizeof(ImDrawIdx));
            VtxPtr += CommandList->VtxBuffer.Size;
            IdxPtr += CommandList->IdxBuffer.Size;

            for (ConstRef<ImDrawCmd> Command : CommandList->CmdBuffer)
            {
                if (Command.UserCallback)
                {
                    Command.UserCallback(CommandList, &Command);
                }
                else
                {
                    // Apply scissor/clipping rectangle
                    const Graphic::Scissor Scissor(
                        static_cast<UInt16>(Command.ClipRect.x - Commands.DisplayPos.x),
                        static_cast<UInt16>(Command.ClipRect.y - Commands.DisplayPos.y),
                        static_cast<UInt16>(Command.ClipRect.z - Commands.DisplayPos.x - Command.ClipRect.x),
                        static_cast<UInt16>(Command.ClipRect.w - Commands.DisplayPos.y - Command.ClipRect.y));
                    if (Scissor.Width == 0 || Scissor.Height == 0)
                    {
                        continue;
                    }

                    mEncoder.SetScissor(Scissor);
                    mEncoder.SetVertices(0, VtxStream);
                    mEncoder.SetIndices(IdxStream);
                    mEncoder.SetUniform(0, Uniforms);
                    mEncoder.SetPipeline(mPipeline->GetID());
                    mEncoder.SetTexture(0, Command.GetTexID());
                    mEncoder.SetSampler(0, Graphic::Sampler(
                        Graphic::TextureEdge::Clamp,
                        Graphic::TextureEdge::Clamp,
                        Graphic::TextureFilter::LinearMipLinear));
                    mEncoder.Draw(Command.ElemCount, Command.VtxOffset + VtxOffset, Command.IdxOffset + IdxOffset);
                }
            }

            VtxOffset += CommandList->VtxBuffer.Size;
            IdxOffset += CommandList->IdxBuffer.Size;
        }

        // Submit draw calls
        mGraphics->Submit(mEncoder.GetSubmissions());
        mEncoder.Clear();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::CreateTexture(Ptr<ImTextureData> Texture)
    {
        const Graphic::Object ID = mGraphics->CreateTexture(
            Graphic::Access::Device,
            Graphic::TextureFormat::RGBA8UIntNorm,
            Graphic::TextureLayout::Source,
            Texture->Width,
            Texture->Height,
            1,
            Graphic::Samples::X1,
            Blob(Texture->GetPixels(), Texture->Width * Texture->Height * 4, Blob::kEmptyDeleter));
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
                1,
                X,
                Y,
                W,
                H,
                Texture->GetPitch(),
                Blob(Texture->GetPixelsAt(X, Y), Texture->Width * Texture->Height * 4, Blob::kEmptyDeleter));
        }
        Texture->SetStatus(ImTextureStatus_OK);
    }
}