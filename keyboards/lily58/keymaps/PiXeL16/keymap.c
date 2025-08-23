#include QMK_KEYBOARD_H

#ifdef WPM_ENABLE
#include "wpm.h"
#endif

enum layer_number {
  _QWERTY = 0,
  _SHIFT,
  _SYMBOLS,
  _NAV,
  _RAISE,
  _FUNCTION,
  _EMOJI,
  _SPANISH,
  _MOUSE,
};

enum custom_keycodes {
  M_LGUI = SAFE_RANGE,
  M_LGUI_LBRC,
  M_LGUI_RBRC,
  // Application navigation shortcuts
  NAV_BACK,      // Ctrl+[
  NAV_FORWARD,   // Ctrl+]
  TAB_PREV,      // Ctrl+Shift+Tab
  TAB_NEXT,      // Ctrl+Tab
  // Workspace navigation shortcuts (macOS)
  WS_LEFT,       // Ctrl+Left (previous space)
  WS_RIGHT,      // Ctrl+Right (next space)
  WS_UP,         // Ctrl+Up (Mission Control)
  WS_DOWN,       // Ctrl+Down (Application windows)
  // Word navigation shortcuts
  WORD_LEFT,     // Option+Left (previous word)
  WORD_RIGHT,    // Option+Right (next word)
  WORD_SELECT,   // Select current word macro
  WORD_DELETE,   // Delete current word macro
  // Smart brackets with cursor positioning
  SYM_LPRN,      // ( with smart positioning
  SYM_RPRN,      // ) with smart positioning  
  SYM_LBRC,      // [ with smart positioning
  SYM_RBRC,      // ] with smart positioning
  SYM_LCBR,      // { with smart positioning
  SYM_RCBR,      // } with smart positioning
  SYM_LABK,      // < with smart positioning
  SYM_RABK,      // > with smart positioning
  // Emojis
  EM_WAVE,       // 👋 (W - wave)
  EM_HEART,      // ❤️ (H - heart)  
  EM_SMILE,      // 😊 (S - smile)
  EM_LAUGH,      // 😂 (L - laugh)
  EM_THINK,      // 🤔 (T - think)
  EM_PARTY,      // 🎉 (P - party)
  EM_FIRE,       // 🔥 (F - fire)
  EM_THUMBS,     // 👍 (U - thumbs up)
  EM_EYES,       // 👀 (E - eyes)
  EM_CRY,        // 😢 (C - cry)
  EM_COOL,       // 😎 (O - cool)
  EM_ANGRY,      // 😡 (A - angry)
  EM_KISS,       // 😘 (K - kiss)
  EM_WINK,       // 😉 (I - wink) 
  EM_JOY,        // 😄 (J - joy)
  EM_ROCKET,     // 🚀 (R - rocket)
  EM_BOOM,       // 💥 (B - boom)
  EM_DIZZY,      // 😵 (D - dizzy)
  EM_MONEY,      // 💰 (M - money)
  EM_ZZZ,        // 😴 (Z - zzz/sleep)
  EM_NERD,       // 🤓 (N - nerd)
  EM_GHOST,      // 👻 (G - ghost)
  EM_ALIEN,      // 👽 (X - alien/x-files)
  EM_VICTORY,    // ✌️ (V - victory)
  EM_QUESTION,   // ❓ (Q - question)
  EM_YES,        // ✅ (Y - yes)
  // Symbols for right side
  EM_CHECK,      // ✓
  EM_CROSS,      // ✗  
  EM_ARROW_L,    // ←
  EM_ARROW_R,    // →
  EM_ARROW_U,    // ↑
  EM_ARROW_D,    // ↓
  EM_QUOTE_L,    // "
  EM_QUOTE_R,    // "
  EM_APOS_L,     // '
  EM_APOS_R,     // '
  // Additional emojis
  EM_POINT_U,    // 👆 pointing up
  EM_POINT_D,    // 👇 pointing down  
  EM_POINT_L,    // 👈 pointing left
  EM_POINT_R,    // 👉 pointing right
  // Double tap emoji key
  EMOJI_PICKER,  // Launch system emoji picker
  // Spanish accented characters
  SPANISH_PICKER, // Spanish character picker
  ES_A,           // á
  ES_E,           // é  
  ES_I,           // í
  ES_O,           // ó
  ES_U,           // ú
  ES_N,           // ñ
  ES_EXCL,        // ¡
  ES_QUEST,       // ¿
  
  // Display rotation
  ROTATE_DISPLAY, // Manual display rotation trigger
};

