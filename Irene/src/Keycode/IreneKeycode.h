#pragma once

#include "ipch.h"

enum IRENEKey : int
{
    // Keyboard
    IRENEKey_None = 0,
    IRENEKey_Tab = 512,             // == IRENEKey_NamedKey_BEGIN
    IRENEKey_LeftArrow,
    IRENEKey_RightArrow,
    IRENEKey_UpArrow,
    IRENEKey_DownArrow,
    IRENEKey_PageUp,
    IRENEKey_PageDown,
    IRENEKey_Home,
    IRENEKey_End,
    IRENEKey_Insert,
    IRENEKey_Delete,
    IRENEKey_Backspace,
    IRENEKey_Space,
    IRENEKey_Enter,
    IRENEKey_Escape,
    IRENEKey_LeftCtrl, IRENEKey_LeftShift, IRENEKey_LeftAlt, IRENEKey_LeftSuper,
    IRENEKey_RightCtrl, IRENEKey_RightShift, IRENEKey_RightAlt, IRENEKey_RightSuper,
    IRENEKey_Menu,
    IRENEKey_0, IRENEKey_1, IRENEKey_2, IRENEKey_3, IRENEKey_4, IRENEKey_5, IRENEKey_6, IRENEKey_7, IRENEKey_8, IRENEKey_9,
    IRENEKey_A, IRENEKey_B, IRENEKey_C, IRENEKey_D, IRENEKey_E, IRENEKey_F, IRENEKey_G, IRENEKey_H, IRENEKey_I, IRENEKey_J,
    IRENEKey_K, IRENEKey_L, IRENEKey_M, IRENEKey_N, IRENEKey_O, IRENEKey_P, IRENEKey_Q, IRENEKey_R, IRENEKey_S, IRENEKey_T,
    IRENEKey_U, IRENEKey_V, IRENEKey_W, IRENEKey_X, IRENEKey_Y, IRENEKey_Z,
    IRENEKey_F1, IRENEKey_F2, IRENEKey_F3, IRENEKey_F4, IRENEKey_F5, IRENEKey_F6,
    IRENEKey_F7, IRENEKey_F8, IRENEKey_F9, IRENEKey_F10, IRENEKey_F11, IRENEKey_F12,
    IRENEKey_Apostrophe,        // '
    IRENEKey_Comma,             // ,
    IRENEKey_Minus,             // -
    IRENEKey_Period,            // .
    IRENEKey_Slash,             // /
    IRENEKey_Semicolon,         // ;
    IRENEKey_Equal,             // =
    IRENEKey_LeftBracket,       // [
    IRENEKey_Backslash,         // \ (this text inhibit multiline comment caused by backslash)
    IRENEKey_RightBracket,      // ]
    IRENEKey_GraveAccent,       // `
    IRENEKey_CapsLock,
    IRENEKey_ScrollLock,
    IRENEKey_NumLock,
    IRENEKey_PrintScreen,
    IRENEKey_Pause,
    IRENEKey_Keypad0, IRENEKey_Keypad1, IRENEKey_Keypad2, IRENEKey_Keypad3, IRENEKey_Keypad4,
    IRENEKey_Keypad5, IRENEKey_Keypad6, IRENEKey_Keypad7, IRENEKey_Keypad8, IRENEKey_Keypad9,
    IRENEKey_KeypadDecimal,
    IRENEKey_KeypadDivide,
    IRENEKey_KeypadMultiply,
    IRENEKey_KeypadSubtract,
    IRENEKey_KeypadAdd,
    IRENEKey_KeypadEnter,
    IRENEKey_KeypadEqual,

    // Gamepad (some of those are analog values, 0.0f to 1.0f)                          // NAVIGATION ACTION
    // (download controller mapping PNG/PSD at http://dearimgui.com/controls_sheets)
    IRENEKey_GamepadStart,          // Menu (Xbox)      + (Switch)   Start/Options (PS)
    IRENEKey_GamepadBack,           // View (Xbox)      - (Switch)   Share (PS)
    IRENEKey_GamepadFaceLeft,       // X (Xbox)         Y (Switch)   Square (PS)        // Tap: Toggle Menu. Hold: Windowing mode (Focus/Move/Resize windows)
    IRENEKey_GamepadFaceRight,      // B (Xbox)         A (Switch)   Circle (PS)        // Cancel / Close / Exit
    IRENEKey_GamepadFaceUp,         // Y (Xbox)         X (Switch)   Triangle (PS)      // Text Input / On-screen Keyboard
    IRENEKey_GamepadFaceDown,       // A (Xbox)         B (Switch)   Cross (PS)         // Activate / Open / Toggle / Tweak
    IRENEKey_GamepadDpadLeft,       // D-pad Left                                       // Move / Tweak / Resize Window (in Windowing mode)
    IRENEKey_GamepadDpadRight,      // D-pad Right                                      // Move / Tweak / Resize Window (in Windowing mode)
    IRENEKey_GamepadDpadUp,         // D-pad Up                                         // Move / Tweak / Resize Window (in Windowing mode)
    IRENEKey_GamepadDpadDown,       // D-pad Down                                       // Move / Tweak / Resize Window (in Windowing mode)
    IRENEKey_GamepadL1,             // L Bumper (Xbox)  L (Switch)   L1 (PS)            // Tweak Slower / Focus Previous (in Windowing mode)
    IRENEKey_GamepadR1,             // R Bumper (Xbox)  R (Switch)   R1 (PS)            // Tweak Faster / Focus Next (in Windowing mode)
    IRENEKey_GamepadL2,             // L Trig. (Xbox)   ZL (Switch)  L2 (PS) [Analog]
    IRENEKey_GamepadR2,             // R Trig. (Xbox)   ZR (Switch)  R2 (PS) [Analog]
    IRENEKey_GamepadL3,             // L Stick (Xbox)   L3 (Switch)  L3 (PS)
    IRENEKey_GamepadR3,             // R Stick (Xbox)   R3 (Switch)  R3 (PS)
    IRENEKey_GamepadLStickLeft,     // [Analog]                                         // Move Window (in Windowing mode)
    IRENEKey_GamepadLStickRight,    // [Analog]                                         // Move Window (in Windowing mode)
    IRENEKey_GamepadLStickUp,       // [Analog]                                         // Move Window (in Windowing mode)
    IRENEKey_GamepadLStickDown,     // [Analog]                                         // Move Window (in Windowing mode)
    IRENEKey_GamepadRStickLeft,     // [Analog]
    IRENEKey_GamepadRStickRight,    // [Analog]
    IRENEKey_GamepadRStickUp,       // [Analog]
    IRENEKey_GamepadRStickDown,     // [Analog]

