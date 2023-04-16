#pragma once

#include "ipch.h"

enum IreneKey : int
{
    // Keyboard
    IreneKey_None = 0,
    IreneKey_Tab = 512,             // == IreneKey_NamedKey_BEGIN
    IreneKey_LeftArrow,
    IreneKey_RightArrow,
    IreneKey_UpArrow,
    IreneKey_DownArrow,
    IreneKey_PageUp,
    IreneKey_PageDown,
    IreneKey_Home,
    IreneKey_End,
    IreneKey_Insert,
    IreneKey_Delete,
    IreneKey_Backspace,
    IreneKey_Space,
    IreneKey_Enter,
    IreneKey_Escape,
    IreneKey_LeftCtrl, IreneKey_LeftShift, IreneKey_LeftAlt, IreneKey_LeftSuper,
    IreneKey_RightCtrl, IreneKey_RightShift, IreneKey_RightAlt, IreneKey_RightSuper,
    IreneKey_Menu,
    IreneKey_0, IreneKey_1, IreneKey_2, IreneKey_3, IreneKey_4, IreneKey_5, IreneKey_6, IreneKey_7, IreneKey_8, IreneKey_9,
    IreneKey_A, IreneKey_B, IreneKey_C, IreneKey_D, IreneKey_E, IreneKey_F, IreneKey_G, IreneKey_H, IreneKey_I, IreneKey_J,
    IreneKey_K, IreneKey_L, IreneKey_M, IreneKey_N, IreneKey_O, IreneKey_P, IreneKey_Q, IreneKey_R, IreneKey_S, IreneKey_T,
    IreneKey_U, IreneKey_V, IreneKey_W, IreneKey_X, IreneKey_Y, IreneKey_Z,
    IreneKey_F1, IreneKey_F2, IreneKey_F3, IreneKey_F4, IreneKey_F5, IreneKey_F6,
    IreneKey_F7, IreneKey_F8, IreneKey_F9, IreneKey_F10, IreneKey_F11, IreneKey_F12,
    IreneKey_Apostrophe,        // '
    IreneKey_Comma,             // ,
    IreneKey_Minus,             // -
    IreneKey_Period,            // .
    IreneKey_Slash,             // /
    IreneKey_Semicolon,         // ;
    IreneKey_Equal,             // =
    IreneKey_LeftBracket,       // [
    IreneKey_Backslash,         // \ (this text inhibit multiline comment caused by backslash)
    IreneKey_RightBracket,      // ]
    IreneKey_GraveAccent,       // `
    IreneKey_CapsLock,
    IreneKey_ScrollLock,
    IreneKey_NumLock,
    IreneKey_PrintScreen,
    IreneKey_Pause,
    IreneKey_Keypad0, IreneKey_Keypad1, IreneKey_Keypad2, IreneKey_Keypad3, IreneKey_Keypad4,
    IreneKey_Keypad5, IreneKey_Keypad6, IreneKey_Keypad7, IreneKey_Keypad8, IreneKey_Keypad9,
    IreneKey_KeypadDecimal,
    IreneKey_KeypadDivide,
    IreneKey_KeypadMultiply,
    IreneKey_KeypadSubtract,
    IreneKey_KeypadAdd,
    IreneKey_KeypadEnter,
    IreneKey_KeypadEqual,

    // Gamepad (some of those are analog values, 0.0f to 1.0f)                          // NAVIGATION ACTION
    // (download controller mapping PNG/PSD at http://dearimgui.com/controls_sheets)
    IreneKey_GamepadStart,          // Menu (Xbox)      + (Switch)   Start/Options (PS)
    IreneKey_GamepadBack,           // View (Xbox)      - (Switch)   Share (PS)
    IreneKey_GamepadFaceLeft,       // X (Xbox)         Y (Switch)   Square (PS)        // Tap: Toggle Menu. Hold: Windowing mode (Focus/Move/Resize windows)
    IreneKey_GamepadFaceRight,      // B (Xbox)         A (Switch)   Circle (PS)        // Cancel / Close / Exit
    IreneKey_GamepadFaceUp,         // Y (Xbox)         X (Switch)   Triangle (PS)      // Text Input / On-screen Keyboard
    IreneKey_GamepadFaceDown,       // A (Xbox)         B (Switch)   Cross (PS)         // Activate / Open / Toggle / Tweak
    IreneKey_GamepadDpadLeft,       // D-pad Left                                       // Move / Tweak / Resize Window (in Windowing mode)
    IreneKey_GamepadDpadRight,      // D-pad Right                                      // Move / Tweak / Resize Window (in Windowing mode)
    IreneKey_GamepadDpadUp,         // D-pad Up                                         // Move / Tweak / Resize Window (in Windowing mode)
    IreneKey_GamepadDpadDown,       // D-pad Down                                       // Move / Tweak / Resize Window (in Windowing mode)
    IreneKey_GamepadL1,             // L Bumper (Xbox)  L (Switch)   L1 (PS)            // Tweak Slower / Focus Previous (in Windowing mode)
    IreneKey_GamepadR1,             // R Bumper (Xbox)  R (Switch)   R1 (PS)            // Tweak Faster / Focus Next (in Windowing mode)
    IreneKey_GamepadL2,             // L Trig. (Xbox)   ZL (Switch)  L2 (PS) [Analog]
    IreneKey_GamepadR2,             // R Trig. (Xbox)   ZR (Switch)  R2 (PS) [Analog]
    IreneKey_GamepadL3,             // L Stick (Xbox)   L3 (Switch)  L3 (PS)
    IreneKey_GamepadR3,             // R Stick (Xbox)   R3 (Switch)  R3 (PS)
    IreneKey_GamepadLStickLeft,     // [Analog]                                         // Move Window (in Windowing mode)
    IreneKey_GamepadLStickRight,    // [Analog]                                         // Move Window (in Windowing mode)
    IreneKey_GamepadLStickUp,       // [Analog]                                         // Move Window (in Windowing mode)
    IreneKey_GamepadLStickDown,     // [Analog]                                         // Move Window (in Windowing mode)
    IreneKey_GamepadRStickLeft,     // [Analog]
    IreneKey_GamepadRStickRight,    // [Analog]
    IreneKey_GamepadRStickUp,       // [Analog]
    IreneKey_GamepadRStickDown,     // [Analog]

