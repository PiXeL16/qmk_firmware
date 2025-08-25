#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
// #include "sm_td.h"  // Commented out - not using SM_TD

#ifdef WPM_ENABLE
#include "wpm.h"
#endif

// Function declarations
void set_keylog(uint16_t keycode, keyrecord_t *record);

// Motivational messages for high WPM
static const char* motivational_messages[] = {
    "You sexy beast!",
    "You are on fire!",
    "Unstoppable!",
    "Speed demon!",
    "Beast mode: ON",
    "Crushing it!",
    "Blazing fast!",
    "Fingers of fury!",
    "RAMPAGE!",
    "DOMINATING!"
};

// WPM motivation tracking
static bool show_motivational_msg = false;
static uint32_t motivational_msg_timer = 0;
static uint8_t current_message_index = 0;
static bool was_above_90_wpm = false;

// Removed Luna functionality to save space

// Smart bracket state tracking
static bool lprn_held = false;
static bool lbrc_held = false;
static bool lcbr_held = false;
static bool labk_held = false;

enum layer_number {
  _QWERTY = 0,
  _SHIFT,
  _SYMBOLS,
  _NAV,
  _RAISE,
  _FUNCTION,
  _SPANISH,
  _MOUSE,
  // _EMOJI,  // Commented out to save memory for SM_TD
};

enum custom_keycodes {
  // Application navigation shortcuts
  NAV_BACK = SAFE_RANGE,      // Cmd+[
  NAV_FORWARD,   // Cmd+]
  TAB_PREV,      // Cmd+Shift+[
  TAB_NEXT,      // Cmd+Shift+]
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
  // Smart brackets (with caret repositioning)
  SYM_LPRN,      // Smart (
  SYM_RPRN,      // Smart )
  SYM_LBRC,      // Smart [
  SYM_RBRC,      // Smart ]
  SYM_LCBR,      // Smart {
  SYM_RCBR,      // Smart }
  SYM_LABK,      // Smart <
  SYM_RABK,      // Smart >
  // Spanish layer picker
  SPANISH_PICKER, // Spanish character picker
  ES_A_ACCENT,    // á (alt+e, a)
  ES_E_ACCENT,    // é (alt+e, e)  
  ES_I_ACCENT,    // í (alt+e, i)
  ES_O_ACCENT,    // ó (alt+e, o)
  ES_U_ACCENT,    // ú (alt+e, u)
  ES_ENYE,        // ñ (alt+n, n)
  ES_IEXCL,       // ¡ (alt+1)
  ES_IQUEST       // ¿ (alt+shift+?)
};

// Tap dance definitions removed

// Combo definitions
enum combo_events {
  SPACE_ENTER_COMBO,
  COMBO_LENGTH
};

// Define which keys make up each combo
const uint16_t PROGMEM space_enter_combo[] = {LT(_SHIFT, KC_SPC), KC_ENT, COMBO_END};

// Map combos to their key combinations
combo_t key_combos[] = {
  [SPACE_ENTER_COMBO] = COMBO(space_enter_combo, KC_NO), // KC_NO means we handle it in process_combo_event
};

// Tap dance functions removed - using Spanish layer instead

// Tap dance actions removed

