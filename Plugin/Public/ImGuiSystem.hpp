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

#include "ImGuiRenderer.hpp"
#include <Zyphryon.Engine/Device.hpp>
#include <Zyphryon.Input/Common.hpp>

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

        /// \brief Tears down the ImGui system and releases its resources.
        ///
        /// \param Host Service host providing access to engine subsystems.
        void Teardown(Ref<Service::Host> Host);

        /// \brief Starts a new ImGui frame.
        ///
        /// \param Time Frame timing information for synchronization.
        void Begin(ConstRef<Time> Time);

        /// \brief Ends the current ImGui frame.
        void End();

    private:

        /// \brief Handles text input events.
        static Bool OnKeyType(UInt32 Codepoint);

        /// \brief Handles key release events.
        static Bool OnKeyUp(Input::Key Key);

        /// \brief Handles key press events.
        static Bool OnKeyDown(Input::Key Key);

        /// \brief Handles mouse movement events.
        static Bool OnMouseMove(Real32 X, Real32 Y, Real32 DeltaX, Real32 DeltaY);

        /// \brief Handles mouse scroll events.
        static Bool OnMouseScroll(Real32 DeltaX, Real32 DeltaY);

        /// \brief Handles mouse button release events.
        static Bool OnMouseUp(Input::Button Button);

        /// \brief Handles mouse button press events.
        static Bool OnMouseDown(Input::Button Button);

        /// \brief Handles window focus change events.
        static Bool OnWindowFocus(Bool Focused);

        /// \brief Handles window resize events.
        static Bool OnWindowResize(UInt32 Width, UInt32 Height);

    private:

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        ImGuiRenderer mRenderer;
    };
}