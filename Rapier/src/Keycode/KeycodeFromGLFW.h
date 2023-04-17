#pragma once

#include "RapierKeycode.h"
#include "GLFW/glfw3.h"


static RapierKey Key_GLFWToRapier(int key)
{
    switch (key)
    {
    case GLFW_KEY_TAB: return RapierKey_Tab;
    case GLFW_KEY_LEFT: return RapierKey_LeftArrow;
    case GLFW_KEY_RIGHT: return RapierKey_RightArrow;
    case GLFW_KEY_UP: return RapierKey_UpArrow;
    case GLFW_KEY_DOWN: return RapierKey_DownArrow;
    case GLFW_KEY_PAGE_UP: return RapierKey_PageUp;
    case GLFW_KEY_PAGE_DOWN: return RapierKey_PageDown;
    case GLFW_KEY_HOME: return RapierKey_Home;
    case GLFW_KEY_END: return RapierKey_End;
    case GLFW_KEY_INSERT: return RapierKey_Insert;
    case GLFW_KEY_DELETE: return RapierKey_Delete;
    case GLFW_KEY_BACKSPACE: return RapierKey_Backspace;
    case GLFW_KEY_SPACE: return RapierKey_Space;
    case GLFW_KEY_ENTER: return RapierKey_Enter;
    case GLFW_KEY_ESCAPE: return RapierKey_Escape;
    case GLFW_KEY_APOSTROPHE: return RapierKey_Apostrophe;
    case GLFW_KEY_COMMA: return RapierKey_Comma;
    case GLFW_KEY_MINUS: return RapierKey_Minus;
    case GLFW_KEY_PERIOD: return RapierKey_Period;
    case GLFW_KEY_SLASH: return RapierKey_Slash;
    case GLFW_KEY_SEMICOLON: return RapierKey_Semicolon;
    case GLFW_KEY_EQUAL: return RapierKey_Equal;
    case GLFW_KEY_LEFT_BRACKET: return RapierKey_LeftBracket;
    case GLFW_KEY_BACKSLASH: return RapierKey_Backslash;
    case GLFW_KEY_RIGHT_BRACKET: return RapierKey_RightBracket;
    case GLFW_KEY_GRAVE_ACCENT: return RapierKey_GraveAccent;
    case GLFW_KEY_CAPS_LOCK: return RapierKey_CapsLock;
    case GLFW_KEY_SCROLL_LOCK: return RapierKey_ScrollLock;
    case GLFW_KEY_NUM_LOCK: return RapierKey_NumLock;
    case GLFW_KEY_PRINT_SCREEN: return RapierKey_PrintScreen;
    case GLFW_KEY_PAUSE: return RapierKey_Pause;
    case GLFW_KEY_KP_0: return RapierKey_Keypad0;
    case GLFW_KEY_KP_1: return RapierKey_Keypad1;
    case GLFW_KEY_KP_2: return RapierKey_Keypad2;
    case GLFW_KEY_KP_3: return RapierKey_Keypad3;
    case GLFW_KEY_KP_4: return RapierKey_Keypad4;
    case GLFW_KEY_KP_5: return RapierKey_Keypad5;
    case GLFW_KEY_KP_6: return RapierKey_Keypad6;
    case GLFW_KEY_KP_7: return RapierKey_Keypad7;
    case GLFW_KEY_KP_8: return RapierKey_Keypad8;
    case GLFW_KEY_KP_9: return RapierKey_Keypad9;
    case GLFW_KEY_KP_DECIMAL: return RapierKey_KeypadDecimal;
    case GLFW_KEY_KP_DIVIDE: return RapierKey_KeypadDivide;
    case GLFW_KEY_KP_MULTIPLY: return RapierKey_KeypadMultiply;
    case GLFW_KEY_KP_SUBTRACT: return RapierKey_KeypadSubtract;
    case GLFW_KEY_KP_ADD: return RapierKey_KeypadAdd;
    case GLFW_KEY_KP_ENTER: return RapierKey_KeypadEnter;
    case GLFW_KEY_KP_EQUAL: return RapierKey_KeypadEqual;
    case GLFW_KEY_LEFT_SHIFT: return RapierKey_LeftShift;
    case GLFW_KEY_LEFT_CONTROL: return RapierKey_LeftCtrl;
    case GLFW_KEY_LEFT_ALT: return RapierKey_LeftAlt;
    case GLFW_KEY_LEFT_SUPER: return RapierKey_LeftSuper;
    case GLFW_KEY_RIGHT_SHIFT: return RapierKey_RightShift;
    case GLFW_KEY_RIGHT_CONTROL: return RapierKey_RightCtrl;
    case GLFW_KEY_RIGHT_ALT: return RapierKey_RightAlt;
    case GLFW_KEY_RIGHT_SUPER: return RapierKey_RightSuper;
    case GLFW_KEY_MENU: return RapierKey_Menu;
    case GLFW_KEY_0: return RapierKey_0;
    case GLFW_KEY_1: return RapierKey_1;
    case GLFW_KEY_2: return RapierKey_2;
    case GLFW_KEY_3: return RapierKey_3;
    case GLFW_KEY_4: return RapierKey_4;
    case GLFW_KEY_5: return RapierKey_5;
    case GLFW_KEY_6: return RapierKey_6;
    case GLFW_KEY_7: return RapierKey_7;
    case GLFW_KEY_8: return RapierKey_8;
    case GLFW_KEY_9: return RapierKey_9;
    case GLFW_KEY_A: return RapierKey_A;
    case GLFW_KEY_B: return RapierKey_B;
    case GLFW_KEY_C: return RapierKey_C;
    case GLFW_KEY_D: return RapierKey_D;
    case GLFW_KEY_E: return RapierKey_E;
    case GLFW_KEY_F: return RapierKey_F;
    case GLFW_KEY_G: return RapierKey_G;
    case GLFW_KEY_H: return RapierKey_H;
    case GLFW_KEY_I: return RapierKey_I;
    case GLFW_KEY_J: return RapierKey_J;
    case GLFW_KEY_K: return RapierKey_K;
    case GLFW_KEY_L: return RapierKey_L;
    case GLFW_KEY_M: return RapierKey_M;
    case GLFW_KEY_N: return RapierKey_N;
    case GLFW_KEY_O: return RapierKey_O;
    case GLFW_KEY_P: return RapierKey_P;
    case GLFW_KEY_Q: return RapierKey_Q;
    case GLFW_KEY_R: return RapierKey_R;
    case GLFW_KEY_S: return RapierKey_S;
    case GLFW_KEY_T: return RapierKey_T;
    case GLFW_KEY_U: return RapierKey_U;
    case GLFW_KEY_V: return RapierKey_V;
    case GLFW_KEY_W: return RapierKey_W;
    case GLFW_KEY_X: return RapierKey_X;
    case GLFW_KEY_Y: return RapierKey_Y;
    case GLFW_KEY_Z: return RapierKey_Z;
    case GLFW_KEY_F1: return RapierKey_F1;
    case GLFW_KEY_F2: return RapierKey_F2;
    case GLFW_KEY_F3: return RapierKey_F3;
    case GLFW_KEY_F4: return RapierKey_F4;
    case GLFW_KEY_F5: return RapierKey_F5;
    case GLFW_KEY_F6: return RapierKey_F6;
    case GLFW_KEY_F7: return RapierKey_F7;
    case GLFW_KEY_F8: return RapierKey_F8;
    case GLFW_KEY_F9: return RapierKey_F9;
    case GLFW_KEY_F10: return RapierKey_F10;
    case GLFW_KEY_F11: return RapierKey_F11;
    case GLFW_KEY_F12: return RapierKey_F12;
    default: return RapierKey_None;
    }
}