// Emoji unicode map - COMMENTED OUT TO SAVE MEMORY FOR SM_TD
/*
enum unicode_names {
  GRIN,    // 😀 grinning face  
  SMILE,   // 😁 grinning face with smiling eyes
  HEART,   // ❤️ heart
  WINK,    // 😉 wink
  KISS,    // 😘 kiss
  COOL,    // 😎 sunglasses  
  PRAY,    // 🙏 pray
  THMUP,   // 👍 thumbs up
  THMDN,   // 👎 thumbs down
  CLAP,    // 👏 clap
  WAVE,    // 👋 wave
  FIRE,    // 🔥 fire
  ROCKET,  // 🚀 rocket
  EYES,    // 👀 eyes  
  SHRUG,   // 🤷 shrug
  PARTY,   // 🎉 party
  MUSIC,   // 🎵 music
  COFFEE,  // ☕ coffee
  LAUGH,   // 😂 laugh/tears of joy
  LOVE,    // 😍 heart eyes
  CRY,     // 😭 crying
  THINK,   // 🤔 thinking
  OK,      // 👌 ok hand
  POINT,   // 👉 pointing finger
};

// Unicode map array
const uint32_t unicode_map[] PROGMEM = {
  [GRIN] = 0x1F600,    // 😀
  [SMILE] = 0x1F601,   // 😁  
  [HEART] = 0x2764,    // ❤️
  [WINK] = 0x1F609,    // 😉
  [KISS] = 0x1F618,    // 😘
  [COOL] = 0x1F60E,    // 😎
  [PRAY] = 0x1F64F,    // 🙏
  [THMUP] = 0x1F44D,   // 👍
  [THMDN] = 0x1F44E,   // 👎  
  [CLAP] = 0x1F44F,    // 👏
  [WAVE] = 0x1F44B,    // 👋
  [FIRE] = 0x1F525,    // 🔥
  [ROCKET] = 0x1F680,  // 🚀
  [EYES] = 0x1F440,    // 👀
  [SHRUG] = 0x1F937,   // 🤷
  [PARTY] = 0x1F389,   // 🎉
  [MUSIC] = 0x1F3B5,   // 🎵
  [COFFEE] = 0x2615,   // ☕
  [LAUGH] = 0x1F602,   // 😂
  [LOVE] = 0x1F60D,    // 😍
  [CRY] = 0x1F62D,     // 😭
  [THINK] = 0x1F914,   // 🤔
  [OK] = 0x1F44C,      // 👌
  [POINT] = 0x1F449,   // 👉
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |A/Shft|S/Alt |D/Ctrl|F/Cmd |   G  |-------.    ,-------|   H  |J/Cmd |K/Ctrl|L/Alt |;/Shft|  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A, KC_S, KC_D, KC_F, KC_G,                   KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* SHIFT
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   ~  |   @  |   #  |   %  |      |                    |   ^  |   &  |   |  |   \  |      |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   !  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   "  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |A/Shft|S/Alt |D/Ctrl|F/Cmd |   G  |-------.    ,-------|   H  |J/Cmd |K/Ctrl|L/Alt |:/Shft|  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ;  |   :  |   *  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SHIFT] = LAYOUT(
  KC_ESC,   KC_TILD, KC_AT,   KC_HASH, KC_PERC, _______,                   KC_CIRC, KC_AMPR, KC_PIPE, KC_BSLS, _______, KC_BSPC,
  KC_EXLM,  S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T),                   S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), KC_DQUO,
  KC_TAB,   S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),                   S(KC_H), S(KC_J), S(KC_K), S(KC_L), KC_COLN, KC_QUOT,
  KC_LSFT,  S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), KC_LBRC, KC_RBRC, S(KC_N), S(KC_M), KC_SCLN, KC_COLN, KC_ASTR, KC_RSFT,
                             KC_LALT, MO(_NAV), KC_LGUI, KC_SPC, KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* SYMBOLS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |  \   |  $   |  {   |  }   |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  <   |  =   |  -   |  (   |  )   |  >   |-------.    ,-------|  ^   |  \   |  %   |  ↑   |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |  [   |  ]   |  +   |-------|    |-------|      |   _  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYMBOLS] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  KC_GRV, KC_BSLS, KC_DLR,  SYM_LCBR, SYM_RCBR, _______,                   _______, _______, _______, _______, _______, _______,
  SYM_LABK, KC_EQL, KC_MINS, SYM_LPRN, SYM_RPRN, SYM_RABK,                   KC_CIRC, KC_BSLS, KC_PERC, KC_UP, _______, _______,
  _______, _______, _______, SYM_LBRC, SYM_RBRC, KC_PLUS, _______, _______, _______, KC_UNDS, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, KC_SPC, KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* FUNCTION 
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | Emoj |      |      |                    |      | Prev | Next | Play | Vol- | Vol+ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Span |      |      |      |-------.    ,-------|      |      |      |      | BrDn | BrUp |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_FUNCTION] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, _______, _______, /*EMOJI_PICKER*/ _______, _______, _______,       _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU,
  _______, _______, SPANISH_PICKER, _______, _______, _______,                   _______, _______, _______, KC_BRMD, KC_BRMU, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, KC_SPC, KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* SPANISH (Español)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ¡   |      |      |   é  |      |      |                    |      |   ú  |   í  |   ó  |      |   ¿  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   á  |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   ñ  |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SPANISH] = LAYOUT(
  TO(_QWERTY), _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
  ES_IEXCL, _______, _______, ES_E_ACCENT, _______, _______,              _______, ES_U_ACCENT, ES_I_ACCENT, ES_O_ACCENT, _______, ES_IQUEST,
  _______, ES_A_ACCENT, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, ES_ENYE, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, KC_SPC, KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),

