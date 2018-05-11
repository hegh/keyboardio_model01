// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"
#include "keyswitch_state.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for one-shots.
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"

/*
// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"
*/


/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY,
       MACRO_REISUB,
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { QWERTY, MOUSE_NUMPAD, FUNCTION, SYSTEM_EMERGENCY }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  ( // QWERTY Left
   Key_Backtick, Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, OSM(LeftAlt),
   Key_Tab,      Key_Q,  Key_W,  Key_E,  Key_R,  Key_T,  Key_F3,
   Key_PageUp,   Key_A,  Key_S,  Key_D,  Key_F,  Key_G,
   Key_PageDown, Key_Z,  Key_X,  Key_C,  Key_V,  Key_B,  Key_Minus, // Dvorak left bracket
   Key_Escape,   Key_LeftShift, Key_LeftControl, Key_LeftGui,
   ShiftToLayer(FUNCTION),

   // QWERTY Right
   LockLayer(MOUSE_NUMPAD),  Key_F6, Key_F7, Key_F8,     Key_F9,         Key_F10,        Key_RightBracket, // Dvorak equals
   Key_F4,                   Key_Y,  Key_U,  Key_I,      Key_O,          Key_P,          Key_LeftBracket,  // Dvorak slash
                             Key_H,  Key_J,  Key_K,      Key_L,          Key_Semicolon,  Key_Quote,        // Dvorak minus
   Key_Equals,               Key_N,  Key_M,  Key_Comma,  Key_Period,     Key_Slash,      Key_Pause,       // = is Dvorak right bracket
   Key_Backspace, Key_Enter, Key_Spacebar, OSM(RightShift),
   ShiftToLayer(FUNCTION)),


  [MOUSE_NUMPAD] =  KEYMAP_STACKED
  ( // Mouse/Numpad Left
   LockLayer(SYSTEM_EMERGENCY),  XXX,        XXX,         XXX,        XXX,           XXX,              XXX,
   XXX,                          XXX,        Key_mouseUp, XXX,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   ___, /* pgup */               Key_mouseL, Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   ___, /* pgdn */               XXX,        XXX,         XXX,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, ___, ___, ___,
   ___,

   // Mouse/Numpad Right
   ___, /* numlk */        XXX, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadMultiply, XXX,
   XXX,                    XXX, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      Key_KeypadDivide,
                           XXX, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_KeypadSubtract,
   XXX,                    XXX, Key_Keypad0, Key_KeypadDot, XXX,                XXX,                Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  ( // Function Left
   XXX,                   ___,             ___,        ___,   ___,   ___,   M(MACRO_VERSION_INFO),
   ___,                   Key_6,           Key_7,      Key_8, Key_9, Key_0, Key_F11,
   Key_LEDEffectNext,     Key_1,           Key_2,      Key_3, Key_4, Key_5,
   Key_LEDEffectPrevious, Key_PrintScreen, Key_Insert, XXX,   XXX,   XXX,   Key_Home,
   Key_LeftGui, Key_LeftShift, Key_LeftControl, Key_LeftAlt,
   ___,

   // Function Right
   M(MACRO_ANY), ___,        ___,                   ___,                   ___,         ___, XXX,
   Key_F12,           XXX,           Key_Home,                 Key_UpArrow,              Key_End,        XXX,     Key_Backslash,
                      XXX,           Key_LeftArrow,            Key_DownArrow,            Key_RightArrow, XXX,     XXX,
   Key_End,           Consumer_Mute, Consumer_VolumeDecrement, Consumer_VolumeIncrement, XXX,            XXX,     XXX,
   Key_Delete, Key_RightControl, Key_RightShift, Key_RightGui,
   ___),

  [SYSTEM_EMERGENCY] = KEYMAP_STACKED
  ( // System Emergency Left
   ___, LCTRL(LALT(Key_F1)), LCTRL(LALT(Key_F2)), LCTRL(LALT(Key_F3)), LCTRL(LALT(Key_F4)), LCTRL(LALT(Key_F5)), XXX, // Prog returns to prev. layer.
   XXX, XXX,                 XXX,                 XXX,                 XXX,                 XXX,                 XXX,
   XXX, XXX,                 XXX,                 XXX,                 XXX,                 XXX,
   XXX, XXX,                 XXX,                 XXX,                 XXX,                 XXX,                 XXX,
   XXX, XXX, XXX, XXX,
   XXX,

   // System Emergency Right
   XXX,             LCTRL(LALT(Key_F6)), LCTRL(LALT(Key_F7)), LCTRL(LALT(Key_F8)), LCTRL(LALT(Key_F9)), XXX, XXX,
   XXX,             XXX,                 XXX,                 XXX,                 XXX,                 XXX, XXX,
                    XXX,                 XXX,                 XXX,                 XXX,                 XXX, XXX,
   M(MACRO_REISUB), XXX,                 XXX,                 XXX,                 XXX,                 XXX, XXX, // Butterfly key reboots the system.
   XXX, XXX, XXX, XXX,
   XXX),

) // KEYMAPS

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */
static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 */
static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}

