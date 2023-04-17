#pragma once

#include "ipch.h"

enum RapierKey : int
{
    // Keyboard
    RapierKey_None = 0,
    RapierKey_Tab = 512,             // == RapierKey_NamedKey_BEGIN
    RapierKey_LeftArrow,
    RapierKey_RightArrow,
    RapierKey_UpArrow,
    RapierKey_DownArrow,
    RapierKey_PageUp,
    RapierKey_PageDown,
    RapierKey_Home,
    RapierKey_End,
    RapierKey_Insert,
    RapierKey_Delete,
    RapierKey_Backspace,
    RapierKey_Space,
    RapierKey_Enter,
    RapierKey_Escape,
    RapierKey_LeftCtrl, RapierKey_LeftShift, RapierKey_LeftAlt, RapierKey_LeftSuper,
    RapierKey_RightCtrl, RapierKey_RightShift, RapierKey_RightAlt, RapierKey_RightSuper,
    RapierKey_Menu,
    RapierKey_0, RapierKey_1, RapierKey_2, RapierKey_3, RapierKey_4, RapierKey_5, RapierKey_6, RapierKey_7, RapierKey_8, RapierKey_9,
    RapierKey_A, RapierKey_B, RapierKey_C, RapierKey_D, RapierKey_E, RapierKey_F, RapierKey_G, RapierKey_H, RapierKey_I, RapierKey_J,
    RapierKey_K, RapierKey_L, RapierKey_M, RapierKey_N, RapierKey_O, RapierKey_P, RapierKey_Q, RapierKey_R, RapierKey_S, RapierKey_T,
    RapierKey_U, RapierKey_V, RapierKey_W, RapierKey_X, RapierKey_Y, RapierKey_Z,
    RapierKey_F1, RapierKey_F2, RapierKey_F3, RapierKey_F4, RapierKey_F5, RapierKey_F6,
    RapierKey_F7, RapierKey_F8, RapierKey_F9, RapierKey_F10, RapierKey_F11, RapierKey_F12,
    RapierKey_Apostrophe,        // '
    RapierKey_Comma,             // ,
    RapierKey_Minus,             // -
    RapierKey_Period,            // .
    RapierKey_Slash,             // /
    RapierKey_Semicolon,         // ;
    RapierKey_Equal,             // =
    RapierKey_LeftBracket,       // [
    RapierKey_Backslash,         // \ (this text inhibit multiline comment caused by backslash)
    RapierKey_RightBracket,      // ]
    RapierKey_GraveAccent,       // `
    RapierKey_CapsLock,
    RapierKey_ScrollLock,
    RapierKey_NumLock,
    RapierKey_PrintScreen,
    RapierKey_Pause,
    RapierKey_Keypad0, RapierKey_Keypad1, RapierKey_Keypad2, RapierKey_Keypad3, RapierKey_Keypad4,
    RapierKey_Keypad5, RapierKey_Keypad6, RapierKey_Keypad7, RapierKey_Keypad8, RapierKey_Keypad9,
    RapierKey_KeypadDecimal,
    RapierKey_KeypadDivide,
    RapierKey_KeypadMultiply,
    RapierKey_KeypadSubtract,
    RapierKey_KeypadAdd,
    RapierKey_KeypadEnter,
    RapierKey_KeypadEqual,

    // Gamepad (some of those are analog values, 0.0f to 1.0f)                          // NAVIGATION ACTION
    // (download controller mapping PNG/PSD at http://dearimgui.com/controls_sheets)
    RapierKey_GamepadStart,          // Menu (Xbox)      + (Switch)   Start/Options (PS)
    RapierKey_GamepadBack,           // View (Xbox)      - (Switch)   Share (PS)
    RapierKey_GamepadFaceLeft,       // X (Xbox)         Y (Switch)   Square (PS)        // Tap: Toggle Menu. Hold: Windowing mode (Focus/Move/Resize windows)
    RapierKey_GamepadFaceRight,      // B (Xbox)         A (Switch)   Circle (PS)        // Cancel / Close / Exit
    RapierKey_GamepadFaceUp,         // Y (Xbox)         X (Switch)   Triangle (PS)      // Text Input / On-screen Keyboard
    RapierKey_GamepadFaceDown,       // A (Xbox)         B (Switch)   Cross (PS)         // Activate / Open / Toggle / Tweak
    RapierKey_GamepadDpadLeft,       // D-pad Left                                       // Move / Tweak / Resize Window (in Windowing mode)
    RapierKey_GamepadDpadRight,      // D-pad Right                                      // Move / Tweak / Resize Window (in Windowing mode)
    RapierKey_GamepadDpadUp,         // D-pad Up                                         // Move / Tweak / Resize Window (in Windowing mode)
    RapierKey_GamepadDpadDown,       // D-pad Down                                       // Move / Tweak / Resize Window (in Windowing mode)
    RapierKey_GamepadL1,             // L Bumper (Xbox)  L (Switch)   L1 (PS)            // Tweak Slower / Focus Previous (in Windowing mode)
    RapierKey_GamepadR1,             // R Bumper (Xbox)  R (Switch)   R1 (PS)            // Tweak Faster / Focus Next (in Windowing mode)
    RapierKey_GamepadL2,             // L Trig. (Xbox)   ZL (Switch)  L2 (PS) [Analog]
    RapierKey_GamepadR2,             // R Trig. (Xbox)   ZR (Switch)  R2 (PS) [Analog]
    RapierKey_GamepadL3,             // L Stick (Xbox)   L3 (Switch)  L3 (PS)
    RapierKey_GamepadR3,             // R Stick (Xbox)   R3 (Switch)  R3 (PS)
    RapierKey_GamepadLStickLeft,     // [Analog]                                         // Move Window (in Windowing mode)
    RapierKey_GamepadLStickRight,    // [Analog]                                         // Move Window (in Windowing mode)
    RapierKey_GamepadLStickUp,       // [Analog]                                         // Move Window (in Windowing mode)
    RapierKey_GamepadLStickDown,     // [Analog]                                         // Move Window (in Windowing mode)
    RapierKey_GamepadRStickLeft,     // [Analog]
    RapierKey_GamepadRStickRight,    // [Analog]
    RapierKey_GamepadRStickUp,       // [Analog]
    RapierKey_GamepadRStickDown,     // [Analog]