/* MOUSE (Mouse control and navigation)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |WheelU|  Up  |WheelD|      |-------.    ,-------|      | Btn1 | Btn3 | Btn2 |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | Left | Down |Right |      |-------|    |-------|      |WheelL|WheelD|WheelU|WheelR|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_MOUSE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______,                   _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                   _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, KC_SPC, KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* NAV (Navigation)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | Back | Fwd  |TbPrv |TbNxt |      |                    |WS←   |WS→   |WS↑   |WS↓   |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |                    |WLeft | WUp  |WRight|WSel  |WDel  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift| Left | Down |Right |  $   |  %   |-------.    ,-------| Left | Down |Right |      |   (  |   )  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |  |   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAV] = LAYOUT(
  _______, NAV_BACK, NAV_FORWARD, TAB_PREV, TAB_NEXT, _______,                   WS_LEFT, WS_RIGHT, WS_UP, WS_DOWN, _______, _______,
  _______, _______, KC_UP, _______, _______, _______,                   WORD_LEFT, KC_UP, WORD_RIGHT, WORD_SELECT, WORD_DELETE, _______,
  KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, S(KC_4), S(KC_5),                   KC_LEFT, KC_DOWN, KC_RGHT, _______, S(KC_9), S(KC_0),
  KC_LCTL, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, S(KC_MINS), S(KC_EQL), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),
                             KC_LALT, MO(_NAV), KC_LGUI, KC_SPC, KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |   4  |   5  |   6  |      |      |
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
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
  KC_LSFT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX,
  KC_LSFT, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_LCTL, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______, S(KC_EQL), KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             KC_LALT, LT(_SYMBOLS, KC_LGUI), _______, KC_SPC, KC_ENT, _______, _______, MO(_FUNCTION)
),
/* EMOJI (Emojis mapped to QWERTY letter positions) - COMMENTED OUT TO SAVE MEMORY FOR SM_TD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Wave | Eyes |Rocket|Think |                    |      |      |      | OK   |Pray  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |Smile |      | Fire | Grin |-------.    ,-------|Heart |      | Kiss |Love  |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |Coffee| Cool | Thumbup-------|    |-------Thumbdn|Music |      |Point |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
/*
[_EMOJI] = LAYOUT(
  TO(_QWERTY), _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, UM(WAVE), UM(EYES), UM(ROCKET), UM(THINK),                _______, _______, _______, UM(OK), UM(PRAY), _______,
  _______, _______, UM(SMILE), _______, UM(FIRE), UM(GRIN),                    UM(HEART), _______, UM(KISS), UM(LOVE), _______, _______,
  _______, _______, _______, UM(COFFEE), UM(COOL), UM(THMUP), _______, _______, UM(THMDN), UM(MUSIC), _______, UM(POINT), _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, KC_SPC, KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
)
*/
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  // Set unicode input mode for macOS - commented out since emoji functionality is disabled
  // set_unicode_input_mode(UNICODE_MODE_MACOS);
}

// SM_TD Home Row Modifiers configuration - COMMENTED OUT
// smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
//   switch (keycode) {
//     // Left hand home row modifiers (ASDF)
//     SMTD_MT(KC_A, KC_LSFT)  // A = Shift (pinky)
//     SMTD_MT(KC_S, KC_LALT)  // S = Alt (ring finger)
//     SMTD_MT(KC_D, KC_LCTL)  // D = Ctrl (middle finger)
//     SMTD_MT(KC_F, KC_LGUI)  // F = Cmd (index finger)
//     
//     // Right hand home row modifiers (JKL;)
//     SMTD_MT(KC_J, KC_RGUI)  // J = Cmd (index finger)
//     SMTD_MT(KC_K, KC_RCTL)  // K = Ctrl (middle finger) 
//     SMTD_MT(KC_L, KC_RALT)  // L = Alt (ring finger)
//     SMTD_MT(KC_SCLN, KC_RSFT)  // ; = Shift (pinky)
//     
//     // Space bar layer-tap using SM_TD
//     SMTD_LT(KC_SPC, _SHIFT)  // Space = tap for space, hold for SHIFT layer
//   }
//   return SMTD_RESOLUTION_UNHANDLED;
// }

// Combo processing function
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SPACE_ENTER_COMBO:
      if (pressed) {
        // Send Cmd+Space (Spotlight search on macOS)
        register_code(KC_LGUI);
        tap_code(KC_SPC);
        unregister_code(KC_LGUI);
      }
      break;
  }
}

// Per-key tapping term configuration - simplified since space is now handled by SM_TD
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return TAPPING_TERM;  // Default 200ms for everything
}

