#pragma once

#include "IreneKeycode.h"
#include "imgui.h"


static ImGuiKey Key_IRENEToImGui(int key)
{
    switch (key)
    {
    case IRENEKey_Tab: return ImGuiKey_Tab;
    case IRENEKey_LeftArrow: return ImGuiKey_LeftArrow;
    case IRENEKey_RightArrow: return ImGuiKey_RightArrow;
    case IRENEKey_UpArrow: return ImGuiKey_UpArrow;
    case IRENEKey_DownArrow: return ImGuiKey_DownArrow;
    case IRENEKey_PageUp: return ImGuiKey_PageUp;
    case IRENEKey_PageDown: return ImGuiKey_PageDown;
    case IRENEKey_Home: return ImGuiKey_Home;
    case IRENEKey_End: return ImGuiKey_End;
    case IRENEKey_Insert: return ImGuiKey_Insert;
    case IRENEKey_Delete: return ImGuiKey_Delete;
    case IRENEKey_Backspace: return ImGuiKey_Backspace;
    case IRENEKey_Space: return ImGuiKey_Space;
    case IRENEKey_Enter: return ImGuiKey_Enter;
    case IRENEKey_Escape: return ImGuiKey_Escape;
    case IRENEKey_Apostrophe: return ImGuiKey_Apostrophe;
    case IRENEKey_Comma: return ImGuiKey_Comma;
    case IRENEKey_Minus: return ImGuiKey_Minus;
    case IRENEKey_Period: return ImGuiKey_Period;
    case IRENEKey_Slash: return ImGuiKey_Slash;
    case IRENEKey_Semicolon: return ImGuiKey_Semicolon;
    case IRENEKey_Equal: return ImGuiKey_Equal;
    case IRENEKey_LeftBracket: return ImGuiKey_LeftBracket;
    case IRENEKey_Backslash: return ImGuiKey_Backslash;
    case IRENEKey_RightBracket: return ImGuiKey_RightBracket;
    case IRENEKey_GraveAccent: return ImGuiKey_GraveAccent;
    case IRENEKey_CapsLock: return ImGuiKey_CapsLock;
    case IRENEKey_ScrollLock: return ImGuiKey_ScrollLock;
    case IRENEKey_NumLock: return ImGuiKey_NumLock;
    case IRENEKey_PrintScreen: return ImGuiKey_PrintScreen;
    case IRENEKey_Pause: return ImGuiKey_Pause;
    case IRENEKey_Keypad0: return ImGuiKey_Keypad0;
    case IRENEKey_Keypad1: return ImGuiKey_Keypad1;
    case IRENEKey_Keypad2: return ImGuiKey_Keypad2;
    case IRENEKey_Keypad3: return ImGuiKey_Keypad3;
    case IRENEKey_Keypad4: return ImGuiKey_Keypad4;
    case IRENEKey_Keypad5: return ImGuiKey_Keypad5;
    case IRENEKey_Keypad6: return ImGuiKey_Keypad6;
    case IRENEKey_Keypad7: return ImGuiKey_Keypad7;
    case IRENEKey_Keypad8: return ImGuiKey_Keypad8;
    case IRENEKey_Keypad9: return ImGuiKey_Keypad9;
    case IRENEKey_KeypadDecimal: return ImGuiKey_KeypadDecimal;
    case IRENEKey_KeypadDivide: return ImGuiKey_KeypadDivide;
    case IRENEKey_KeypadMultiply: return ImGuiKey_KeypadMultiply;
    case IRENEKey_KeypadSubtract: return ImGuiKey_KeypadSubtract;
    case IRENEKey_KeypadAdd: return ImGuiKey_KeypadAdd;
    case IRENEKey_KeypadEnter: return ImGuiKey_KeypadEnter;
    case IRENEKey_KeypadEqual: return ImGuiKey_KeypadEqual;
    case IRENEKey_LeftShift: return ImGuiKey_LeftShift;
    case IRENEKey_LeftCtrl: return ImGuiKey_LeftCtrl;
    case IRENEKey_LeftAlt: return ImGuiKey_LeftAlt;
    case IRENEKey_LeftSuper: return ImGuiKey_LeftSuper;
    case IRENEKey_RightShift: return ImGuiKey_RightShift;
    case IRENEKey_RightCtrl: return ImGuiKey_RightCtrl;
    case IRENEKey_RightAlt: return ImGuiKey_RightAlt;
    case IRENEKey_RightSuper: return ImGuiKey_RightSuper;
    case IRENEKey_Menu: return ImGuiKey_Menu;
    case IRENEKey_0: return ImGuiKey_0;
    case IRENEKey_1: return ImGuiKey_1;
    case IRENEKey_2: return ImGuiKey_2;
    case IRENEKey_3: return ImGuiKey_3;
    case IRENEKey_4: return ImGuiKey_4;
    case IRENEKey_5: return ImGuiKey_5;
    case IRENEKey_6: return ImGuiKey_6;
    case IRENEKey_7: return ImGuiKey_7;
    case IRENEKey_8: return ImGuiKey_8;
    case IRENEKey_9: return ImGuiKey_9;
    case IRENEKey_A: return ImGuiKey_A;
    case IRENEKey_B: return ImGuiKey_B;
    case IRENEKey_C: return ImGuiKey_C;
    case IRENEKey_D: return ImGuiKey_D;
    case IRENEKey_E: return ImGuiKey_E;
    case IRENEKey_F: return ImGuiKey_F;
    case IRENEKey_G: return ImGuiKey_G;
    case IRENEKey_H: return ImGuiKey_H;
    case IRENEKey_I: return ImGuiKey_I;
    case IRENEKey_J: return ImGuiKey_J;
    case IRENEKey_K: return ImGuiKey_K;
    case IRENEKey_L: return ImGuiKey_L;
    case IRENEKey_M: return ImGuiKey_M;
    case IRENEKey_N: return ImGuiKey_N;
    case IRENEKey_O: return ImGuiKey_O;
    case IRENEKey_P: return ImGuiKey_P;
    case IRENEKey_Q: return ImGuiKey_Q;
    case IRENEKey_R: return ImGuiKey_R;
    case IRENEKey_S: return ImGuiKey_S;
    case IRENEKey_T: return ImGuiKey_T;
    case IRENEKey_U: return ImGuiKey_U;
    case IRENEKey_V: return ImGuiKey_V;
    case IRENEKey_W: return ImGuiKey_W;
    case IRENEKey_X: return ImGuiKey_X;
    case IRENEKey_Y: return ImGuiKey_Y;
    case IRENEKey_Z: return ImGuiKey_Z;
    case IRENEKey_F1: return ImGuiKey_F1;
    case IRENEKey_F2: return ImGuiKey_F2;
    case IRENEKey_F3: return ImGuiKey_F3;
    case IRENEKey_F4: return ImGuiKey_F4;
    case IRENEKey_F5: return ImGuiKey_F5;
    case IRENEKey_F6: return ImGuiKey_F6;
    case IRENEKey_F7: return ImGuiKey_F7;
    case IRENEKey_F8: return ImGuiKey_F8;
    case IRENEKey_F9: return ImGuiKey_F9;
    case IRENEKey_F10: return ImGuiKey_F10;
    case IRENEKey_F11: return ImGuiKey_F11;
    case IRENEKey_F12: return ImGuiKey_F12;
    default: return ImGuiKey_None;
    }
}