    // Aliases: Mouse Buttons (auto-submitted from AddMouseButtonEvent() calls)
    // - This is mirroring the data also written to io.MouseDown[], io.MouseWheel, in a format allowing them to be accessed via standard key API.
    RapierKey_MouseLeft, RapierKey_MouseRight, RapierKey_MouseMiddle, RapierKey_MouseX1, RapierKey_MouseX2, RapierKey_MouseWheelX, RapierKey_MouseWheelY,

    // [Internal] Reserved for mod storage
    RapierKey_ReservedForModCtrl, RapierKey_ReservedForModShift, RapierKey_ReservedForModAlt, RapierKey_ReservedForModSuper,
    RapierKey_COUNT,

    // Keyboard Modifiers (explicitly submitted by backend via AddKeyEvent() calls)
    // - This is mirroring the data also written to io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper, in a format allowing
    //   them to be accessed via standard key API, allowing calls such as IsKeyPressed(), IsKeyReleased(), querying duration etc.
    // - Code polling every key (e.g. an interface to detect a key press for input mapping) might want to ignore those
    //   and prefer using the real keys (e.g. RapierKey_LeftCtrl, RapierKey_RightCtrl instead of ImGuiMod_Ctrl).
    // - In theory the value of keyboard modifiers should be roughly equivalent to a logical or of the equivalent left/right keys.
    //   In practice: it's complicated; mods are often provided from different sources. Keyboard layout, IME, sticky keys and
    //   backends tend to interfere and break that equivalence. The safer decision is to relay that ambiguity down to the end-user...
    RapierMod_None = 0,
    RapierMod_Ctrl = 1 << 12, // Ctrl
    RapierMod_Shift = 1 << 13, // Shift
    RapierMod_Alt = 1 << 14, // Option/Menu
    RapierMod_Super = 1 << 15, // Cmd/Super/Windows
    RapierMod_Shortcut = 1 << 11, // Alias for Ctrl (non-macOS) _or_ Super (macOS).
    RapierMod_Mask_ = 0xF800,  // 5-bits

    // [Internal] Prior to 1.87 we required user to fill io.KeysDown[512] using their own native index + the io.KeyMap[] array.
    // We are ditching this method but keeping a legacy path for user code doing e.g. IsKeyPressed(MY_NATIVE_KEY_CODE)
    // If you need to iterate all keys (for e.g. an input mapper) you may use RapierKey_NamedKey_BEGIN..RapierKey_NamedKey_END.
    RapierKey_NamedKey_BEGIN = 512,
    RapierKey_NamedKey_END = RapierKey_COUNT,
    RapierKey_NamedKey_COUNT = RapierKey_NamedKey_END - RapierKey_NamedKey_BEGIN,
#ifdef IMGUI_DISABLE_OBSOLETE_KEYIO
    RapierKey_KeysData_SIZE = RapierKey_NamedKey_COUNT,  // Size of KeysData[]: only hold named keys
    RapierKey_KeysData_OFFSET = RapierKey_NamedKey_BEGIN,  // Accesses to io.KeysData[] must use (key - RapierKey_KeysData_OFFSET) index.
#else
    RapierKey_KeysData_SIZE = RapierKey_COUNT,           // Size of KeysData[]: hold legacy 0..512 keycodes + named keys
    RapierKey_KeysData_OFFSET = 0,                        // Accesses to io.KeysData[] must use (key - RapierKey_KeysData_OFFSET) index.
#endif

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    RapierKey_ModCtrl = RapierMod_Ctrl, RapierKey_ModShift = RapierMod_Shift, RapierKey_ModAlt = RapierMod_Alt, RapierKey_ModSuper = RapierMod_Super, // Renamed in 1.89
    RapierKey_KeyPadEnter = RapierKey_KeypadEnter,    // Renamed in 1.87
#endif
};