/** reisubMacro sends the Linux Reboot Even If System Utterly Broken sequence.
 */
static const macro_t *reisubMacro(uint8_t keyState) {
  return MACRODOWN(D(LeftAlt),
                   D(Sysreq),
                   T(R),
		   T(E),
		   W(250), W(250), W(250), W(250), W(250), W(250), W(250), W(250), // 2 seconds.
		   T(I),
		   W(250), W(250), W(250), W(250), W(250), W(250), W(250), W(250), // 2 seconds.
		   T(S),
		   W(250), W(250), W(250), W(250), W(250), W(250), W(250), W(250), // 2 seconds.
		   T(U),
		   W(250), W(250), W(250), W(250), W(250), W(250), W(250), W(250), // 2 seconds.
		   T(B),
		   U(Sysreq),
		   U(LeftAlt));
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.
 */
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;

  case MACRO_REISUB:
    return reisubMacro(keyState);
  }
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.

/*
static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);
*/

static void layerColorOverride(bool post_clear) {
  if (!post_clear) return;

  // NOTE: Multiple layers may be enabled at the same time. Don't assume that
  // just because the layer you are interested in coloring is enabled, no other
  // layers are also enabled.

  if (Layer.isOn(SYSTEM_EMERGENCY)) {
    LEDControl.set_all_leds_to(breath_compute(33, 255));  // Yellow
    LEDControl.setCrgbAt(LED_PROG, CRGB(0, 160, 0));      // Green
    LEDControl.setCrgbAt(LED_BUTTERFLY, CRGB(160, 0, 0)); // Red

    // Blue numbers to switch to virtual terminals.
    constexpr int8_t numbers[] = {
        LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9, -1,
    };
    for (int8_t i = 0; numbers[i] != -1; i++) {
      LEDControl.setCrgbAt(numbers[i], CRGB(0, 0, 160)); // Blue
    }
    return;
  }
  if (Layer.isOn(MOUSE_NUMPAD)) {
    LEDControl.setCrgbAt(LED_PROG, breath_compute(0, 255)); // Red
    return;
  }
}


/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
    &BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
    &TestMode,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

/* Disable the LED effects I'm never likely to use.
    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    &LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    &AlphaSquareEffect,
*/

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    &NumPad,

    // The macros plugin adds support for macros
    &Macros,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys,

    // The HostPowerManagement plugin enables waking up the host from suspend,
    // and allows us to turn LEDs off when it goes to sleep.
    &HostPowerManagement,

    // OneShot and OneShotEscape enable one-shot keys (tap a modifier and it
    // sticks until it applies to something, double-tap to lock/single to
    // unlock), and Escape to leave any active one-shots.
    &OneShot, &EscapeOneShot
  );

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = MOUSE_NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  // AlphaSquare.color = CRGB(255, 0, 0);

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // Add any layer-specific overrides defined in this file.
  Kaleidoscope.useLoopHook(layerColorOverride);

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
