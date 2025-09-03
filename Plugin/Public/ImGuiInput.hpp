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

#include <Zyphryon.Input/Listener.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Plugin
{
    /// \brief Adapts engine input events for ImGui.
    class ImGuiInput final : public Input::Listener
    {
    private:

        /// \copydoc Input:Listener::OnKeyType
        Bool OnKeyType(UInt32 Codepoint) override;

        /// \copydoc Input:Listener::OnKeyUp
        Bool OnKeyUp(Input::Key Key) override;

        /// \copydoc Input:Listener::OnKeyDown
        Bool OnKeyDown(Input::Key Key) override;

        /// \copydoc Input:Listener::OnMouseMove
        Bool OnMouseMove(Real32 X, Real32 Y, Real32 DeltaX, Real32 DeltaY) override;

        /// \copydoc Input:Listener::OnMouseScroll
        Bool OnMouseScroll(Real32 DeltaX, Real32 DeltaY) override;

        /// \copydoc Input:Listener::OnMouseUp
        Bool OnMouseUp(Input::Button Button) override;

        /// \copydoc Input:Listener::OnMouseDown
        Bool OnMouseDown(Input::Button Button) override;

        /// \copydoc Input:Listener::OnWindowFocus
        Bool OnWindowFocus(Bool Focused) override;

        /// \copydoc Input:Listener::OnWindowResize
        Bool OnWindowResize(UInt32 Width, UInt32 Height) override;
    };
}