// Per-key hold on other key press configuration - simplified since space is now handled by SM_TD
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return false; // Default behavior for all keys
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // SM_TD processing commented out - not using home row modifiers
  // if (!process_smtd(keycode, record)) {
  //   return false;
  // }
  
  switch (keycode) {
    // Application navigation shortcuts
    case NAV_BACK:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_LBRC);
        unregister_code(KC_LGUI);
      }
      return false;
      
    case NAV_FORWARD:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_RBRC);
        unregister_code(KC_LGUI);
      }
      return false;
      
    case TAB_PREV:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_LBRC);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
      }
      return false;
      
    case TAB_NEXT:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_RBRC);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
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
        
        // Move to end of word while selecting
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_RIGHT);
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
        register_code(KC_LSFT);
        tap_code(KC_RIGHT);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
        
        // Then delete the selection
        tap_code(KC_BSPC);
      }
      return false;

    // Smart bracket functionality with caret repositioning
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
        register_code(KC_LSFT);
        tap_code(KC_0);
        unregister_code(KC_LSFT);
        if (lprn_held) {
          tap_code(KC_LEFT);  // Reposition cursor inside brackets
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
        tap_code(KC_RBRC);
        if (lbrc_held) {
          tap_code(KC_LEFT);
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
        register_code(KC_LSFT);
        tap_code(KC_RBRC);
        unregister_code(KC_LSFT);
        if (lcbr_held) {
          tap_code(KC_LEFT);
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
        register_code(KC_LSFT);
        tap_code(KC_DOT);
        unregister_code(KC_LSFT);
        if (labk_held) {
          tap_code(KC_LEFT);
        }
      }
      return false;

    // Spanish accented characters using Alt+key combinations (macOS)
    case ES_A_ACCENT:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_E);  // Alt+E for acute accent
        unregister_code(KC_LALT);
        tap_code(KC_A);  // Then press A
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_E_ACCENT:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_E);  // Alt+E for acute accent
        unregister_code(KC_LALT);
        tap_code(KC_E);  // Then press E
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_I_ACCENT:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_E);  // Alt+E for acute accent
        unregister_code(KC_LALT);
        tap_code(KC_I);  // Then press I
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_O_ACCENT:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_E);  // Alt+E for acute accent
        unregister_code(KC_LALT);
        tap_code(KC_O);  // Then press O
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_U_ACCENT:
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_E);  // Alt+E for acute accent
        unregister_code(KC_LALT);
        tap_code(KC_U);  // Then press U
        layer_off(_SPANISH);
      }
      return false;

    case ES_ENYE:  // ñ
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_N);  // Alt+N for tilde accent
        unregister_code(KC_LALT);
        tap_code(KC_N);  // Then press N
        layer_off(_SPANISH);
      }
      return false;

    case ES_IEXCL:  // ¡
      if (record->event.pressed) {
        register_code(KC_LALT);
        tap_code(KC_1);  // Alt+1 for ¡
        unregister_code(KC_LALT);
        layer_off(_SPANISH);
      }
      return false;

    case ES_IQUEST:  // ¿
      if (record->event.pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_SLSH);  // Alt+Shift+? for ¿
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        layer_off(_SPANISH);
      }
      return false;

    case SPANISH_PICKER:
      if (record->event.pressed) {
        // Activate Spanish one-shot layer
        layer_on(_SPANISH);
      }
      return false;
      
    // EMOJI_PICKER case commented out to save memory for SM_TD
    /*
    case EMOJI_PICKER:
      {
        static uint16_t emoji_timer = 0;
        static uint8_t emoji_tap_count = 0;
        
        if (record->event.pressed) {
          emoji_tap_count++;
          emoji_timer = timer_read();
          
          if (emoji_tap_count == 1) {
            // First tap - activate one-shot emoji layer
            layer_on(_EMOJI);
          } else if (emoji_tap_count == 2) {
            // Double tap - open system emoji picker (Ctrl+Cmd+Space on macOS)
            layer_off(_EMOJI); // Turn off the emoji layer first
            register_code(KC_LCTL);
            register_code(KC_LGUI);
            tap_code(KC_SPC);
            unregister_code(KC_LGUI);
            unregister_code(KC_LCTL);
            emoji_tap_count = 0;
          }
        } else {
          // Check if enough time has passed to reset tap count
          if (timer_elapsed(emoji_timer) > 300 && emoji_tap_count == 1) {
            emoji_tap_count = 0;
          }
        }
        return false;
      }
    */
  }
  
  
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
  }
  return true;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

/* Bongocat animation - more space-efficient implementation */
#include "matrix.h"
extern matrix_row_t matrix[MATRIX_ROWS];

#define ANIM_FRAME_DURATION 100
#define IDLE_FRAMES 5
#define IDLE_TIMEOUT 750
#define SLEEP_TIMEOUT 15000



