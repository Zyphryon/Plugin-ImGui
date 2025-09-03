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

        CreateFonts();
        CreateTextureFontAtlas(Host);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::Submit(ConstRef<ImDrawData> Commands)
    {
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
                            Command.ClipRect.x - Commands.DisplayPos.x,
                            Command.ClipRect.y - Commands.DisplayPos.y,
                            Command.ClipRect.x - Command.ClipRect.z - Commands.DisplayPos.x,
                            Command.ClipRect.y - Command.ClipRect.w - Commands.DisplayPos.y);
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
                        Graphic::TextureFilter::MinMagMipLinear));
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

    void ImGuiRenderer::CreateFonts()
    {
        constexpr Real32  kAwesomeFontSize    = 13.0f;
        constexpr ImWchar kAwesomeFontRange[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

        ImFontConfig Config;
        Config.MergeMode        = true;
        Config.PixelSnapH       = true;
        Config.GlyphMinAdvanceX = kAwesomeFontSize;

        ImGui::GetIO().Fonts->AddFontDefault();
        ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
                FontAwesome400EmbeddedFile,
                sizeof(FontAwesome400EmbeddedFile), kAwesomeFontSize, &Config, kAwesomeFontRange);
        ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
                FontAwesome900EmbeddedFile,
                sizeof(FontAwesome900EmbeddedFile), kAwesomeFontSize, &Config, kAwesomeFontRange);
        ImGui::GetIO().Fonts->Build();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiRenderer::CreateTextureFontAtlas(Ref<Service::Host> Host)
    {
        Ptr<UInt8> Pixels;
        SInt32     Width;
        SInt32     Height;
        ImGui::GetIO().Fonts->GetTexDataAsRGBA32(&Pixels, &Width, &Height);

        Tracker<Graphic::Texture> Texture = Tracker<Graphic::Texture>::Create("ImGUI_FontAtlas");
        Blob Data(Pixels, Width * Height * 4, Blob::kEmptyDeleter);

        Texture->Load(Graphic::TextureFormat::RGBA8UIntNorm, Width, Height, 1, Move(Data));
        Texture->Create(Host);

        ImGui::GetIO().Fonts->SetTexID(Texture->GetID());
    }
}