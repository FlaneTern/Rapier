#pragma once

#include "RapierKeycode.h"
#include "GLFW/glfw3.h"


static int Key_RapierToGLFW(int key)
{
    switch (key)
    {
    case RapierKey_Tab: return  GLFW_KEY_TAB;
    case RapierKey_LeftArrow: return  GLFW_KEY_LEFT;
    case RapierKey_RightArrow: return  GLFW_KEY_RIGHT;
    case RapierKey_UpArrow: return  GLFW_KEY_UP;
    case RapierKey_DownArrow: return  GLFW_KEY_DOWN;
    case RapierKey_PageUp: return  GLFW_KEY_PAGE_UP;
    case RapierKey_PageDown: return  GLFW_KEY_PAGE_DOWN;
    case RapierKey_Home: return  GLFW_KEY_HOME;
    case RapierKey_End: return  GLFW_KEY_END;
    case RapierKey_Insert: return GLFW_KEY_INSERT;
    case RapierKey_Delete: return GLFW_KEY_DELETE;
    case RapierKey_Backspace: return GLFW_KEY_BACKSPACE;
    case RapierKey_Space: return GLFW_KEY_SPACE;
    case RapierKey_Enter: return GLFW_KEY_ENTER;
    case RapierKey_Escape: return GLFW_KEY_ESCAPE;
    case RapierKey_Apostrophe: return GLFW_KEY_APOSTROPHE;
    case RapierKey_Comma: return GLFW_KEY_COMMA;
    case RapierKey_Minus: return GLFW_KEY_MINUS;
    case RapierKey_Period: return GLFW_KEY_PERIOD;
    case RapierKey_Slash: return GLFW_KEY_SLASH;
    case RapierKey_Semicolon: return GLFW_KEY_SEMICOLON;
    case RapierKey_Equal: return GLFW_KEY_EQUAL;
    case RapierKey_LeftBracket: return GLFW_KEY_LEFT_BRACKET;
    case RapierKey_Backslash: return GLFW_KEY_BACKSLASH;
    case RapierKey_RightBracket: return GLFW_KEY_RIGHT_BRACKET;
    case RapierKey_GraveAccent: return GLFW_KEY_GRAVE_ACCENT;
    case RapierKey_CapsLock: return GLFW_KEY_CAPS_LOCK;
    case RapierKey_ScrollLock: return GLFW_KEY_SCROLL_LOCK;
    case RapierKey_NumLock: return GLFW_KEY_NUM_LOCK;
    case RapierKey_PrintScreen: return GLFW_KEY_PRINT_SCREEN;
    case RapierKey_Pause: return GLFW_KEY_PAUSE;
    case RapierKey_Keypad0: return GLFW_KEY_KP_0;
    case RapierKey_Keypad1: return GLFW_KEY_KP_1;
    case RapierKey_Keypad2: return GLFW_KEY_KP_2;
    case RapierKey_Keypad3: return GLFW_KEY_KP_3;
    case RapierKey_Keypad4: return GLFW_KEY_KP_4;
    case RapierKey_Keypad5: return GLFW_KEY_KP_5;
    case RapierKey_Keypad6: return GLFW_KEY_KP_6;
    case RapierKey_Keypad7: return GLFW_KEY_KP_7;
    case RapierKey_Keypad8: return GLFW_KEY_KP_8;
    case RapierKey_Keypad9: return GLFW_KEY_KP_9;
    case RapierKey_KeypadDecimal: return GLFW_KEY_KP_DECIMAL;
    case RapierKey_KeypadDivide: return GLFW_KEY_KP_DIVIDE;
    case RapierKey_KeypadMultiply: return GLFW_KEY_KP_MULTIPLY;
    case RapierKey_KeypadSubtract: return GLFW_KEY_KP_SUBTRACT;
    case RapierKey_KeypadAdd: return GLFW_KEY_KP_ADD;
    case RapierKey_KeypadEnter: return GLFW_KEY_KP_ENTER;
    case RapierKey_KeypadEqual: return GLFW_KEY_KP_EQUAL;
    case RapierKey_LeftShift: return GLFW_KEY_LEFT_SHIFT;
    case RapierKey_LeftCtrl: return GLFW_KEY_LEFT_CONTROL;
    case RapierKey_LeftAlt: return GLFW_KEY_LEFT_ALT;
    case RapierKey_LeftSuper: return GLFW_KEY_LEFT_SUPER;
    case RapierKey_RightShift: return GLFW_KEY_RIGHT_SHIFT;
    case RapierKey_RightCtrl: return GLFW_KEY_RIGHT_CONTROL;
    case RapierKey_RightAlt: return GLFW_KEY_RIGHT_ALT;
    case RapierKey_RightSuper: return GLFW_KEY_RIGHT_SUPER;
    case RapierKey_Menu: return GLFW_KEY_MENU;
    case RapierKey_0: return GLFW_KEY_0;
    case RapierKey_1: return GLFW_KEY_1;
    case RapierKey_2: return GLFW_KEY_2;
    case RapierKey_3: return GLFW_KEY_3;
    case RapierKey_4: return GLFW_KEY_4;
    case RapierKey_5: return GLFW_KEY_5;
    case RapierKey_6: return GLFW_KEY_6;
    case RapierKey_7: return GLFW_KEY_7;
    case RapierKey_8: return GLFW_KEY_8;
    case RapierKey_9: return GLFW_KEY_9;
    case RapierKey_A: return GLFW_KEY_A;
    case RapierKey_B: return GLFW_KEY_B;
    case RapierKey_C: return GLFW_KEY_C;
    case RapierKey_D: return GLFW_KEY_D;
    case RapierKey_E: return GLFW_KEY_E;
    case RapierKey_F: return GLFW_KEY_F;
    case RapierKey_G: return GLFW_KEY_G;
    case RapierKey_H: return GLFW_KEY_H;
    case RapierKey_I: return GLFW_KEY_I;
    case RapierKey_J: return GLFW_KEY_J;
    case RapierKey_K: return GLFW_KEY_K;
    case RapierKey_L: return GLFW_KEY_L;
    case RapierKey_M: return GLFW_KEY_M;
    case RapierKey_N: return GLFW_KEY_N;
    case RapierKey_O: return GLFW_KEY_O;
    case RapierKey_P: return GLFW_KEY_P;
    case RapierKey_Q: return GLFW_KEY_Q;
    case RapierKey_R: return GLFW_KEY_R;
    case RapierKey_S: return GLFW_KEY_S;
    case RapierKey_T: return GLFW_KEY_T;
    case RapierKey_U: return GLFW_KEY_U;
    case RapierKey_V: return GLFW_KEY_V;
    case RapierKey_W: return GLFW_KEY_W;
    case RapierKey_X: return GLFW_KEY_X;
    case RapierKey_Y: return GLFW_KEY_Y;
    case RapierKey_Z: return GLFW_KEY_Z;
    case RapierKey_F1: return GLFW_KEY_F1;
    case RapierKey_F2: return GLFW_KEY_F2;
    case RapierKey_F3: return GLFW_KEY_F3;
    case RapierKey_F4: return GLFW_KEY_F4;
    case RapierKey_F5: return GLFW_KEY_F5;
    case RapierKey_F6: return GLFW_KEY_F6;
    case RapierKey_F7: return GLFW_KEY_F7;
    case RapierKey_F8: return GLFW_KEY_F8;
    case RapierKey_F9: return GLFW_KEY_F9;
    case RapierKey_F10: return GLFW_KEY_F10;
    case RapierKey_F11: return GLFW_KEY_F11;
    case RapierKey_F12: return GLFW_KEY_F12;
    case RapierKey_MouseLeft:   return GLFW_MOUSE_BUTTON_1;
    case RapierKey_MouseRight:  return GLFW_MOUSE_BUTTON_2;
    case RapierKey_MouseMiddle: return GLFW_MOUSE_BUTTON_3;
    default: return GLFW_KEY_UNKNOWN;
    }
}