static const uint8_t bongofont[] PROGMEM = { \
    0xC1, 0xC1, 0xC2, 0x04, 0x08, 0x10, \
    0xC0, 0x38, 0x04, 0x03, 0x00, 0x00, \
    0xA0, 0x22, 0x24, 0x14, 0x12, 0x12, \
    0xA0, 0x21, 0x22, 0x12, 0x11, 0x11, \
    0x83, 0x7C, 0x41, 0x41, 0x40, 0x40, \
    0x82, 0x82, 0x84, 0x08, 0x10, 0x20, \
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, \
    0x80, 0x70, 0x19, 0x06, 0x00, 0x00, \
    0x80, 0x70, 0x0C, 0x03, 0x00, 0x00, \
    0x80, 0x00, 0x30, 0x30, 0x00, 0xC0, \
    0x80, 0x00, 0x30, 0x30, 0x00, 0x00, \
    0x49, 0x88, 0x08, 0x08, 0x08, 0x00, \
    0x44, 0x84, 0x04, 0x04, 0x00, 0x00, \
    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, \
    0x40, 0x40, 0x20, 0x20, 0x20, 0x20, \
    0x3C, 0xC2, 0x01, 0x01, 0x02, 0x02, \
    0x35, 0x01, 0x8A, 0x7C, 0x00, 0x00, \
    0x20, 0x40, 0x80, 0x00, 0x00, 0x00, \
    0x20, 0x21, 0x22, 0x12, 0x11, 0x11, \
    0x20, 0x20, 0x10, 0x10, 0x10, 0x10, \
    0x1E, 0xE1, 0x00, 0x00, 0x01, 0x01, \
    0x1C, 0xE2, 0x01, 0x01, 0x02, 0x02, \
    0x18, 0x64, 0x82, 0x02, 0x02, 0x02, \
    0x18, 0x60, 0x80, 0x00, 0x00, 0x00, \
    0x18, 0x18, 0x1B, 0x03, 0x00, 0x40, \
    0x18, 0x06, 0x05, 0x98, 0x99, 0x84, \
    0x12, 0x0B, 0x08, 0x08, 0x08, 0x08, \
    0x11, 0x09, 0x08, 0x08, 0x08, 0x08, \
    0x10, 0x10, 0xD0, 0x11, 0x0F, 0x21, \
    0x10, 0x10, 0x10, 0x11, 0x0F, 0x01, \
    0x10, 0x08, 0x08, 0x04, 0x04, 0x04, \
    0x10, 0x08, 0x04, 0x02, 0x02, 0x04, \
    0x0C, 0x30, 0x40, 0x80, 0x00, 0x00, \
    0x0C, 0x0C, 0x0D, 0x01, 0x00, 0x40, \
    0x08, 0xE8, 0x08, 0x07, 0x10, 0x24, \
    0x08, 0x30, 0x40, 0x80, 0x00, 0x00, \
    0x08, 0x08, 0x08, 0x07, 0x00, 0x00, \
    0x08, 0x08, 0x04, 0x02, 0x02, 0x02, \
    0x08, 0x04, 0x02, 0x01, 0x01, 0x02, \
    0x05, 0x05, 0x09, 0x09, 0x10, 0x10, \
    0x04, 0x38, 0x40, 0x80, 0x00, 0x00, \
    0x04, 0x04, 0x08, 0x08, 0x10, 0x10, \
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, \
    0x04, 0x04, 0x02, 0x01, 0x00, 0x00, \
    0x02, 0x02, 0x81, 0x80, 0x80, 0x00, \
    0x02, 0x02, 0x04, 0x04, 0x08, 0x08, \
    0x02, 0x02, 0x02, 0x01, 0x01, 0x01, \
    0x02, 0x02, 0x01, 0x00, 0x00, 0x00, \
    0x01, 0xE1, 0x1A, 0x06, 0x09, 0x31, \
    0x01, 0x01, 0x02, 0x04, 0x08, 0x10, \
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00, \
    0x00, 0x80, 0x40, 0x40, 0x20, 0x20, \
    0x00, 0x00, 0x80, 0x80, 0x40, 0x40, \
    0x00, 0x00, 0x60, 0x60, 0x00, 0x81, \
    0x00, 0x00, 0x01, 0x01, 0x00, 0x40, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 

static const uint8_t bongo_line_x[] = {51, 49, 48, 57};
static const uint8_t bongo_line_y[] = {0, 8, 16, 24};
static const uint8_t bongo_line_len[] = {5, 7, 8, 6};

const uint8_t bongo_line_data[8][26] PROGMEM = {
    { //idle1
    60, 52, 19, 30, 35, \
    22, 47, 51, 60, 9, 0, 17, \
    1, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle2
    60, 52, 19, 30, 35, \
    22, 47, 51, 60, 9, 0, 17, \
    1, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle3
    60, 53, 14, 31, 23, \
    15, 43, 60, 60, 54, 5, 13, \
    7, 56, 24, 2, 26, 39, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle4
    6, 52, 19, 38, 32, \
    20, 47, 51, 60, 9, 0, 17, \
    8, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle5
    60, 52, 19, 37, 40, \
    21, 47, 51, 60, 9, 0, 17, \
    8, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //prep
    6, 52, 19, 38, 32, \
    20, 44, 51, 60, 10, 48, 16, \
    8, 25, 4, 18, 27, 42, 46, 50, \
    60, 60, 60, 60, 60, 60}, \
    { //tap1
    6, 52, 19, 38, 32, \
    20, 44, 51, 60, 10, 49, 17, \
    8, 25, 4, 18, 27, 41, 28, 11, \
    60, 60, 60, 60, 58, 59}, \
    { //tap2
    6, 52, 19, 38, 32, \
    20, 47, 51, 60, 10, 48, 16, \
    8, 60, 55, 3, 27, 42, 46, 50, \
    45, 34, 12, 60, 60, 60}
};

enum anin_states { sleep, idle, prep, tap };
uint8_t anim_state = idle;
uint32_t idle_timeout_timer = 0;
uint32_t anim_timer = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 6;
uint8_t last_bongo_frame = 12;

void write_bongochar_at_pixel_xy(uint8_t x, uint8_t y, uint8_t data, bool invert) {
    uint8_t i, j, temp;
    for (i = 0; i < 6 ; i++) { // 6 = font width
        temp = pgm_read_byte(&bongofont[data * 6]+i);
        for (j = 0; j < 8; j++) {  // 8 = font height
            if (temp & 0x01) {
                oled_write_pixel(x + i, y + j, !invert);
            } else {
                oled_write_pixel(x + i, y + j, invert);
            }
            temp >>= 1;
        }
    }
}

bool is_key_down(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > 0) {
            return true;
        }
    }
    return false;
}