// Smart bracket state tracking
static bool lprn_held = false;
static bool lbrc_held = false; 
static bool lcbr_held = false;
static bool labk_held = false;

// Double tap detection for emoji picker
static uint16_t emoji_key_timer = 0;

// Space -> Enter combo detection for Cmd+Space
static bool space_pressed_first = false;
static uint16_t space_combo_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |A/Sft |S/Cmd |D/Opt |F/Ctl |   G  |-------.    ,-------|   H  |J/Ctl |K/Opt |L/Cmd |;/Sft |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  MT(MOD_LSFT, KC_A), MT(MOD_LGUI, KC_S), MT(MOD_LALT, KC_D), MT(MOD_LCTL, KC_F), KC_G, KC_H, MT(MOD_RCTL, KC_J), MT(MOD_RALT, KC_K), MT(MOD_RGUI, KC_L), MT(MOD_RSFT, KC_SCLN), KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* SHIFT
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   ~  |   @  |   #  |   %  |      |                    |   ^  |   &  |   |  |   \  |      |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   !  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   "  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   :  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ;  |   :  |   *  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |NAV | /SHIFT /       \Enter \  |RAISE |RAlt| FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SHIFT] = LAYOUT(
  KC_ESC,   KC_TILD, KC_AT,   KC_HASH, KC_PERC, _______,                   KC_CIRC, KC_AMPR, KC_PIPE, KC_BSLS, _______, KC_BSPC,
  KC_EXLM,  S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),                   S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), KC_DQUO,
  KC_TAB,   S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),                   S(KC_H), S(KC_J), S(KC_K), S(KC_L), KC_COLN, KC_QUOT,
  KC_LSFT,  S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), KC_LBRC, KC_RBRC, S(KC_N), S(KC_M), KC_SCLN, KC_COLN, KC_ASTR, KC_RSFT,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* SYMBOLS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   \  |   $  |   {  |   }  |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   <  |   =  |   -  |   (  |   )  |   >  |-------.    ,-------|      |J/Ctl |K/Opt |L/Cmd |;/Sft |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |   [  |   ]  |   +  |-------|    |-------|      |   _  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYMBOLS] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_BSLS, KC_DLR,  SYM_LCBR, SYM_RCBR, _______,                   _______, _______, _______, _______, _______, _______,
  SYM_LABK, KC_EQL, KC_MINS, SYM_LPRN, SYM_RPRN, SYM_RABK,                   _______, MT(MOD_RCTL, KC_J), MT(MOD_RALT, KC_K), MT(MOD_RGUI, KC_L), MT(MOD_RSFT, KC_SCLN), _______,
  _______, _______, _______, SYM_LBRC, SYM_RBRC, KC_PLUS, _______, _______, _______, KC_UNDS, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* FUNCTION 
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |SPANI |EMOJI |      |      |                    | Prev | Next | Play | Vol- | Vol+ | Mute |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |Bri- |Bri+ |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_FUNCTION] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, SPANISH_PICKER, EMOJI_PICKER, _______, _______,       KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, KC_BRMD, KC_BRMU, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* EMOJI
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |Cancel|      |      |      |      |      |                    |      |      |      |      |      | ✗   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Cancel| Q❓  | W👋  | E👀  | R🚀  | T🤔  |                    | Y✅  | U↑   | I😉  | O😎  | P🎉  |  "  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | A😡  | S😊  | D😵  | F🔥  | G👻  |-------.    ,-------|H←   | J↓   | K→   | L😂  |  ;👉 |  '  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Z😴  | X👽  | C😢  | V✌️  | B💥  |-------|    |-------|N🤓  | M💰  |      |      |      |     |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_EMOJI] = LAYOUT(
  TO(_QWERTY), _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, EM_CROSS,
  TO(_QWERTY), EM_QUESTION, EM_WAVE, EM_EYES, EM_ROCKET, EM_THINK,       EM_YES, EM_ARROW_U, EM_WINK, EM_COOL, EM_PARTY, EM_QUOTE_R,
  _______, EM_ANGRY, EM_SMILE, EM_DIZZY, EM_FIRE, EM_GHOST,              EM_ARROW_L, EM_ARROW_D, EM_ARROW_R, EM_LAUGH, EM_POINT_R, EM_APOS_R,
  _______, EM_ZZZ, EM_ALIEN, EM_CRY, EM_VICTORY, EM_BOOM, _______, _______, EM_NERD, EM_MONEY, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* SPANISH (Español)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |Cancel|   ¡  |      |      |      |      |                    |      |      |      |      |      |   ¿  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Cancel|      |      |   é  |      |      |                    |      |   ú  |   í  |   ó  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   á  |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   ñ  |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SPANISH] = LAYOUT(
  TO(_QWERTY), ES_EXCL, _______, _______, _______, _______,           _______, _______, _______, _______, _______, ES_QUEST,
  TO(_QWERTY), _______, _______, ES_E, _______, _______,              _______, ES_U, ES_I, ES_O, _______, _______,
  _______, ES_A, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, ES_N, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* MOUSE (Mouse Control)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |WhlUp |      |      |      |                    |      | ↑    |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LClk |WhlDn | RClk |      |      |-------.    ,-------| ←    | ↓    | ↑    | →    |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | MClk |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_MOUSE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, KC_MS_WH_UP, _______, _______, _______,              _______, KC_MS_UP, _______, _______, _______, _______,
  _______, KC_MS_BTN1, KC_MS_WH_DOWN, KC_MS_BTN2, _______, _______,      KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, _______, _______,
  _______, _______, KC_MS_BTN3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), _______, MO(_FUNCTION)
),
/* NAV (Navigation)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |Back  |Forwd |PrvTab|NxtTab|      |                    |WS ←  |WS →  |WS ↑  |WS ↓  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |                    | W←   | Up   | W→   |WSel  |W⌫   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift| Left | Down |Right |   $  |   %  |-------.    ,-------| Left | Down |Right |      |   (  |   )  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LCtrl |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |  |   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAV] = LAYOUT(
  _______, NAV_BACK, NAV_FORWARD, TAB_PREV, TAB_NEXT, _______,             WS_LEFT, WS_RIGHT, WS_UP, WS_DOWN, _______, _______,
  _______, _______, KC_UP,   _______, _______, _______,                   WORD_LEFT, KC_UP, WORD_RIGHT, WORD_SELECT, WORD_DELETE, _______,
  KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, S(KC_4), S(KC_5),                   KC_LEFT, KC_DOWN, KC_RGHT, _______, S(KC_9), S(KC_0),
  KC_LCTL, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, S(KC_MINS), S(KC_EQL), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LCtrl |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_LSFT, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_LCTL, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______, S(KC_EQL), KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             KC_LALT, LT(_SYMBOLS, KC_LGUI), _______, LT(_SHIFT, KC_SPC), KC_ENT, _______, MO(_MOUSE), MO(_FUNCTION)
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  // Initialize Unicode mode for emoji support
  set_unicode_input_mode(UNICODE_MODE_MACOS);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_custom_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
const char *read_layer_icon(void);
const char *read_layer_name(void);

// Rotating display functions
const char *read_rotating_display(void);
uint8_t get_current_display_type(void);
void force_display_rotation(void);

const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // Left side - Layer icon + typing info
    oled_write_ln(read_layer_icon(), false);
    oled_write_ln("", false); // Empty line for spacing
    
    // Display WPM using QMK's built-in function
    char wpm_str[16];
    snprintf(wpm_str, sizeof(wpm_str), "WPM: %3d", get_current_wpm());
    oled_write_ln(wpm_str, false);
    
    oled_write_ln(read_keylogs(), false);
  } else {
    // Right side - Rotating display (changes every 30 minutes)
    uint8_t display_type = get_current_display_type();
    const char *display_content = read_rotating_display();
    
    // All displays are now bitmap-based
    if (display_type == 2) {
      // Mindset logo (32x128 - different orientation, same total bytes)
      oled_write_raw_P(display_content, 512); // 32x128 = 4096 bits = 512 bytes
    } else {
      // PiXeL16 and Ichigo logos (128x32 standard)
      oled_write_raw_P(display_content, 512); // 128x32 = 4096 bits = 512 bytes
    }
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Handle Space -> Enter combo for Cmd+Space
  // Check for both KC_SPC and the Layer Tap key that produces space
  if ((keycode == KC_SPC || keycode == LT(_SHIFT, KC_SPC)) && record->event.pressed) {
    space_pressed_first = true;
    space_combo_timer = timer_read();
    return true; // Continue normal space processing
  }
  
  if (keycode == KC_ENT && record->event.pressed) {
    if (space_pressed_first && timer_elapsed(space_combo_timer) < 500) {
      // Space->Enter combo detected within 500ms - trigger Cmd+Space
      space_pressed_first = false;
      register_code(KC_LGUI);
      tap_code(KC_SPC);
      unregister_code(KC_LGUI);
      return false; // Don't process Enter normally
    } else {
      space_pressed_first = false;
      return true; // Process Enter normally
    }
  }
  
  // Reset combo state if any other key is pressed or timeout exceeded
  if (record->event.pressed && keycode != KC_SPC && keycode != KC_ENT && keycode != LT(_SHIFT, KC_SPC)) {
    space_pressed_first = false;
  }
  
  // Timeout check - reset combo state if too much time has passed
  if (space_pressed_first && timer_elapsed(space_combo_timer) > 500) {
    space_pressed_first = false;
  }
  
  switch (keycode) {
    case M_LGUI:
      if (record->event.pressed) {
        tap_code(KC_LGUI);
      }
      return false;
      
    case M_LGUI_LBRC:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_LBRC);
        unregister_code(KC_LGUI);
      }
      return false;
      
    case M_LGUI_RBRC:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_RBRC);
        unregister_code(KC_LGUI);
      }
      return false;

    // Application navigation shortcuts
    case NAV_BACK:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_LBRC);
        unregister_code(KC_LCTL);
      }
      return false;
      
    case NAV_FORWARD:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_RBRC);
        unregister_code(KC_LCTL);
      }
      return false;
      
    case TAB_PREV:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_TAB);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
      }
      return false;
      
    case TAB_NEXT:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_TAB);
        unregister_code(KC_LCTL);
      }
      return false;

    // Workspace navigation shortcuts (macOS)
    case WS_LEFT:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_LEFT);
        unregister_code(KC_LCTL);
      }
      return false;
      
    case WS_RIGHT:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_RGHT);
        unregister_code(KC_LCTL);
      }
      return false;
      
    case WS_UP:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_UP);
        unregister_code(KC_LCTL);
      }
      return false;
      
    case WS_DOWN:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        tap_code(KC_DOWN);
        unregister_code(KC_LCTL);
      }
      return false;

    // Word navigation shortcuts
    case WORD_LEFT:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_LEFT);
        unregister_code(KC_LALT);
      }
      return false;

    case WORD_RIGHT:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_RIGHT);
        unregister_code(KC_LALT);
      }
      return false;

    case WORD_SELECT:
      if (record->event.pressed) {
        // Macro: W← W→ Shift+W←
        // Move to beginning of word
        register_code(KC_LALT);
        tap_code(KC_LEFT);
        unregister_code(KC_LALT);
        
        // Move to end of word  
        register_code(KC_LALT);
        tap_code(KC_RIGHT);
        unregister_code(KC_LALT);
        
        // Select back to beginning of word
        register_code(KC_LSFT);
        register_code(KC_LALT);
        tap_code(KC_LEFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
      }
      return false;

    case WORD_DELETE:
      if (record->event.pressed) {
        // Select word first (same as WORD_SELECT)
        register_code(KC_LALT);
        tap_code(KC_LEFT);
        unregister_code(KC_LALT);
        
        register_code(KC_LALT);
        tap_code(KC_RIGHT);
        unregister_code(KC_LALT);
        
        register_code(KC_LSFT);
        register_code(KC_LALT);
        tap_code(KC_LEFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
        
        // Then delete the selection
        tap_code(KC_BSPC);
      }
      return false;

    // Smart brackets with cursor positioning
    case SYM_LPRN:
      if (record->event.pressed) {
        lprn_held = true;
        register_code(KC_LSFT);
        tap_code(KC_9);
        unregister_code(KC_LSFT);
      } else {
        lprn_held = false;
      }
      return false;

    case SYM_RPRN:
      if (record->event.pressed) {
        if (lprn_held) {
          // Smart positioning: type ) and move cursor back
          register_code(KC_LSFT);
          tap_code(KC_0);
          unregister_code(KC_LSFT);
          tap_code(KC_LEFT);
        } else {
          register_code(KC_LSFT);
          tap_code(KC_0);
          unregister_code(KC_LSFT);
        }
      }
      return false;

    case SYM_LBRC:
      if (record->event.pressed) {
        lbrc_held = true;
        tap_code(KC_LBRC);
      } else {
        lbrc_held = false;
      }
      return false;

    case SYM_RBRC:
      if (record->event.pressed) {
        if (lbrc_held) {
          // Smart positioning: type ] and move cursor back
          tap_code(KC_RBRC);
          tap_code(KC_LEFT);
        } else {
          tap_code(KC_RBRC);
        }
      }
      return false;

    case SYM_LCBR:
      if (record->event.pressed) {
        lcbr_held = true;
        register_code(KC_LSFT);
        tap_code(KC_LBRC);
        unregister_code(KC_LSFT);
      } else {
        lcbr_held = false;
      }
      return false;

    case SYM_RCBR:
      if (record->event.pressed) {
        if (lcbr_held) {
          // Smart positioning: type } and move cursor back
          register_code(KC_LSFT);
          tap_code(KC_RBRC);
          unregister_code(KC_LSFT);
          tap_code(KC_LEFT);
        } else {
          register_code(KC_LSFT);
          tap_code(KC_RBRC);
          unregister_code(KC_LSFT);
        }
      }
      return false;

    case SYM_LABK:
      if (record->event.pressed) {
        labk_held = true;
        register_code(KC_LSFT);
        tap_code(KC_COMM);
        unregister_code(KC_LSFT);
      } else {
        labk_held = false;
      }
      return false;

    case SYM_RABK:
      if (record->event.pressed) {
        if (labk_held) {
          // Smart positioning: type > and move cursor back
          register_code(KC_LSFT);
          tap_code(KC_DOT);
          unregister_code(KC_LSFT);
          tap_code(KC_LEFT);
        } else {
          register_code(KC_LSFT);
          tap_code(KC_DOT);
          unregister_code(KC_LSFT);
        }
      }
      return false;

    // Emoji keycodes
    case EM_WAVE:
      if (record->event.pressed) {
        send_unicode_string("👋");
        layer_off(_EMOJI);
      }
      return false;
    case EM_HEART:
      if (record->event.pressed) {
        send_unicode_string("❤️");
        layer_off(_EMOJI);
      }
      return false;
    case EM_SMILE:
      if (record->event.pressed) {
        send_unicode_string("😊");
        layer_off(_EMOJI);
      }
      return false;
    case EM_LAUGH:
      if (record->event.pressed) {
        send_unicode_string("😂");
        layer_off(_EMOJI);
      }
      return false;
    case EM_THINK:
      if (record->event.pressed) {
        send_unicode_string("🤔");
        layer_off(_EMOJI);
      }
      return false;
    case EM_PARTY:
      if (record->event.pressed) {
        send_unicode_string("🎉");
        layer_off(_EMOJI);
      }
      return false;
    case EM_FIRE:
      if (record->event.pressed) {
        send_unicode_string("🔥");
        layer_off(_EMOJI);
      }
      return false;
    case EM_THUMBS:
      if (record->event.pressed) {
        send_unicode_string("👍");
        layer_off(_EMOJI);
      }
      return false;
    case EM_EYES:
      if (record->event.pressed) {
        send_unicode_string("👀");
        layer_off(_EMOJI);
      }
      return false;
    case EM_CRY:
      if (record->event.pressed) {
        send_unicode_string("😢");
        layer_off(_EMOJI);
      }
      return false;
    case EM_COOL:
      if (record->event.pressed) {
        send_unicode_string("😎");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ANGRY:
      if (record->event.pressed) {
        send_unicode_string("😡");
        layer_off(_EMOJI);
      }
      return false;
    case EM_KISS:
      if (record->event.pressed) {
        send_unicode_string("😘");
        layer_off(_EMOJI);
      }
      return false;
    case EM_WINK:
      if (record->event.pressed) {
        send_unicode_string("😉");
        layer_off(_EMOJI);
      }
      return false;
    case EM_JOY:
      if (record->event.pressed) {
        send_unicode_string("😄");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ROCKET:
      if (record->event.pressed) {
        send_unicode_string("🚀");
        layer_off(_EMOJI);
      }
      return false;
    case EM_BOOM:
      if (record->event.pressed) {
        send_unicode_string("💥");
        layer_off(_EMOJI);
      }
      return false;
    case EM_DIZZY:
      if (record->event.pressed) {
        send_unicode_string("😵");
        layer_off(_EMOJI);
      }
      return false;
    case EM_MONEY:
      if (record->event.pressed) {
        send_unicode_string("💰");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ZZZ:
      if (record->event.pressed) {
        send_unicode_string("😴");
        layer_off(_EMOJI);
      }
      return false;
    case EM_NERD:
      if (record->event.pressed) {
        send_unicode_string("🤓");
        layer_off(_EMOJI);
      }
      return false;
    case EM_GHOST:
      if (record->event.pressed) {
        send_unicode_string("👻");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ALIEN:
      if (record->event.pressed) {
        send_unicode_string("👽");
        layer_off(_EMOJI);
      }
      return false;
    case EM_VICTORY:
      if (record->event.pressed) {
        send_unicode_string("✌️");
        layer_off(_EMOJI);
      }
      return false;
    case EM_QUESTION:
      if (record->event.pressed) {
        send_unicode_string("❓");
        layer_off(_EMOJI);
      }
      return false;
    case EM_YES:
      if (record->event.pressed) {
        send_unicode_string("✅");
        layer_off(_EMOJI);
      }
      return false;
    case EM_CHECK:
      if (record->event.pressed) {
        send_unicode_string("✓");
        layer_off(_EMOJI);
      }
      return false;
    case EM_CROSS:
      if (record->event.pressed) {
        send_unicode_string("✗");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ARROW_L:
      if (record->event.pressed) {
        send_unicode_string("←");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ARROW_R:
      if (record->event.pressed) {
        send_unicode_string("→");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ARROW_U:
      if (record->event.pressed) {
        send_unicode_string("↑");
        layer_off(_EMOJI);
      }
      return false;
    case EM_ARROW_D:
      if (record->event.pressed) {
        send_unicode_string("↓");
        layer_off(_EMOJI);
      }
      return false;
    case EM_QUOTE_L:
      if (record->event.pressed) {
        send_unicode_string("\"");
        layer_off(_EMOJI);
      }
      return false;
    case EM_QUOTE_R:
      if (record->event.pressed) {
        send_unicode_string("\"");
        layer_off(_EMOJI);
      }
      return false;
    case EM_APOS_L:
      if (record->event.pressed) {
        send_unicode_string("'");
        layer_off(_EMOJI);
      }
      return false;
    case EM_APOS_R:
      if (record->event.pressed) {
        send_unicode_string("'");
        layer_off(_EMOJI);
      }
      return false;
    case EM_POINT_U:
      if (record->event.pressed) {
        send_unicode_string("👆");
        layer_off(_EMOJI);
      }
      return false;
    case EM_POINT_D:
      if (record->event.pressed) {
        send_unicode_string("👇");
        layer_off(_EMOJI);
      }
      return false;
    case EM_POINT_L:
      if (record->event.pressed) {
        send_unicode_string("👈");
        layer_off(_EMOJI);
      }
      return false;
    case EM_POINT_R:
      if (record->event.pressed) {
        send_unicode_string("👉");
        layer_off(_EMOJI);
      }
      return false;
      
    // Spanish character cases
    case ES_A:
      if (record->event.pressed) {
        send_unicode_string("á");
        layer_off(_SPANISH);
      }
      return false;
    case ES_E:
      if (record->event.pressed) {
        send_unicode_string("é");
        layer_off(_SPANISH);
      }
      return false;
    case ES_I:
      if (record->event.pressed) {
        send_unicode_string("í");
        layer_off(_SPANISH);
      }
      return false;
    case ES_O:
      if (record->event.pressed) {
        send_unicode_string("ó");
        layer_off(_SPANISH);
      }
      return false;
    case ES_U:
      if (record->event.pressed) {
        send_unicode_string("ú");
        layer_off(_SPANISH);
      }
      return false;
    case ES_N:
      if (record->event.pressed) {
        send_unicode_string("ñ");
        layer_off(_SPANISH);
      }
      return false;
    case ES_EXCL:
      if (record->event.pressed) {
        send_unicode_string("¡");
        layer_off(_SPANISH);
      }
      return false;
    case ES_QUEST:
      if (record->event.pressed) {
        send_unicode_string("¿");
        layer_off(_SPANISH);
      }
      return false;
      
    case ROTATE_DISPLAY:
      if (record->event.pressed) {
        force_display_rotation();
      }
      return false;
      
    case SPANISH_PICKER:
      if (record->event.pressed) {
        // Activate Spanish one-shot layer
        layer_on(_SPANISH);
      }
      return false;
      
    case EMOJI_PICKER:
      if (record->event.pressed) {
        if (emoji_key_timer > 0 && timer_elapsed(emoji_key_timer) < TAPPING_TERM) {
          // Double tap detected - launch macOS emoji picker
          layer_off(_EMOJI);  // Make sure emoji layer is off
          register_code(KC_LGUI);
          register_code(KC_LCTL);
          tap_code(KC_SPC);
          unregister_code(KC_LCTL);
          unregister_code(KC_LGUI);
          emoji_key_timer = 0;
        } else {
          // Single tap - activate emoji layer
          layer_on(_EMOJI);
          emoji_key_timer = timer_read();
        }
      }
      return false;
  }
  
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
