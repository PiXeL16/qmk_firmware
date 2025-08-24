/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Layer-tap configuration for space bar layer switching
#define TAPPING_TERM 200                     // 200ms for tap/hold detection
#define TAPPING_TERM_PER_KEY                 // Allow per-key tapping term customization
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY      // Allow per-key hold-on-other-key-press behavior
#define QUICK_TAP_TERM 0                     // Disable quick tap for more consistent behavior

// Combo configuration
#define COMBO_TERM 150                       // 150ms window to press both keys for combo

// Tap Dance configuration
// Tap dance configuration removed

// SM_TD (Home Row Modifiers) configuration - COMMENTED OUT (not using home row modifiers)
// #define MAX_DEFERRED_EXECUTORS 10            // Required for SM_TD library
// #define SMTD_TIMEOUT_RELEASE 5               // If false holds during fast typing, decrease this

// Unicode settings for emoji layer (using UNICODEMAP instead)
// #define UNICODE_SELECTED_MODES UC_MAC

#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_LED_COUNT 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

// Underglow
/*
#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 14    // Number of LEDs
#define RGBLIGHT_SLEEP
*/