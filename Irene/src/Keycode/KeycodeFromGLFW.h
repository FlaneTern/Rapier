#pragma once

#include "IreneKeycode.h"
#include "GLFW/glfw3.h"


static IreneKey Key_GLFWToIrene(int key)
{
    switch (key)
    {
    case GLFW_KEY_TAB: return IreneKey_Tab;
    case GLFW_KEY_LEFT: return IreneKey_LeftArrow;
    case GLFW_KEY_RIGHT: return IreneKey_RightArrow;
    case GLFW_KEY_UP: return IreneKey_UpArrow;
    case GLFW_KEY_DOWN: return IreneKey_DownArrow;
    case GLFW_KEY_PAGE_UP: return IreneKey_PageUp;
    case GLFW_KEY_PAGE_DOWN: return IreneKey_PageDown;
    case GLFW_KEY_HOME: return IreneKey_Home;
    case GLFW_KEY_END: return IreneKey_End;
    case GLFW_KEY_INSERT: return IreneKey_Insert;
    case GLFW_KEY_DELETE: return IreneKey_Delete;
    case GLFW_KEY_BACKSPACE: return IreneKey_Backspace;
    case GLFW_KEY_SPACE: return IreneKey_Space;
    case GLFW_KEY_ENTER: return IreneKey_Enter;
    case GLFW_KEY_ESCAPE: return IreneKey_Escape;
    case GLFW_KEY_APOSTROPHE: return IreneKey_Apostrophe;
    case GLFW_KEY_COMMA: return IreneKey_Comma;
    case GLFW_KEY_MINUS: return IreneKey_Minus;
    case GLFW_KEY_PERIOD: return IreneKey_Period;
    case GLFW_KEY_SLASH: return IreneKey_Slash;
    case GLFW_KEY_SEMICOLON: return IreneKey_Semicolon;
    case GLFW_KEY_EQUAL: return IreneKey_Equal;
    case GLFW_KEY_LEFT_BRACKET: return IreneKey_LeftBracket;
    case GLFW_KEY_BACKSLASH: return IreneKey_Backslash;
    case GLFW_KEY_RIGHT_BRACKET: return IreneKey_RightBracket;
    case GLFW_KEY_GRAVE_ACCENT: return IreneKey_GraveAccent;
    case GLFW_KEY_CAPS_LOCK: return IreneKey_CapsLock;
    case GLFW_KEY_SCROLL_LOCK: return IreneKey_ScrollLock;
    case GLFW_KEY_NUM_LOCK: return IreneKey_NumLock;
    case GLFW_KEY_PRINT_SCREEN: return IreneKey_PrintScreen;
    case GLFW_KEY_PAUSE: return IreneKey_Pause;
    case GLFW_KEY_KP_0: return IreneKey_Keypad0;
    case GLFW_KEY_KP_1: return IreneKey_Keypad1;
    case GLFW_KEY_KP_2: return IreneKey_Keypad2;
    case GLFW_KEY_KP_3: return IreneKey_Keypad3;
    case GLFW_KEY_KP_4: return IreneKey_Keypad4;
    case GLFW_KEY_KP_5: return IreneKey_Keypad5;
    case GLFW_KEY_KP_6: return IreneKey_Keypad6;
    case GLFW_KEY_KP_7: return IreneKey_Keypad7;
    case GLFW_KEY_KP_8: return IreneKey_Keypad8;
    case GLFW_KEY_KP_9: return IreneKey_Keypad9;
    case GLFW_KEY_KP_DECIMAL: return IreneKey_KeypadDecimal;
    case GLFW_KEY_KP_DIVIDE: return IreneKey_KeypadDivide;
    case GLFW_KEY_KP_MULTIPLY: return IreneKey_KeypadMultiply;
    case GLFW_KEY_KP_SUBTRACT: return IreneKey_KeypadSubtract;
    case GLFW_KEY_KP_ADD: return IreneKey_KeypadAdd;
    case GLFW_KEY_KP_ENTER: return IreneKey_KeypadEnter;
    case GLFW_KEY_KP_EQUAL: return IreneKey_KeypadEqual;
    case GLFW_KEY_LEFT_SHIFT: return IreneKey_LeftShift;
    case GLFW_KEY_LEFT_CONTROL: return IreneKey_LeftCtrl;
    case GLFW_KEY_LEFT_ALT: return IreneKey_LeftAlt;
    case GLFW_KEY_LEFT_SUPER: return IreneKey_LeftSuper;
    case GLFW_KEY_RIGHT_SHIFT: return IreneKey_RightShift;
    case GLFW_KEY_RIGHT_CONTROL: return IreneKey_RightCtrl;
    case GLFW_KEY_RIGHT_ALT: return IreneKey_RightAlt;
    case GLFW_KEY_RIGHT_SUPER: return IreneKey_RightSuper;
    case GLFW_KEY_MENU: return IreneKey_Menu;
    case GLFW_KEY_0: return IreneKey_0;
    case GLFW_KEY_1: return IreneKey_1;
    case GLFW_KEY_2: return IreneKey_2;
    case GLFW_KEY_3: return IreneKey_3;
    case GLFW_KEY_4: return IreneKey_4;
    case GLFW_KEY_5: return IreneKey_5;
    case GLFW_KEY_6: return IreneKey_6;
    case GLFW_KEY_7: return IreneKey_7;
    case GLFW_KEY_8: return IreneKey_8;
    case GLFW_KEY_9: return IreneKey_9;
    case GLFW_KEY_A: return IreneKey_A;
    case GLFW_KEY_B: return IreneKey_B;
    case GLFW_KEY_C: return IreneKey_C;
    case GLFW_KEY_D: return IreneKey_D;
    case GLFW_KEY_E: return IreneKey_E;
    case GLFW_KEY_F: return IreneKey_F;
    case GLFW_KEY_G: return IreneKey_G;
    case GLFW_KEY_H: return IreneKey_H;
    case GLFW_KEY_I: return IreneKey_I;
    case GLFW_KEY_J: return IreneKey_J;
    case GLFW_KEY_K: return IreneKey_K;
    case GLFW_KEY_L: return IreneKey_L;
    case GLFW_KEY_M: return IreneKey_M;
    case GLFW_KEY_N: return IreneKey_N;
    case GLFW_KEY_O: return IreneKey_O;
    case GLFW_KEY_P: return IreneKey_P;
    case GLFW_KEY_Q: return IreneKey_Q;
    case GLFW_KEY_R: return IreneKey_R;
    case GLFW_KEY_S: return IreneKey_S;
    case GLFW_KEY_T: return IreneKey_T;
    case GLFW_KEY_U: return IreneKey_U;
    case GLFW_KEY_V: return IreneKey_V;
    case GLFW_KEY_W: return IreneKey_W;
    case GLFW_KEY_X: return IreneKey_X;
    case GLFW_KEY_Y: return IreneKey_Y;
    case GLFW_KEY_Z: return IreneKey_Z;
    case GLFW_KEY_F1: return IreneKey_F1;
    case GLFW_KEY_F2: return IreneKey_F2;
    case GLFW_KEY_F3: return IreneKey_F3;
    case GLFW_KEY_F4: return IreneKey_F4;
    case GLFW_KEY_F5: return IreneKey_F5;
    case GLFW_KEY_F6: return IreneKey_F6;
    case GLFW_KEY_F7: return IreneKey_F7;
    case GLFW_KEY_F8: return IreneKey_F8;
    case GLFW_KEY_F9: return IreneKey_F9;
    case GLFW_KEY_F10: return IreneKey_F10;
    case GLFW_KEY_F11: return IreneKey_F11;
    case GLFW_KEY_F12: return IreneKey_F12;
    default: return IreneKey_None;
    }
}


