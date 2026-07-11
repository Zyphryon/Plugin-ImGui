// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2021-2026 by Agustin L. Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include <imgui.h>
#include <Zyphryon.Graphic/Technique.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Plugin
{
    /// \brief Handles rendering of ImGui draw data using the engine graphics service.
    class ImGuiRenderer final
    {
    public:

        /// Initializes the ImGui renderer with the specified host.
        ///
        /// \param Host The engine subsystem host used to access graphics services.
        void Initialize(Ref<Engine::Subsystem::Host> Host);

        /// Disposes of the renderer and releases all associated resources.
        void Dispose();

        /// Submits ImGui draw commands for rendering.
        ///
        /// \param Commands The ImGui draw data containing all commands to be rendered.
        void Submit(ConstRef<ImDrawData> Commands);

    private:

        /// Creates a texture resource for ImGui rendering.
        ///
        /// \param Texture The texture data to be created.
        void CreateTexture(Ptr<ImTextureData> Texture);

        /// Deletes a texture resource previously created for ImGui rendering.
        ///
        /// \param Texture The texture data to be deleted.
        void DeleteTexture(Ptr<ImTextureData> Texture);

        /// Updates an existing texture resource with new data.
        ///
        /// \param Texture The texture data to be updated.
        void UpdateTexture(Ptr<ImTextureData> Texture);

    private:

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        Retainer<Graphic::Service>   mGraphics;
        Retainer<Graphic::Technique> mTechnique;
    };
}