    // Aliases: Mouse Buttons (auto-submitted from AddMouseButtonEvent() calls)
    // - This is mirroring the data also written to io.MouseDown[], io.MouseWheel, in a format allowing them to be accessed via standard key API.
    IRENEKey_MouseLeft, IRENEKey_MouseRight, IRENEKey_MouseMiddle, IRENEKey_MouseX1, IRENEKey_MouseX2, IRENEKey_MouseWheelX, IRENEKey_MouseWheelY,

    // [Internal] Reserved for mod storage
    IRENEKey_ReservedForModCtrl, IRENEKey_ReservedForModShift, IRENEKey_ReservedForModAlt, IRENEKey_ReservedForModSuper,
    IRENEKey_COUNT,

    // Keyboard Modifiers (explicitly submitted by backend via AddKeyEvent() calls)
    // - This is mirroring the data also written to io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper, in a format allowing
    //   them to be accessed via standard key API, allowing calls such as IsKeyPressed(), IsKeyReleased(), querying duration etc.
    // - Code polling every key (e.g. an interface to detect a key press for input mapping) might want to ignore those
    //   and prefer using the real keys (e.g. IRENEKey_LeftCtrl, IRENEKey_RightCtrl instead of ImGuiMod_Ctrl).
    // - In theory the value of keyboard modifiers should be roughly equivalent to a logical or of the equivalent left/right keys.
    //   In practice: it's complicated; mods are often provided from different sources. Keyboard layout, IME, sticky keys and
    //   backends tend to interfere and break that equivalence. The safer decision is to relay that ambiguity down to the end-user...
    IRENEMod_None = 0,
    IRENEMod_Ctrl = 1 << 12, // Ctrl
    IRENEMod_Shift = 1 << 13, // Shift
    IRENEMod_Alt = 1 << 14, // Option/Menu
    IRENEMod_Super = 1 << 15, // Cmd/Super/Windows
    IRENEMod_Shortcut = 1 << 11, // Alias for Ctrl (non-macOS) _or_ Super (macOS).
    IRENEMod_Mask_ = 0xF800,  // 5-bits

    // [Internal] Prior to 1.87 we required user to fill io.KeysDown[512] using their own native index + the io.KeyMap[] array.
    // We are ditching this method but keeping a legacy path for user code doing e.g. IsKeyPressed(MY_NATIVE_KEY_CODE)
    // If you need to iterate all keys (for e.g. an input mapper) you may use IRENEKey_NamedKey_BEGIN..IRENEKey_NamedKey_END.
    IRENEKey_NamedKey_BEGIN = 512,
    IRENEKey_NamedKey_END = IRENEKey_COUNT,
    IRENEKey_NamedKey_COUNT = IRENEKey_NamedKey_END - IRENEKey_NamedKey_BEGIN,
#ifdef IMGUI_DISABLE_OBSOLETE_KEYIO
    IRENEKey_KeysData_SIZE = IRENEKey_NamedKey_COUNT,  // Size of KeysData[]: only hold named keys
    IRENEKey_KeysData_OFFSET = IRENEKey_NamedKey_BEGIN,  // Accesses to io.KeysData[] must use (key - IRENEKey_KeysData_OFFSET) index.
#else
    IRENEKey_KeysData_SIZE = IRENEKey_COUNT,           // Size of KeysData[]: hold legacy 0..512 keycodes + named keys
    IRENEKey_KeysData_OFFSET = 0,                        // Accesses to io.KeysData[] must use (key - IRENEKey_KeysData_OFFSET) index.
#endif

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    IRENEKey_ModCtrl = IRENEMod_Ctrl, IRENEKey_ModShift = IRENEMod_Shift, IRENEKey_ModAlt = IRENEMod_Alt, IRENEKey_ModSuper = IRENEMod_Super, // Renamed in 1.89
    IRENEKey_KeyPadEnter = IRENEKey_KeypadEnter,    // Renamed in 1.87
#endif
};