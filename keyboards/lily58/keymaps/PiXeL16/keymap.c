#include QMK_KEYBOARD_H
#include "keymap_spanish.h"

#ifdef WPM_ENABLE
#include "wpm.h"
#endif

// Function declarations
void set_keylog(uint16_t keycode, keyrecord_t *record);

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
  _EMOJI,
};

enum custom_keycodes {
  // Application navigation shortcuts
  NAV_BACK = SAFE_RANGE,      // Ctrl+[
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
  EMOJI_PICKER,   // Emoji layer picker
  ES_A_ACCENT,    // á (dead key + a)
  ES_E_ACCENT,    // é (dead key + e)  
  ES_I_ACCENT,    // í (dead key + i)
  ES_O_ACCENT,    // ó (dead key + o)
  ES_U_ACCENT     // ú (dead key + u)
};

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

// Emoji unicode map
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
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
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   :  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ;  |   :  |   *  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
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
 * |  `   |  \   |  $   |  {   |  }   |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  <   |  =   |  -   |  (   |  )   |  >   |-------.    ,-------|  ^   |  \   |  %   |  ↑   |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |  [   |  ]   |  +   |-------|    |-------|      |   _  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYMBOLS] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  KC_GRV, KC_BSLS, KC_DLR,  SYM_LCBR, SYM_RCBR, _______,                   _______, _______, _______, _______, _______, _______,
  SYM_LABK, KC_EQL, KC_MINS, SYM_LPRN, SYM_RPRN, SYM_RABK,                   KC_CIRC, KC_BSLS, KC_PERC, KC_UP, _______, _______,
  _______, _______, _______, SYM_LBRC, SYM_RBRC, KC_PLUS, _______, _______, _______, KC_UNDS, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* FUNCTION 
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Span | Emoj |      |      |                    |      | Prev | Next | Play | Vol- | Vol+ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      | BrDn | BrUp |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_FUNCTION] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, _______, SPANISH_PICKER, EMOJI_PICKER, _______, _______,       _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, KC_BRMD, KC_BRMU, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
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
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SPANISH] = LAYOUT(
  TO(_QWERTY), _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
  ES_IEXL, _______, _______, ES_E_ACCENT, _______, _______,              _______, ES_U_ACCENT, ES_I_ACCENT, ES_O_ACCENT, _______, ES_IQUE,
  _______, ES_A_ACCENT, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, ES_NTIL, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* MOUSE (Mouse Control)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | WhUp |      |      |      |                    |      | MsUp |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LClk | WhDn | RClk |      |      |-------.    ,-------|MsLeft|MsDown|MsUp  |MsRght|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | MClk |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_MOUSE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
  _______, _______, KC_MS_WH_UP, _______, _______, _______,              _______, KC_MS_UP, _______, _______, _______, _______,
  _______, KC_MS_BTN1, KC_MS_WH_DOWN, KC_MS_BTN2, _______, _______,      KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, _______, _______,
  _______, _______, KC_MS_BTN3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), _______, MO(_FUNCTION)
),
/* NAV (Navigation)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | Back | Fwd  |TbPrv |TbNxt |      |                    |      |WS←   |WS→   |WS↑   |WS↓   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |                    |WLeft | WUp  |WRight|WSel  |WDel  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift| Left | Down |Right |  $   |  %   |-------.    ,-------| Left | Down |Right |      |   (  |   )  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |  |   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAV] = LAYOUT(
  _______, NAV_BACK, NAV_FORWARD, TAB_PREV, TAB_NEXT, _______,                   _______, WS_LEFT, WS_RIGHT, WS_UP, WS_DOWN, _______,
  _______, _______, KC_UP, _______, _______, _______,                   WORD_LEFT, KC_UP, WORD_RIGHT, WORD_SELECT, WORD_DELETE, _______,
  KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, S(KC_4), S(KC_5),                   KC_LEFT, KC_DOWN, KC_RGHT, _______, S(KC_9), S(KC_0),
  KC_LCTL, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, S(KC_MINS), S(KC_EQL), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
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
                             KC_LALT, LT(_SYMBOLS, KC_LGUI), _______, LT(_SHIFT, KC_SPC), KC_ENT, _______, MO(_MOUSE), MO(_FUNCTION)
),
/* EMOJI (Emojis mapped to QWERTY letter positions)
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
[_EMOJI] = LAYOUT(
  TO(_QWERTY), _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, UM(WAVE), UM(EYES), UM(ROCKET), UM(THINK),                _______, _______, _______, UM(OK), UM(PRAY), _______,
  _______, _______, UM(SMILE), _______, UM(FIRE), UM(GRIN),                    UM(HEART), _______, UM(KISS), UM(LOVE), _______, _______,
  _______, _______, _______, UM(COFFEE), UM(COOL), UM(THMUP), _______, _______, UM(THMDN), UM(MUSIC), _______, UM(POINT), _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  // Set unicode input mode for macOS
  set_unicode_input_mode(UNICODE_MODE_MACOS);
}

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

// Per-key tapping term configuration 
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Space bar shift layer can be more responsive
        case LT(_SHIFT, KC_SPC):
            return 150;  // Shorter for space bar layer-tap
            
        default:
            return TAPPING_TERM;  // Default 200ms for everything else
    }
}

// Per-key hold on other key press configuration
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Disable for space layer-tap to prevent accidental layer activation
        case LT(_SHIFT, KC_SPC):
            return false; // Wait for full tapping term before deciding
            
        default:
            return false; // Default behavior for other keys
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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

    // Spanish accented characters using dead keys
    case ES_A_ACCENT:
      if (record->event.pressed) {
        tap_code(ES_ACUT);  // Dead key for acute accent
        tap_code(KC_A);     // Then press A
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_E_ACCENT:
      if (record->event.pressed) {
        tap_code(ES_ACUT);  // Dead key for acute accent
        tap_code(KC_E);     // Then press E
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_I_ACCENT:
      if (record->event.pressed) {
        tap_code(ES_ACUT);  // Dead key for acute accent
        tap_code(KC_I);     // Then press I
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_O_ACCENT:
      if (record->event.pressed) {
        tap_code(ES_ACUT);  // Dead key for acute accent
        tap_code(KC_O);     // Then press O
        layer_off(_SPANISH);
      }
      return false;
      
    case ES_U_ACCENT:
      if (record->event.pressed) {
        tap_code(ES_ACUT);  // Dead key for acute accent
        tap_code(KC_U);     // Then press U
        layer_off(_SPANISH);
      }
      return false;

    case SPANISH_PICKER:
      if (record->event.pressed) {
        // Activate Spanish one-shot layer
        layer_on(_SPANISH);
      }
      return false;
      
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

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_keylogs(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    
    // Display WPM
    char wpm_str[32];
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
    
    oled_write_ln(read_keylogs(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE