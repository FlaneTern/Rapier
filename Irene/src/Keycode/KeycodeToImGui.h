#pragma once

#include "IreneKeycode.h"
#include "imgui.h"


static ImGuiKey Key_IreneToImGui(int key)
{
    switch (key)
    {
    case IreneKey_Tab: return ImGuiKey_Tab;
    case IreneKey_LeftArrow: return ImGuiKey_LeftArrow;
    case IreneKey_RightArrow: return ImGuiKey_RightArrow;
    case IreneKey_UpArrow: return ImGuiKey_UpArrow;
    case IreneKey_DownArrow: return ImGuiKey_DownArrow;
    case IreneKey_PageUp: return ImGuiKey_PageUp;
    case IreneKey_PageDown: return ImGuiKey_PageDown;
    case IreneKey_Home: return ImGuiKey_Home;
    case IreneKey_End: return ImGuiKey_End;
    case IreneKey_Insert: return ImGuiKey_Insert;
    case IreneKey_Delete: return ImGuiKey_Delete;
    case IreneKey_Backspace: return ImGuiKey_Backspace;
    case IreneKey_Space: return ImGuiKey_Space;
    case IreneKey_Enter: return ImGuiKey_Enter;
    case IreneKey_Escape: return ImGuiKey_Escape;
    case IreneKey_Apostrophe: return ImGuiKey_Apostrophe;
    case IreneKey_Comma: return ImGuiKey_Comma;
    case IreneKey_Minus: return ImGuiKey_Minus;
    case IreneKey_Period: return ImGuiKey_Period;
    case IreneKey_Slash: return ImGuiKey_Slash;
    case IreneKey_Semicolon: return ImGuiKey_Semicolon;
    case IreneKey_Equal: return ImGuiKey_Equal;
    case IreneKey_LeftBracket: return ImGuiKey_LeftBracket;
    case IreneKey_Backslash: return ImGuiKey_Backslash;
    case IreneKey_RightBracket: return ImGuiKey_RightBracket;
    case IreneKey_GraveAccent: return ImGuiKey_GraveAccent;
    case IreneKey_CapsLock: return ImGuiKey_CapsLock;
    case IreneKey_ScrollLock: return ImGuiKey_ScrollLock;
    case IreneKey_NumLock: return ImGuiKey_NumLock;
    case IreneKey_PrintScreen: return ImGuiKey_PrintScreen;
    case IreneKey_Pause: return ImGuiKey_Pause;
    case IreneKey_Keypad0: return ImGuiKey_Keypad0;
    case IreneKey_Keypad1: return ImGuiKey_Keypad1;
    case IreneKey_Keypad2: return ImGuiKey_Keypad2;
    case IreneKey_Keypad3: return ImGuiKey_Keypad3;
    case IreneKey_Keypad4: return ImGuiKey_Keypad4;
    case IreneKey_Keypad5: return ImGuiKey_Keypad5;
    case IreneKey_Keypad6: return ImGuiKey_Keypad6;
    case IreneKey_Keypad7: return ImGuiKey_Keypad7;
    case IreneKey_Keypad8: return ImGuiKey_Keypad8;
    case IreneKey_Keypad9: return ImGuiKey_Keypad9;
    case IreneKey_KeypadDecimal: return ImGuiKey_KeypadDecimal;
    case IreneKey_KeypadDivide: return ImGuiKey_KeypadDivide;
    case IreneKey_KeypadMultiply: return ImGuiKey_KeypadMultiply;
    case IreneKey_KeypadSubtract: return ImGuiKey_KeypadSubtract;
    case IreneKey_KeypadAdd: return ImGuiKey_KeypadAdd;
    case IreneKey_KeypadEnter: return ImGuiKey_KeypadEnter;
    case IreneKey_KeypadEqual: return ImGuiKey_KeypadEqual;
    case IreneKey_LeftShift: return ImGuiKey_LeftShift;
    case IreneKey_LeftCtrl: return ImGuiKey_LeftCtrl;
    case IreneKey_LeftAlt: return ImGuiKey_LeftAlt;
    case IreneKey_LeftSuper: return ImGuiKey_LeftSuper;
    case IreneKey_RightShift: return ImGuiKey_RightShift;
    case IreneKey_RightCtrl: return ImGuiKey_RightCtrl;
    case IreneKey_RightAlt: return ImGuiKey_RightAlt;
    case IreneKey_RightSuper: return ImGuiKey_RightSuper;
    case IreneKey_Menu: return ImGuiKey_Menu;
    case IreneKey_0: return ImGuiKey_0;
    case IreneKey_1: return ImGuiKey_1;
    case IreneKey_2: return ImGuiKey_2;
    case IreneKey_3: return ImGuiKey_3;
    case IreneKey_4: return ImGuiKey_4;
    case IreneKey_5: return ImGuiKey_5;
    case IreneKey_6: return ImGuiKey_6;
    case IreneKey_7: return ImGuiKey_7;
    case IreneKey_8: return ImGuiKey_8;
    case IreneKey_9: return ImGuiKey_9;
    case IreneKey_A: return ImGuiKey_A;
    case IreneKey_B: return ImGuiKey_B;
    case IreneKey_C: return ImGuiKey_C;
    case IreneKey_D: return ImGuiKey_D;
    case IreneKey_E: return ImGuiKey_E;
    case IreneKey_F: return ImGuiKey_F;
    case IreneKey_G: return ImGuiKey_G;
    case IreneKey_H: return ImGuiKey_H;
    case IreneKey_I: return ImGuiKey_I;
    case IreneKey_J: return ImGuiKey_J;
    case IreneKey_K: return ImGuiKey_K;
    case IreneKey_L: return ImGuiKey_L;
    case IreneKey_M: return ImGuiKey_M;
    case IreneKey_N: return ImGuiKey_N;
    case IreneKey_O: return ImGuiKey_O;
    case IreneKey_P: return ImGuiKey_P;
    case IreneKey_Q: return ImGuiKey_Q;
    case IreneKey_R: return ImGuiKey_R;
    case IreneKey_S: return ImGuiKey_S;
    case IreneKey_T: return ImGuiKey_T;
    case IreneKey_U: return ImGuiKey_U;
    case IreneKey_V: return ImGuiKey_V;
    case IreneKey_W: return ImGuiKey_W;
    case IreneKey_X: return ImGuiKey_X;
    case IreneKey_Y: return ImGuiKey_Y;
    case IreneKey_Z: return ImGuiKey_Z;
    case IreneKey_F1: return ImGuiKey_F1;
    case IreneKey_F2: return ImGuiKey_F2;
    case IreneKey_F3: return ImGuiKey_F3;
    case IreneKey_F4: return ImGuiKey_F4;
    case IreneKey_F5: return ImGuiKey_F5;
    case IreneKey_F6: return ImGuiKey_F6;
    case IreneKey_F7: return ImGuiKey_F7;
    case IreneKey_F8: return ImGuiKey_F8;
    case IreneKey_F9: return ImGuiKey_F9;
    case IreneKey_F10: return ImGuiKey_F10;
    case IreneKey_F11: return ImGuiKey_F11;
    case IreneKey_F12: return ImGuiKey_F12;
    default: return ImGuiKey_None;
    }
}