void eval_anim_state(void) {
    bool key_down;
    key_down = is_key_down();

    switch (anim_state) {
        case sleep:
            if(key_down) { anim_state = tap; }
            break; 
        case idle:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= SLEEP_TIMEOUT) //prep to idle
                {
                    anim_state = sleep;
                    current_idle_frame = 0;
                }
            break;
        case prep:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= IDLE_TIMEOUT) //prep to idle
                {
                    anim_state = idle;
                    current_idle_frame = 0;
                }
            break;
        case tap:
            if (!key_down)
            {
                anim_state = prep;
                idle_timeout_timer = timer_read32();
            }
            break;
        default:
            break;
    }
}

void draw_bongo_table(void) {
    //draws the table edge for bongocat, this edge doesn't change during the animation
    uint8_t i;
    uint8_t y = 31;
    uint8_t j = 0;
    for (i = 17; i < 57; i++) {
        oled_write_pixel(i, y, true); //every five horizontal pixels, move up one pixel to make a diagonal line
        if (j == 4) {
            --y;
            j=0;
        } else {
            j++;
        }
    }

    y=15;
    j=0;
    for (i = 91; i < 128; i++) {

        oled_write_pixel(i, y, true); //every four horizontal pixels, move up one pixel to make a diagonal line
        if (j == 3) {
            --y;
            j=0;
        } else {
            j++;
        }
    }
}

void draw_bongocat_frame(int framenumber) {
    //only redraw if the animation frame has changed
    if (framenumber != last_bongo_frame) {
        last_bongo_frame = framenumber;
        uint8_t i, j, current_bongochar = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < bongo_line_len[i]; j++) {
                write_bongochar_at_pixel_xy(bongo_line_x[i] + j*6, bongo_line_y[i], pgm_read_byte(&bongo_line_data[framenumber][current_bongochar]), false);
                current_bongochar++;
            }
        }
    }
}

bool is_new_tap(void) {
    // Use WPM and last activity time to detect typing from both halves
    static uint8_t last_wpm = 0;
    
    uint8_t current_wpm = get_current_wpm();
    uint32_t current_time = timer_read32();
    
    // Check if WPM changed or if we have recent activity
    bool wpm_changed = (current_wpm != last_wpm);
    bool recent_activity = (current_time - last_input_activity_time()) < 100; // 100ms threshold
    
    // Also check local matrix for immediate response on this side
    static matrix_row_t old_matrix[MATRIX_ROWS] = {0};
    bool local_tap = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > old_matrix[i]) {
            local_tap = true;
        }
        old_matrix[i] = matrix[i];
    }
    
    if (wpm_changed || recent_activity || local_tap) {
        last_wpm = current_wpm;
        return true;
    }
    
    return false;
}

