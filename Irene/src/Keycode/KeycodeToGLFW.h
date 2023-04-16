#pragma once

#include "IreneKeycode.h"
#include "GLFW/glfw3.h"


static int Key_IreneToGLFW(int key)
{
    switch (key)
    {
    case IreneKey_Tab: return  GLFW_KEY_TAB;
    case IreneKey_RightArrow: return  GLFW_KEY_RIGHT;
    case IreneKey_UpArrow: return  GLFW_KEY_UP;
    case IreneKey_DownArrow: return  GLFW_KEY_DOWN;
    case IreneKey_PageUp: return  GLFW_KEY_PAGE_UP;
    case IreneKey_PageDown: return  GLFW_KEY_PAGE_DOWN;
    case IreneKey_Home: return  GLFW_KEY_HOME;
    case IreneKey_End: return  GLFW_KEY_END;
    case IreneKey_Insert: return GLFW_KEY_INSERT;
    case IreneKey_Delete: return GLFW_KEY_DELETE;
    case IreneKey_Backspace: return GLFW_KEY_BACKSPACE;
    case IreneKey_Space: return GLFW_KEY_SPACE;
    case IreneKey_Enter: return GLFW_KEY_ENTER;
    case IreneKey_Escape: return GLFW_KEY_ESCAPE;
    case IreneKey_Apostrophe: return GLFW_KEY_APOSTROPHE;
    case IreneKey_Comma: return GLFW_KEY_COMMA;
    case IreneKey_Minus: return GLFW_KEY_MINUS;
    case IreneKey_Period: return GLFW_KEY_PERIOD;
    case IreneKey_Slash: return GLFW_KEY_SLASH;
    case IreneKey_Semicolon: return GLFW_KEY_SEMICOLON;
    case IreneKey_Equal: return GLFW_KEY_EQUAL;
    case IreneKey_LeftBracket: return GLFW_KEY_LEFT_BRACKET;
    case IreneKey_Backslash: return GLFW_KEY_BACKSLASH;
    case IreneKey_RightBracket: return GLFW_KEY_RIGHT_BRACKET;
    case IreneKey_GraveAccent: return GLFW_KEY_GRAVE_ACCENT;
    case IreneKey_CapsLock: return GLFW_KEY_CAPS_LOCK;
    case IreneKey_ScrollLock: return GLFW_KEY_SCROLL_LOCK;
    case IreneKey_NumLock: return GLFW_KEY_NUM_LOCK;
    case IreneKey_PrintScreen: return GLFW_KEY_PRINT_SCREEN;
    case IreneKey_Pause: return GLFW_KEY_PAUSE;
    case IreneKey_Keypad0: return GLFW_KEY_KP_0;
    case IreneKey_Keypad1: return GLFW_KEY_KP_1;
    case IreneKey_Keypad2: return GLFW_KEY_KP_2;
    case IreneKey_Keypad3: return GLFW_KEY_KP_3;
    case IreneKey_Keypad4: return GLFW_KEY_KP_4;
    case IreneKey_Keypad5: return GLFW_KEY_KP_5;
    case IreneKey_Keypad6: return GLFW_KEY_KP_6;
    case IreneKey_Keypad7: return GLFW_KEY_KP_7;
    case IreneKey_Keypad8: return GLFW_KEY_KP_8;
    case IreneKey_Keypad9: return GLFW_KEY_KP_9;
    case IreneKey_KeypadDecimal: return GLFW_KEY_KP_DECIMAL;
    case IreneKey_KeypadDivide: return GLFW_KEY_KP_DIVIDE;
    case IreneKey_KeypadMultiply: return GLFW_KEY_KP_MULTIPLY;
    case IreneKey_KeypadSubtract: return GLFW_KEY_KP_SUBTRACT;
    case IreneKey_KeypadAdd: return GLFW_KEY_KP_ADD;
    case IreneKey_KeypadEnter: return GLFW_KEY_KP_ENTER;
    case IreneKey_KeypadEqual: return GLFW_KEY_KP_EQUAL;
    case IreneKey_LeftShift: return GLFW_KEY_LEFT_SHIFT;
    case IreneKey_LeftCtrl: return GLFW_KEY_LEFT_CONTROL;
    case IreneKey_LeftAlt: return GLFW_KEY_LEFT_ALT;
    case IreneKey_LeftSuper: return GLFW_KEY_LEFT_SUPER;
    case IreneKey_RightShift: return GLFW_KEY_RIGHT_SHIFT;
    case IreneKey_RightCtrl: return GLFW_KEY_RIGHT_CONTROL;
    case IreneKey_RightAlt: return GLFW_KEY_RIGHT_ALT;
    case IreneKey_RightSuper: return GLFW_KEY_RIGHT_SUPER;
    case IreneKey_Menu: return GLFW_KEY_MENU;
    case IreneKey_0: return GLFW_KEY_0;
    case IreneKey_1: return GLFW_KEY_1;
    case IreneKey_2: return GLFW_KEY_2;
    case IreneKey_3: return GLFW_KEY_3;
    case IreneKey_4: return GLFW_KEY_4;
    case IreneKey_5: return GLFW_KEY_5;
    case IreneKey_6: return GLFW_KEY_6;
    case IreneKey_7: return GLFW_KEY_7;
    case IreneKey_8: return GLFW_KEY_8;
    case IreneKey_9: return GLFW_KEY_9;
    case IreneKey_A: return GLFW_KEY_A;
    case IreneKey_B: return GLFW_KEY_B;
    case IreneKey_C: return GLFW_KEY_C;
    case IreneKey_D: return GLFW_KEY_D;
    case IreneKey_E: return GLFW_KEY_E;
    case IreneKey_F: return GLFW_KEY_F;
    case IreneKey_G: return GLFW_KEY_G;
    case IreneKey_H: return GLFW_KEY_H;
    case IreneKey_I: return GLFW_KEY_I;
    case IreneKey_J: return GLFW_KEY_J;
    case IreneKey_K: return GLFW_KEY_K;
    case IreneKey_L: return GLFW_KEY_L;
    case IreneKey_M: return GLFW_KEY_M;
    case IreneKey_N: return GLFW_KEY_N;
    case IreneKey_O: return GLFW_KEY_O;
    case IreneKey_P: return GLFW_KEY_P;
    case IreneKey_Q: return GLFW_KEY_Q;
    case IreneKey_R: return GLFW_KEY_R;
    case IreneKey_S: return GLFW_KEY_S;
    case IreneKey_T: return GLFW_KEY_T;
    case IreneKey_U: return GLFW_KEY_U;
    case IreneKey_V: return GLFW_KEY_V;
    case IreneKey_W: return GLFW_KEY_W;
    case IreneKey_X: return GLFW_KEY_X;
    case IreneKey_Y: return GLFW_KEY_Y;
    case IreneKey_Z: return GLFW_KEY_Z;
    case IreneKey_F1: return GLFW_KEY_F1;
    case IreneKey_F2: return GLFW_KEY_F2;
    case IreneKey_F3: return GLFW_KEY_F3;
    case IreneKey_F4: return GLFW_KEY_F4;
    case IreneKey_F5: return GLFW_KEY_F5;
    case IreneKey_F6: return GLFW_KEY_F6;
    case IreneKey_F7: return GLFW_KEY_F7;
    case IreneKey_F8: return GLFW_KEY_F8;
    case IreneKey_F9: return GLFW_KEY_F9;
    case IreneKey_F10: return GLFW_KEY_F10;
    case IreneKey_F11: return GLFW_KEY_F11;
    case IreneKey_F12: return GLFW_KEY_F12;
    default: return GLFW_KEY_UNKNOWN;
    }
}


