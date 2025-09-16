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

#include <Zyphryon.Engine/Device.hpp>
#include "ImGuiInput.hpp"
#include "ImGuiRenderer.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Plugin
{
    /// \brief Provides integration between the engine and ImGui.
    class ImGuiSystem final
    {
    public:

        /// \brief Initializes the ImGui system with context, IO, styling, and renderer.
        ///
        /// \param Host   Service host providing access to engine subsystems.
        /// \param Device Engine device used for display and clipboard interaction.
        void Initialize(Ref<Service::Host> Host, Ref<Engine::Device> Device);

        /// \brief Forwards an input event to the ImGui input system.
        ///
        /// \param Event The input event to process.
        /// \return `true` if the event was handled by ImGui, otherwise `false`.
        ZYPHRYON_INLINE Bool Forward(ConstRef<Input::Event> Event)
        {
            return mInput.OnEvent(Event);
        }

        /// \brief Starts a new ImGui frame.
        ///
        /// \param Time Frame timing information for synchronization.
        void Begin(ConstRef<Time> Time);

        /// \brief Ends the current ImGui frame.
        void End();

        /// \brief Builds the font atlas texture and registers it with the graphics backend.
        ///
        /// \param Host Service host used to allocate and register GPU resources.
        void CreateTextureFontAtlas(Ref<Service::Host> Host);

    private:

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        ImGuiRenderer mRenderer;
        ImGuiInput    mInput;
    };
}