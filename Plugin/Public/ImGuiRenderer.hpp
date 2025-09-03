// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2021-2025 by Agustin L. Alvarez. All rights reserved.
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
#include "ImGuiFont.hpp"
#include <Zyphryon.Content/Service.hpp>
#include <Zyphryon.Graphic/Service.hpp>
#include <Zyphryon.Graphic/Encoder.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Plugin
{
    /// \brief Handles rendering of ImGui draw data using the engine graphics service.
    class ImGuiRenderer final
    {
    public:

        /// \brief Initializes the ImGui renderer.
        ///
        /// \param Host Service host providing access to graphics and content subsystems.
        void Initialize(Ref<Service::Host> Host);

        /// \brief Submits ImGui draw data for rendering.
        ///
        /// \param Commands The set of ImGui draw lists to render.
        void Submit(ConstRef<ImDrawData> Commands);

    private:

        /// \brief Creates and uploads font textures required by ImGui.
        void CreateFonts();

        /// \brief Builds the font atlas texture and registers it with the graphics backend.
        ///
        /// \param Host Service host used to allocate and register GPU resources.
        void CreateTextureFontAtlas(Ref<Service::Host> Host);

    private:

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        Tracker<Graphic::Service>  mGraphics;
        Tracker<Graphic::Pipeline> mPipeline;
        Graphic::Encoder           mEncoder;
    };
}