void draw_bongocat(void) {
    static bool already_tapped = false;
    if (is_new_tap()) {
        already_tapped = false;
    };
    eval_anim_state();
    switch (anim_state) {
        case sleep:
            draw_bongocat_frame(4);
            break;
        case idle:       
            draw_bongocat_frame(4 - current_idle_frame);
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                current_idle_frame = (current_idle_frame + 1) % 5;
                anim_timer = timer_read32();
            }
            break;
        case prep:
            draw_bongocat_frame(5);
            already_tapped = false;
            break;
        case tap:
            draw_bongocat_frame(current_tap_frame);
            if (already_tapped == false) {
                if (current_tap_frame == 6) {
                    current_tap_frame = 7;
                }
                else {
                    current_tap_frame = 6;
                }
            }
            already_tapped = true;
            break;
        default:
            draw_bongocat_frame(4);
            already_tapped = false;
            break;

    }
}

void update_motivational_message(void) {
    uint8_t current_wpm = get_current_wpm();
    uint32_t current_time = timer_read32();
    
    // Check if WPM crosses the 90 threshold
    if (current_wpm >= 90 && !was_above_90_wpm) {
        // Just crossed above 90 WPM - show new message
        was_above_90_wpm = true;
        show_motivational_msg = true;
        motivational_msg_timer = current_time;
        
        // Select a random message (using timer as pseudo-random seed)
        current_message_index = (current_time / 1000) % (sizeof(motivational_messages) / sizeof(motivational_messages[0]));
    } else if (current_wpm < 90 && was_above_90_wpm) {
        // Dropped below 90 WPM
        was_above_90_wpm = false;
    }
    
    // Hide message after 3 seconds
    if (show_motivational_msg && timer_elapsed32(motivational_msg_timer) > 3000) {
        show_motivational_msg = false;
    }
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_keylogs(void);


bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // Left OLED - Simple display: layer, WPM, keylog, motivational messages
    
    // Update motivational message state
    update_motivational_message();
    
    oled_write_ln(read_layer_state(), false);
    
    char wpm_str[32];
    sprintf(wpm_str, "WPM:%03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
    
    // Show motivational message if active, otherwise show keylogs
    if (show_motivational_msg) {
      oled_write("", false); // Empty line for spacing
      oled_write_ln(motivational_messages[current_message_index], true); // Inverted text for emphasis
    } else {
      oled_write_ln(read_keylogs(), false);
    }
  } else {
    // Right OLED - Rotating Images (restored original functionality)
    // Define multiple images for right OLED
    static const char PROGMEM ichigo_logo[] = { 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
      0x81, 0xc1, 0xc1, 0xe1, 0xe1, 0xc1, 0x81, 0x81, 0xc1, 0xe1, 0xe1, 0xc1, 0xc1, 0x81, 0x01, 0x01, 
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x21, 
      0x31, 0xf1, 0xf1, 0xb1, 0xa1, 0xb1, 0xf1, 0xf1, 0x31, 0x01, 0x01, 0xf1, 0xf1, 0x99, 0x99, 0x99, 
      0xf1, 0xf1, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0xc1, 0xc1, 0xe1, 0x61, 0x31, 0x31, 
      0x31, 0x31, 0x61, 0xc1, 0xc1, 0x81, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 
      0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xb8, 0x3c, 0xfc, 0xfc, 0xfc, 0xfc, 0x38, 0x30, 
      0x33, 0xa7, 0x27, 0x0f, 0x9f, 0xdf, 0xc3, 0xc3, 0xdf, 0x1f, 0x0f, 0x27, 0xa7, 0x33, 0x30, 0x38, 
      0xfc, 0xfc, 0xfc, 0xfc, 0x3c, 0x98, 0x18, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x48, 
      0xc8, 0x6f, 0x2f, 0x0a, 0x0a, 0x0a, 0x6f, 0x2f, 0x08, 0x60, 0x60, 0x1f, 0x1f, 0x04, 0x24, 0x64, 
      0x3f, 0x3f, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
      0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x05, 0x05, 0x65, 0x65, 0x64, 0x3c, 0x3d, 0x65, 0x65, 
      0x65, 0x65, 0x6d, 0x3c, 0x3c, 0x65, 0x25, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
      0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xe7, 0xf3, 
      0xf3, 0xf9, 0xf9, 0xf8, 0xf9, 0xfb, 0xc3, 0xc3, 0xfb, 0xf8, 0xf8, 0xf9, 0xf9, 0xf3, 0xe3, 0xe7, 
      0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 
      0x00, 0x7c, 0xfe, 0x86, 0x82, 0xc6, 0xc6, 0x44, 0x00, 0x00, 0xfe, 0xfe, 0x10, 0x10, 0x10, 0xfe, 
      0xfe, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0x7c, 0xfe, 0x86, 0x82, 0x92, 0xf6, 0x70, 0x00, 
      0x00, 0x7c, 0xfe, 0x86, 0x82, 0x82, 0xfe, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 
      0x00, 0x7c, 0xfc, 0xfe, 0x82, 0x82, 0xc6, 0xc4, 0x40, 0x00, 0xfe, 0xfe, 0x30, 0x10, 0x10, 0xfe, 
      0xfe, 0xfe, 0x00, 0x80, 0xfe, 0xfe, 0x92, 0x92, 0x92, 0x82, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
      0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 
      0x81, 0x83, 0x83, 0x83, 0x83, 0x81, 0x80, 0x80, 0x81, 0x83, 0x83, 0x83, 0x83, 0x81, 0x81, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff};

    // PiXeL16 logo
    static const char PROGMEM pixel16_logo[] = { 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
      0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 
      0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xe0, 
      0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x80, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xe0, 0xf0, 0xf0, 0xff, 0xff, 0xf8, 0xf0, 0xf0, 0xc0, 
      0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 
      0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0f, 0x7f, 0x7f, 0xf0, 0xf0, 0xf0, 0xf0, 0x7f, 
      0x7f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xf0, 0xf0, 0x10, 0x10, 0x10, 0x10, 0xf0, 0xf0, 
      0xe0, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x1c, 0x3c, 0x0f, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
      0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x87, 0x8f, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x0f, 0x0f, 0xff, 0xff, 0x0f, 0x0f, 0x07, 0x03, 
      0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0e, 0x0e, 
      0x0e, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
      0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xfe, 0xff, 0x0f, 0x0f, 0x0f, 0x0f, 0xfe, 
      0xfe, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c, 0x8f, 0x8f, 
      0x8f, 0x8f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
      0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
      0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
      0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 
      0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 
      0x01, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
      0x01, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Third image
    static const char PROGMEM third_logo[] = {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xf8, 0x20, 0x20, 0x20, 
      0x20, 0x20, 0x20, 0x20, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x60, 0x60, 0xc0, 0xc0, 0xc0, 
      0xc0, 0xc0, 0x40, 0x01, 0x81, 0xc3, 0xe3, 0xf3, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xf3, 0xe3, 
      0xc3, 0x81, 0x81, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9b, 0x9b, 0xda, 0x52, 0x5b, 
      0x5b, 0x4a, 0x42, 0xdb, 0x9b, 0x00, 0x00, 0x00, 0x80, 0x96, 0x92, 0x92, 0x12, 0x52, 0xd2, 0x52, 
      0x52, 0x5f, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
      0x01, 0x03, 0x18, 0x3c, 0x3d, 0x7d, 0x7d, 0xcd, 0xcd, 0xcd, 0xfd, 0xfd, 0xfd, 0xfd, 0x7d, 0x7d, 
      0xf9, 0x7b, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x55, 0x55, 0x55, 0x5d, 
      0x5d, 0x4d, 0x05, 0x45, 0x55, 0x00, 0x00, 0x00, 0x10, 0xb8, 0xb8, 0xa1, 0xb0, 0x99, 0xd9, 0x89, 
      0xb9, 0xb9, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x0f, 0x0f, 0x0f, 
      0x09, 0x09, 0x09, 0x09, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Rotate between all 4 displays (3 images + bongo cat) every 1 minute
    static uint8_t current_logo = 0;
    static uint32_t logo_timer = 0;
    
    // Change logo every 1 minute (60000ms)
    if (timer_elapsed32(logo_timer) > 60000) {
      current_logo = (current_logo + 1) % 4;
      logo_timer = timer_read32();
      
      // Clear screen when switching away from bongo cat or to bongo cat
      if (current_logo == 3 || (current_logo == 0)) {
        oled_clear();
        if (current_logo == 3) {
          last_bongo_frame = 12; //force a redraw for bongo cat
          draw_bongo_table();
        }
      }
    }
    
    switch (current_logo) {
      case 0:
        oled_write_raw_P(ichigo_logo, sizeof(ichigo_logo));
        break;
      case 1:
        oled_write_raw_P(pixel16_logo, sizeof(pixel16_logo));
        break;
      case 2:
        oled_write_raw_P(third_logo, sizeof(third_logo));
        break;
      case 3:
        // Bongo cat animation
        draw_bongocat();
        break;
    }
  }
    return false;
}
#endif // OLED_ENABLE