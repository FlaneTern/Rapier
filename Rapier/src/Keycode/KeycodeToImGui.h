#pragma once

#include "RapierKeycode.h"
#include "imgui.h"


static ImGuiKey Key_RapierToImGui(int key)
{
    switch (key)
    {
    case RapierKey_Tab: return ImGuiKey_Tab;
    case RapierKey_LeftArrow: return ImGuiKey_LeftArrow;
    case RapierKey_RightArrow: return ImGuiKey_RightArrow;
    case RapierKey_UpArrow: return ImGuiKey_UpArrow;
    case RapierKey_DownArrow: return ImGuiKey_DownArrow;
    case RapierKey_PageUp: return ImGuiKey_PageUp;
    case RapierKey_PageDown: return ImGuiKey_PageDown;
    case RapierKey_Home: return ImGuiKey_Home;
    case RapierKey_End: return ImGuiKey_End;
    case RapierKey_Insert: return ImGuiKey_Insert;
    case RapierKey_Delete: return ImGuiKey_Delete;
    case RapierKey_Backspace: return ImGuiKey_Backspace;
    case RapierKey_Space: return ImGuiKey_Space;
    case RapierKey_Enter: return ImGuiKey_Enter;
    case RapierKey_Escape: return ImGuiKey_Escape;
    case RapierKey_Apostrophe: return ImGuiKey_Apostrophe;
    case RapierKey_Comma: return ImGuiKey_Comma;
    case RapierKey_Minus: return ImGuiKey_Minus;
    case RapierKey_Period: return ImGuiKey_Period;
    case RapierKey_Slash: return ImGuiKey_Slash;
    case RapierKey_Semicolon: return ImGuiKey_Semicolon;
    case RapierKey_Equal: return ImGuiKey_Equal;
    case RapierKey_LeftBracket: return ImGuiKey_LeftBracket;
    case RapierKey_Backslash: return ImGuiKey_Backslash;
    case RapierKey_RightBracket: return ImGuiKey_RightBracket;
    case RapierKey_GraveAccent: return ImGuiKey_GraveAccent;
    case RapierKey_CapsLock: return ImGuiKey_CapsLock;
    case RapierKey_ScrollLock: return ImGuiKey_ScrollLock;
    case RapierKey_NumLock: return ImGuiKey_NumLock;
    case RapierKey_PrintScreen: return ImGuiKey_PrintScreen;
    case RapierKey_Pause: return ImGuiKey_Pause;
    case RapierKey_Keypad0: return ImGuiKey_Keypad0;
    case RapierKey_Keypad1: return ImGuiKey_Keypad1;
    case RapierKey_Keypad2: return ImGuiKey_Keypad2;
    case RapierKey_Keypad3: return ImGuiKey_Keypad3;
    case RapierKey_Keypad4: return ImGuiKey_Keypad4;
    case RapierKey_Keypad5: return ImGuiKey_Keypad5;
    case RapierKey_Keypad6: return ImGuiKey_Keypad6;
    case RapierKey_Keypad7: return ImGuiKey_Keypad7;
    case RapierKey_Keypad8: return ImGuiKey_Keypad8;
    case RapierKey_Keypad9: return ImGuiKey_Keypad9;
    case RapierKey_KeypadDecimal: return ImGuiKey_KeypadDecimal;
    case RapierKey_KeypadDivide: return ImGuiKey_KeypadDivide;
    case RapierKey_KeypadMultiply: return ImGuiKey_KeypadMultiply;
    case RapierKey_KeypadSubtract: return ImGuiKey_KeypadSubtract;
    case RapierKey_KeypadAdd: return ImGuiKey_KeypadAdd;
    case RapierKey_KeypadEnter: return ImGuiKey_KeypadEnter;
    case RapierKey_KeypadEqual: return ImGuiKey_KeypadEqual;
    case RapierKey_LeftShift: return ImGuiKey_LeftShift;
    case RapierKey_LeftCtrl: return ImGuiKey_LeftCtrl;
    case RapierKey_LeftAlt: return ImGuiKey_LeftAlt;
    case RapierKey_LeftSuper: return ImGuiKey_LeftSuper;
    case RapierKey_RightShift: return ImGuiKey_RightShift;
    case RapierKey_RightCtrl: return ImGuiKey_RightCtrl;
    case RapierKey_RightAlt: return ImGuiKey_RightAlt;
    case RapierKey_RightSuper: return ImGuiKey_RightSuper;
    case RapierKey_Menu: return ImGuiKey_Menu;
    case RapierKey_0: return ImGuiKey_0;
    case RapierKey_1: return ImGuiKey_1;
    case RapierKey_2: return ImGuiKey_2;
    case RapierKey_3: return ImGuiKey_3;
    case RapierKey_4: return ImGuiKey_4;
    case RapierKey_5: return ImGuiKey_5;
    case RapierKey_6: return ImGuiKey_6;
    case RapierKey_7: return ImGuiKey_7;
    case RapierKey_8: return ImGuiKey_8;
    case RapierKey_9: return ImGuiKey_9;
    case RapierKey_A: return ImGuiKey_A;
    case RapierKey_B: return ImGuiKey_B;
    case RapierKey_C: return ImGuiKey_C;
    case RapierKey_D: return ImGuiKey_D;
    case RapierKey_E: return ImGuiKey_E;
    case RapierKey_F: return ImGuiKey_F;
    case RapierKey_G: return ImGuiKey_G;
    case RapierKey_H: return ImGuiKey_H;
    case RapierKey_I: return ImGuiKey_I;
    case RapierKey_J: return ImGuiKey_J;
    case RapierKey_K: return ImGuiKey_K;
    case RapierKey_L: return ImGuiKey_L;
    case RapierKey_M: return ImGuiKey_M;
    case RapierKey_N: return ImGuiKey_N;
    case RapierKey_O: return ImGuiKey_O;
    case RapierKey_P: return ImGuiKey_P;
    case RapierKey_Q: return ImGuiKey_Q;
    case RapierKey_R: return ImGuiKey_R;
    case RapierKey_S: return ImGuiKey_S;
    case RapierKey_T: return ImGuiKey_T;
    case RapierKey_U: return ImGuiKey_U;
    case RapierKey_V: return ImGuiKey_V;
    case RapierKey_W: return ImGuiKey_W;
    case RapierKey_X: return ImGuiKey_X;
    case RapierKey_Y: return ImGuiKey_Y;
    case RapierKey_Z: return ImGuiKey_Z;
    case RapierKey_F1: return ImGuiKey_F1;
    case RapierKey_F2: return ImGuiKey_F2;
    case RapierKey_F3: return ImGuiKey_F3;
    case RapierKey_F4: return ImGuiKey_F4;
    case RapierKey_F5: return ImGuiKey_F5;
    case RapierKey_F6: return ImGuiKey_F6;
    case RapierKey_F7: return ImGuiKey_F7;
    case RapierKey_F8: return ImGuiKey_F8;
    case RapierKey_F9: return ImGuiKey_F9;
    case RapierKey_F10: return ImGuiKey_F10;
    case RapierKey_F11: return ImGuiKey_F11;
    case RapierKey_F12: return ImGuiKey_F12;
    default: return ImGuiKey_None;
    }
}