    // Aliases: Mouse Buttons (auto-submitted from AddMouseButtonEvent() calls)
    // - This is mirroring the data also written to io.MouseDown[], io.MouseWheel, in a format allowing them to be accessed via standard key API.
    IreneKey_MouseLeft, IreneKey_MouseRight, IreneKey_MouseMiddle, IreneKey_MouseX1, IreneKey_MouseX2, IreneKey_MouseWheelX, IreneKey_MouseWheelY,

    // [Internal] Reserved for mod storage
    IreneKey_ReservedForModCtrl, IreneKey_ReservedForModShift, IreneKey_ReservedForModAlt, IreneKey_ReservedForModSuper,
    IreneKey_COUNT,

    // Keyboard Modifiers (explicitly submitted by backend via AddKeyEvent() calls)
    // - This is mirroring the data also written to io.KeyCtrl, io.KeyShift, io.KeyAlt, io.KeySuper, in a format allowing
    //   them to be accessed via standard key API, allowing calls such as IsKeyPressed(), IsKeyReleased(), querying duration etc.
    // - Code polling every key (e.g. an interface to detect a key press for input mapping) might want to ignore those
    //   and prefer using the real keys (e.g. IreneKey_LeftCtrl, IreneKey_RightCtrl instead of ImGuiMod_Ctrl).
    // - In theory the value of keyboard modifiers should be roughly equivalent to a logical or of the equivalent left/right keys.
    //   In practice: it's complicated; mods are often provided from different sources. Keyboard layout, IME, sticky keys and
    //   backends tend to interfere and break that equivalence. The safer decision is to relay that ambiguity down to the end-user...
    IreneMod_None = 0,
    IreneMod_Ctrl = 1 << 12, // Ctrl
    IreneMod_Shift = 1 << 13, // Shift
    IreneMod_Alt = 1 << 14, // Option/Menu
    IreneMod_Super = 1 << 15, // Cmd/Super/Windows
    IreneMod_Shortcut = 1 << 11, // Alias for Ctrl (non-macOS) _or_ Super (macOS).
    IreneMod_Mask_ = 0xF800,  // 5-bits

    // [Internal] Prior to 1.87 we required user to fill io.KeysDown[512] using their own native index + the io.KeyMap[] array.
    // We are ditching this method but keeping a legacy path for user code doing e.g. IsKeyPressed(MY_NATIVE_KEY_CODE)
    // If you need to iterate all keys (for e.g. an input mapper) you may use IreneKey_NamedKey_BEGIN..IreneKey_NamedKey_END.
    IreneKey_NamedKey_BEGIN = 512,
    IreneKey_NamedKey_END = IreneKey_COUNT,
    IreneKey_NamedKey_COUNT = IreneKey_NamedKey_END - IreneKey_NamedKey_BEGIN,
#ifdef IMGUI_DISABLE_OBSOLETE_KEYIO
    IreneKey_KeysData_SIZE = IreneKey_NamedKey_COUNT,  // Size of KeysData[]: only hold named keys
    IreneKey_KeysData_OFFSET = IreneKey_NamedKey_BEGIN,  // Accesses to io.KeysData[] must use (key - IreneKey_KeysData_OFFSET) index.
#else
    IreneKey_KeysData_SIZE = IreneKey_COUNT,           // Size of KeysData[]: hold legacy 0..512 keycodes + named keys
    IreneKey_KeysData_OFFSET = 0,                        // Accesses to io.KeysData[] must use (key - IreneKey_KeysData_OFFSET) index.
#endif

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    IreneKey_ModCtrl = IreneMod_Ctrl, IreneKey_ModShift = IreneMod_Shift, IreneKey_ModAlt = IreneMod_Alt, IreneKey_ModSuper = IreneMod_Super, // Renamed in 1.89
    IreneKey_KeyPadEnter = IreneKey_KeypadEnter,    // Renamed in 1.87
#endif
};