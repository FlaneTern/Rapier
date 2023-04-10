#pragma once

#include "IreneKeycode.h"
#include "GLFW/glfw3.h"


static IRENEKey Key_GLFWToIRENE(int key)
{
    switch (key)
    {
    case GLFW_KEY_TAB: return IRENEKey_Tab;
    case GLFW_KEY_LEFT: return IRENEKey_LeftArrow;
    case GLFW_KEY_RIGHT: return IRENEKey_RightArrow;
    case GLFW_KEY_UP: return IRENEKey_UpArrow;
    case GLFW_KEY_DOWN: return IRENEKey_DownArrow;
    case GLFW_KEY_PAGE_UP: return IRENEKey_PageUp;
    case GLFW_KEY_PAGE_DOWN: return IRENEKey_PageDown;
    case GLFW_KEY_HOME: return IRENEKey_Home;
    case GLFW_KEY_END: return IRENEKey_End;
    case GLFW_KEY_INSERT: return IRENEKey_Insert;
    case GLFW_KEY_DELETE: return IRENEKey_Delete;
    case GLFW_KEY_BACKSPACE: return IRENEKey_Backspace;
    case GLFW_KEY_SPACE: return IRENEKey_Space;
    case GLFW_KEY_ENTER: return IRENEKey_Enter;
    case GLFW_KEY_ESCAPE: return IRENEKey_Escape;
    case GLFW_KEY_APOSTROPHE: return IRENEKey_Apostrophe;
    case GLFW_KEY_COMMA: return IRENEKey_Comma;
    case GLFW_KEY_MINUS: return IRENEKey_Minus;
    case GLFW_KEY_PERIOD: return IRENEKey_Period;
    case GLFW_KEY_SLASH: return IRENEKey_Slash;
    case GLFW_KEY_SEMICOLON: return IRENEKey_Semicolon;
    case GLFW_KEY_EQUAL: return IRENEKey_Equal;
    case GLFW_KEY_LEFT_BRACKET: return IRENEKey_LeftBracket;
    case GLFW_KEY_BACKSLASH: return IRENEKey_Backslash;
    case GLFW_KEY_RIGHT_BRACKET: return IRENEKey_RightBracket;
    case GLFW_KEY_GRAVE_ACCENT: return IRENEKey_GraveAccent;
    case GLFW_KEY_CAPS_LOCK: return IRENEKey_CapsLock;
    case GLFW_KEY_SCROLL_LOCK: return IRENEKey_ScrollLock;
    case GLFW_KEY_NUM_LOCK: return IRENEKey_NumLock;
    case GLFW_KEY_PRINT_SCREEN: return IRENEKey_PrintScreen;
    case GLFW_KEY_PAUSE: return IRENEKey_Pause;
    case GLFW_KEY_KP_0: return IRENEKey_Keypad0;
    case GLFW_KEY_KP_1: return IRENEKey_Keypad1;
    case GLFW_KEY_KP_2: return IRENEKey_Keypad2;
    case GLFW_KEY_KP_3: return IRENEKey_Keypad3;
    case GLFW_KEY_KP_4: return IRENEKey_Keypad4;
    case GLFW_KEY_KP_5: return IRENEKey_Keypad5;
    case GLFW_KEY_KP_6: return IRENEKey_Keypad6;
    case GLFW_KEY_KP_7: return IRENEKey_Keypad7;
    case GLFW_KEY_KP_8: return IRENEKey_Keypad8;
    case GLFW_KEY_KP_9: return IRENEKey_Keypad9;
    case GLFW_KEY_KP_DECIMAL: return IRENEKey_KeypadDecimal;
    case GLFW_KEY_KP_DIVIDE: return IRENEKey_KeypadDivide;
    case GLFW_KEY_KP_MULTIPLY: return IRENEKey_KeypadMultiply;
    case GLFW_KEY_KP_SUBTRACT: return IRENEKey_KeypadSubtract;
    case GLFW_KEY_KP_ADD: return IRENEKey_KeypadAdd;
    case GLFW_KEY_KP_ENTER: return IRENEKey_KeypadEnter;
    case GLFW_KEY_KP_EQUAL: return IRENEKey_KeypadEqual;
    case GLFW_KEY_LEFT_SHIFT: return IRENEKey_LeftShift;
    case GLFW_KEY_LEFT_CONTROL: return IRENEKey_LeftCtrl;
    case GLFW_KEY_LEFT_ALT: return IRENEKey_LeftAlt;
    case GLFW_KEY_LEFT_SUPER: return IRENEKey_LeftSuper;
    case GLFW_KEY_RIGHT_SHIFT: return IRENEKey_RightShift;
    case GLFW_KEY_RIGHT_CONTROL: return IRENEKey_RightCtrl;
    case GLFW_KEY_RIGHT_ALT: return IRENEKey_RightAlt;
    case GLFW_KEY_RIGHT_SUPER: return IRENEKey_RightSuper;
    case GLFW_KEY_MENU: return IRENEKey_Menu;
    case GLFW_KEY_0: return IRENEKey_0;
    case GLFW_KEY_1: return IRENEKey_1;
    case GLFW_KEY_2: return IRENEKey_2;
    case GLFW_KEY_3: return IRENEKey_3;
    case GLFW_KEY_4: return IRENEKey_4;
    case GLFW_KEY_5: return IRENEKey_5;
    case GLFW_KEY_6: return IRENEKey_6;
    case GLFW_KEY_7: return IRENEKey_7;
    case GLFW_KEY_8: return IRENEKey_8;
    case GLFW_KEY_9: return IRENEKey_9;
    case GLFW_KEY_A: return IRENEKey_A;
    case GLFW_KEY_B: return IRENEKey_B;
    case GLFW_KEY_C: return IRENEKey_C;
    case GLFW_KEY_D: return IRENEKey_D;
    case GLFW_KEY_E: return IRENEKey_E;
    case GLFW_KEY_F: return IRENEKey_F;
    case GLFW_KEY_G: return IRENEKey_G;
    case GLFW_KEY_H: return IRENEKey_H;
    case GLFW_KEY_I: return IRENEKey_I;
    case GLFW_KEY_J: return IRENEKey_J;
    case GLFW_KEY_K: return IRENEKey_K;
    case GLFW_KEY_L: return IRENEKey_L;
    case GLFW_KEY_M: return IRENEKey_M;
    case GLFW_KEY_N: return IRENEKey_N;
    case GLFW_KEY_O: return IRENEKey_O;
    case GLFW_KEY_P: return IRENEKey_P;
    case GLFW_KEY_Q: return IRENEKey_Q;
    case GLFW_KEY_R: return IRENEKey_R;
    case GLFW_KEY_S: return IRENEKey_S;
    case GLFW_KEY_T: return IRENEKey_T;
    case GLFW_KEY_U: return IRENEKey_U;
    case GLFW_KEY_V: return IRENEKey_V;
    case GLFW_KEY_W: return IRENEKey_W;
    case GLFW_KEY_X: return IRENEKey_X;
    case GLFW_KEY_Y: return IRENEKey_Y;
    case GLFW_KEY_Z: return IRENEKey_Z;
    case GLFW_KEY_F1: return IRENEKey_F1;
    case GLFW_KEY_F2: return IRENEKey_F2;
    case GLFW_KEY_F3: return IRENEKey_F3;
    case GLFW_KEY_F4: return IRENEKey_F4;
    case GLFW_KEY_F5: return IRENEKey_F5;
    case GLFW_KEY_F6: return IRENEKey_F6;
    case GLFW_KEY_F7: return IRENEKey_F7;
    case GLFW_KEY_F8: return IRENEKey_F8;
    case GLFW_KEY_F9: return IRENEKey_F9;
    case GLFW_KEY_F10: return IRENEKey_F10;
    case GLFW_KEY_F11: return IRENEKey_F11;
    case GLFW_KEY_F12: return IRENEKey_F12;
    default: return IRENEKey_None;
    }
}


