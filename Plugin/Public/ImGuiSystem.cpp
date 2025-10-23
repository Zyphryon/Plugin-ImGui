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

#include "ImGuiSystem.hpp"
#include <Zyphryon.Input/Service.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Plugin
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    constexpr auto GetKey(Input::Key Key)
    {
        switch (Key)
        {
        case Input::Key::Space:
            return ImGuiKey_Space;
        case Input::Key::Apostrophe:
            return ImGuiKey_Apostrophe;
        case Input::Key::Comma:
            return ImGuiKey_Comma;
        case Input::Key::Minus:
            return ImGuiKey_Minus;
        case Input::Key::Period:
            return ImGuiKey_Period;
        case Input::Key::Slash:
            return ImGuiKey_Slash;
        case Input::Key::Alpha0:
            return ImGuiKey_0;
        case Input::Key::Alpha1:
            return ImGuiKey_1;
        case Input::Key::Alpha2:
            return ImGuiKey_2;
        case Input::Key::Alpha3:
            return ImGuiKey_3;
        case Input::Key::Alpha4:
            return ImGuiKey_4;
        case Input::Key::Alpha5:
            return ImGuiKey_5;
        case Input::Key::Alpha6:
            return ImGuiKey_6;
        case Input::Key::Alpha7:
            return ImGuiKey_7;
        case Input::Key::Alpha8:
            return ImGuiKey_8;
        case Input::Key::Alpha9:
            return ImGuiKey_9;
        case Input::Key::Semicolon:
            return ImGuiKey_Semicolon;
        case Input::Key::Equal:
            return ImGuiKey_Equal;
        case Input::Key::A:
            return ImGuiKey_A;
        case Input::Key::B:
            return ImGuiKey_B;
        case Input::Key::C:
            return ImGuiKey_C;
        case Input::Key::D:
            return ImGuiKey_D;
        case Input::Key::E:
            return ImGuiKey_E;
        case Input::Key::F:
            return ImGuiKey_F;
        case Input::Key::G:
            return ImGuiKey_G;
        case Input::Key::H:
            return ImGuiKey_H;
        case Input::Key::I:
            return ImGuiKey_I;
        case Input::Key::J:
            return ImGuiKey_J;
        case Input::Key::K:
            return ImGuiKey_K;
        case Input::Key::L:
            return ImGuiKey_L;
        case Input::Key::M:
            return ImGuiKey_M;
        case Input::Key::N:
            return ImGuiKey_N;
        case Input::Key::O:
            return ImGuiKey_O;
        case Input::Key::P:
            return ImGuiKey_P;
        case Input::Key::Q:
            return ImGuiKey_Q;
        case Input::Key::R:
            return ImGuiKey_R;
        case Input::Key::S:
            return ImGuiKey_S;
        case Input::Key::T:
            return ImGuiKey_T;
        case Input::Key::U:
            return ImGuiKey_U;
        case Input::Key::V:
            return ImGuiKey_V;
        case Input::Key::W:
            return ImGuiKey_W;
        case Input::Key::X:
            return ImGuiKey_X;
        case Input::Key::Y:
            return ImGuiKey_Y;
        case Input::Key::Z:
            return ImGuiKey_Z;
        case Input::Key::Backslash:
            return ImGuiKey_Backslash;
        case Input::Key::Grave:
            return ImGuiKey_GraveAccent;
        case Input::Key::Escape:
            return ImGuiKey_Escape;
        case Input::Key::Enter:
            return ImGuiKey_Enter;
        case Input::Key::Tab:
            return ImGuiKey_Tab;
        case Input::Key::Backspace:
            return ImGuiKey_Backspace;
        case Input::Key::Insert:
            return ImGuiKey_Insert;
        case Input::Key::Delete:
            return ImGuiKey_Delete;
        case Input::Key::Right:
            return ImGuiKey_RightArrow;
        case Input::Key::Left:
            return ImGuiKey_LeftArrow;
        case Input::Key::Down:
            return ImGuiKey_DownArrow;
        case Input::Key::Up:
            return ImGuiKey_UpArrow;
        case Input::Key::PageUp:
            return ImGuiKey_PageUp;
        case Input::Key::PageDown:
            return ImGuiKey_PageDown;
        case Input::Key::Home:
            return ImGuiKey_Home;
        case Input::Key::End:
            return ImGuiKey_End;
        case Input::Key::Capital:
            return ImGuiKey_CapsLock;
        case Input::Key::Scroll:
            return ImGuiKey_ScrollLock;
        case Input::Key::Lock:
            return ImGuiKey_NumLock;
        case Input::Key::Print:
            return ImGuiKey_PrintScreen;
        case Input::Key::Pause:
            return ImGuiKey_Pause;
        case Input::Key::F1:
            return ImGuiKey_F1;
        case Input::Key::F2:
            return ImGuiKey_F2;
        case Input::Key::F3:
            return ImGuiKey_F3;
        case Input::Key::F4:
            return ImGuiKey_F4;
        case Input::Key::F5:
            return ImGuiKey_F5;
        case Input::Key::F6:
            return ImGuiKey_F6;
        case Input::Key::F7:
            return ImGuiKey_F7;
        case Input::Key::F8:
            return ImGuiKey_F8;
        case Input::Key::F9:
            return ImGuiKey_F9;
        case Input::Key::F10:
            return ImGuiKey_F10;
        case Input::Key::F11:
            return ImGuiKey_F11;
        case Input::Key::F12:
            return ImGuiKey_F12;
        case Input::Key::Keypad0:
            return ImGuiKey_Keypad0;
        case Input::Key::Keypad1:
            return ImGuiKey_Keypad1;
        case Input::Key::Keypad2:
            return ImGuiKey_Keypad2;
        case Input::Key::Keypad3:
            return ImGuiKey_Keypad3;
        case Input::Key::Keypad4:
            return ImGuiKey_Keypad4;
        case Input::Key::Keypad5:
            return ImGuiKey_Keypad5;
        case Input::Key::Keypad6:
            return ImGuiKey_Keypad6;
        case Input::Key::Keypad7:
            return ImGuiKey_Keypad7;
        case Input::Key::Keypad8:
            return ImGuiKey_Keypad8;
        case Input::Key::Keypad9:
            return ImGuiKey_Keypad9;
        case Input::Key::Decimal:
            return ImGuiKey_KeypadDecimal;
        case Input::Key::Divide:
            return ImGuiKey_KeypadDivide;
        case Input::Key::Multiply:
            return ImGuiKey_KeypadMultiply;
        case Input::Key::Subtract:
            return ImGuiKey_KeypadSubtract;
        case Input::Key::Add:
            return ImGuiKey_KeypadAdd;
        case Input::Key::LeftBracket:
            return ImGuiKey_LeftBracket;
        case Input::Key::LeftShift:
            return ImGuiKey_LeftShift;
        case Input::Key::LeftCtrl:
            return ImGuiKey_LeftCtrl;
        case Input::Key::LeftAlt:
            return ImGuiKey_LeftAlt;
        case Input::Key::LeftSuper:
            return ImGuiKey_LeftSuper;
        case Input::Key::Menu:
            return ImGuiKey_Menu;
        case Input::Key::RightBracket:
            return ImGuiKey_RightBracket;
        case Input::Key::RightShift:
            return ImGuiKey_RightShift;
        case Input::Key::RightCtrl:
            return ImGuiKey_RightCtrl;
        case Input::Key::RightAlt:
            return ImGuiKey_RightAlt;
        case Input::Key::RightSuper:
            return ImGuiKey_RightSuper;
        case Input::Key::Unknown:
            break;
        }
        return ImGuiKey_None;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    constexpr auto GetKeyModifier(Input::Key Key)
    {
        switch (Key)
        {
        case Input::Key::LeftCtrl:
        case Input::Key::RightCtrl:
            return ImGuiMod_Ctrl;
        case Input::Key::LeftAlt:
        case Input::Key::RightAlt:
            return ImGuiMod_Alt;
        case Input::Key::LeftShift:
        case Input::Key::RightShift:
            return ImGuiMod_Shift;
        case Input::Key::LeftSuper:
        case Input::Key::RightSuper:
            return ImGuiMod_Super;
        default:
            return ImGuiMod_None;
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    constexpr auto GetButton(Input::Button Button)
    {
        switch (Button)
        {
        case Input::Button::Left:
            return Enum::Cast(ImGuiMouseButton_Left);
        case Input::Button::Middle:
            return Enum::Cast(ImGuiMouseButton_Middle);
        case Input::Button::Right:
            return Enum::Cast(ImGuiMouseButton_Right);
        case Input::Button::Back:
            return 3;
        case Input::Button::Forward:
            return 4;
        default:
            return -1;
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiSystem::Initialize(Ref<Service::Host> Host, Ref<Engine::Device> Device)
    {
        // Create the ImGui context and configure basic IO flags (keyboard navigation, docking, renderer features).
        ImGui::CreateContext();

        Ref<ImGuiIO> IO = ImGui::GetIO();
        IO.ConfigFlags            |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
        IO.BackendFlags           |= ImGuiBackendFlags_RendererHasVtxOffset | ImGuiBackendFlags_RendererHasTextures;
        IO.DisplaySize             = ImVec2(Device.GetWidth(), Device.GetHeight());
        IO.DisplayFramebufferScale = ImVec2(Device.GetScale(), Device.GetScale());
        IO.BackendPlatformUserData = &Device;

        // Register custom clipboard handlers to integrate with the engine's device clipboard API.
        Ref<ImGuiPlatformIO> PlatformIO = ImGui::GetPlatformIO();
        PlatformIO.Platform_SetClipboardTextFn = [](Ptr<ImGuiContext>, ConstPtr<Char> Text) {
            static_cast<Ptr<Engine::Device>>(ImGui::GetIO().BackendPlatformUserData)->SetClipboard(Text);
        };
        PlatformIO.Platform_GetClipboardTextFn = [](Ptr<ImGuiContext>) -> ConstPtr<Char> {
            static Str8 Clipboard;
            Clipboard = static_cast<Ptr<Engine::Device>>(ImGui::GetIO().BackendPlatformUserData)->GetClipboard();
            return Clipboard.data();
        };
        PlatformIO.Platform_OpenInShellFn      = [](Ptr<ImGuiContext>, ConstPtr<Char> Url) -> Bool {
            return SDL_OpenURL(Url);
        };

        // Apply the default dark theme styling.
        ImGui::StyleColorsDark();

        // Initialize the renderer backend for ImGui.
        mRenderer.Initialize(Host);

        // Register input event callbacks.
        ConstTracker<Input::Service> Input = Host.GetService<Input::Service>();

        Input->OnKeyDown.AddFunction<&ImGuiSystem::OnKeyDown>();
        Input->OnKeyUp.AddFunction<&ImGuiSystem::OnKeyUp>();
        Input->OnKeyType.AddFunction<&ImGuiSystem::OnKeyType>();
        Input->OnMouseDown.AddFunction<&ImGuiSystem::OnMouseDown>();
        Input->OnMouseUp.AddFunction<&ImGuiSystem::OnMouseUp>();
        Input->OnMouseMove.AddFunction<&ImGuiSystem::OnMouseMove>();
        Input->OnMouseScroll.AddFunction<&ImGuiSystem::OnMouseScroll>();
        Input->OnWindowFocus.AddFunction<&ImGuiSystem::OnWindowFocus>();
        Input->OnWindowResize.AddFunction<&ImGuiSystem::OnWindowResize>();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiSystem::Teardown(Ref<Service::Host> Host)
    {
        // Dispose of the renderer backend.
        mRenderer.Dispose();

        // Releases all input event callbacks.
        ConstTracker<Input::Service> Input = Host.GetService<Input::Service>();

        Input->OnKeyDown.RemoveFunction<&ImGuiSystem::OnKeyDown>();
        Input->OnKeyUp.RemoveFunction<&ImGuiSystem::OnKeyUp>();
        Input->OnKeyType.RemoveFunction<&ImGuiSystem::OnKeyType>();
        Input->OnMouseDown.RemoveFunction<&ImGuiSystem::OnMouseDown>();
        Input->OnMouseUp.RemoveFunction<&ImGuiSystem::OnMouseUp>();
        Input->OnMouseMove.RemoveFunction<&ImGuiSystem::OnMouseMove>();
        Input->OnMouseScroll.RemoveFunction<&ImGuiSystem::OnMouseScroll>();
        Input->OnWindowFocus.RemoveFunction<&ImGuiSystem::OnWindowFocus>();
        Input->OnWindowResize.RemoveFunction<&ImGuiSystem::OnWindowResize>();
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiSystem::Begin(ConstRef<Time> Time)
    {
        ImGui::NewFrame();
        ImGui::GetIO().DeltaTime = static_cast<Real32>(Time.GetDelta());
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void ImGuiSystem::End()
    {
        ImGui::Render();

        if (const ConstPtr<ImDrawData> Commands = ImGui::GetDrawData(); Commands && Commands->TotalVtxCount > 0)
        {
            mRenderer.Submit(* Commands);
        }
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnKeyType(UInt32 Codepoint)
    {
        ImGui::GetIO().AddInputCharacter(Codepoint);
        return ImGui::GetIO().WantCaptureKeyboard;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnKeyUp(Input::Key Key)
    {
        if (const auto ImModifier = GetKeyModifier(Key); ImModifier != ImGuiMod_None)
        {
            ImGui::GetIO().AddKeyEvent(ImModifier, false);
        }
        if (const auto ImKey = GetKey(Key); ImKey != ImGuiKey_None)
        {
            ImGui::GetIO().AddKeyEvent(ImKey, false);
        }
        return ImGui::GetIO().WantCaptureKeyboard;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnKeyDown(Input::Key Key)
    {
        if (const auto ImModifier = GetKeyModifier(Key); ImModifier != ImGuiMod_None)
        {
            ImGui::GetIO().AddKeyEvent(ImModifier, true);
        }
        if (const auto ImKey = GetKey(Key); ImKey != ImGuiKey_None)
        {
            ImGui::GetIO().AddKeyEvent(ImKey, true);
        }
        return ImGui::GetIO().WantCaptureKeyboard;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnMouseMove(Real32 X, Real32 Y, Real32 DeltaX, Real32 DeltaY)
    {
        ImGui::GetIO().AddMousePosEvent(X, Y);
        return ImGui::GetIO().WantCaptureMouse;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnMouseScroll(Real32 DeltaX, Real32 DeltaY)
    {
        ImGui::GetIO().AddMouseWheelEvent(DeltaX, DeltaY);
        return ImGui::GetIO().WantCaptureMouse;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnMouseUp(Input::Button Button)
    {
        if (const auto ImButton = GetButton(Button); ImButton >= 0)
        {
            ImGui::GetIO().AddMouseButtonEvent(ImButton, false);
        }
        return ImGui::GetIO().WantCaptureMouse;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnMouseDown(Input::Button Button)
    {
        if (const auto ImButton = GetButton(Button); ImButton >= 0)
        {
            ImGui::GetIO().AddMouseButtonEvent(ImButton, true);
        }
        return ImGui::GetIO().WantCaptureMouse;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnWindowFocus(Bool Focused)
    {
        ImGui::GetIO().AddFocusEvent(Focused);
        return false;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool ImGuiSystem::OnWindowResize(UInt32 Width, UInt32 Height)
    {
        ImGui::GetIO().DisplaySize = ImVec2(Width, Height);
        return false;
    }
}