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

#include "ImGuiRenderer.hpp"
#include <Zyphryon.Input/Common.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Plugin
{
    /// System for managing ImGui integration with the engine.
    class ImGuiSystem final
    {
    public:

        /// Initializes the ImGui system with the specified host.
        ///
        /// \param Host The engine subsystem host used to access platform and graphics services.
        void Initialize(Ref<Engine::Subsystem::Host> Host);

        /// Tears down the ImGui system and releases all resources.
        ///
        /// \param Host The engine subsystem host used to access platform and graphics services.
        void Teardown(Ref<Engine::Subsystem::Host> Host);

        /// Begins a new ImGui frame.
        ///
        /// \param Time The current frame time in seconds.
        void Begin(Real64 Time);

        /// Ends the current ImGui frame and submits rendering commands.
        void End();

    private:

        /// \brief Handles text input events.
        static Bool OnKeyType(Text Text);

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