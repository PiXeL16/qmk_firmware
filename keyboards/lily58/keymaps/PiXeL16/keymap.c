#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
// #include "sm_td.h"  // Commented out - not using SM_TD

#ifdef WPM_ENABLE
#include "wpm.h"
#include "motivational_messages.h"
#endif

#ifdef OLED_ENABLE
#include "oled_images.h"
#include "bongocat_animation.h"
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
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  // Set unicode input mode for macOS - commented out since emoji functionality is disabled
  // set_unicode_input_mode(UNICODE_MODE_MACOS);
  
#ifdef WPM_ENABLE
  motivational_init();
#endif

#ifdef OLED_ENABLE
  oled_images_init();
  bongocat_init();
#endif
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

// Per-key tapping term configuration - simplified since space is now handled by SM_TD
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return TAPPING_TERM;  // Default 200ms for everything
}

// Per-key hold on other key press configuration - simplified since space is now handled by SM_TD
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return false; // Default behavior for all keys
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
const char *read_keylogs(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // Left OLED - Simple display: layer, WPM, keylog, motivational messages
    
#ifdef WPM_ENABLE
    // Update motivational message state
    motivational_update();
#endif
    
    oled_write_ln(read_layer_state(), false);
    
#ifdef WPM_ENABLE
    char wpm_str[32];
    sprintf(wpm_str, "WPM:%03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
    
    // Show motivational message if active, otherwise show keylogs
    if (motivational_should_show_message()) {
      oled_write("", false); // Empty line for spacing
      oled_write_ln(motivational_get_current_message(), true); // Inverted text for emphasis
    } else {
      oled_write_ln(read_keylogs(), false);
    }
#else
    oled_write_ln(read_keylogs(), false);
#endif

  } else {
    // Right OLED - Rotating Images and bongo cat
    oled_images_update();
    
    uint8_t current_image = oled_images_get_current();
    
    // Clear screen when switching to/from bongo cat
    if (oled_images_should_clear_for_bongocat()) {
      oled_clear();
      if (current_image == 3) {
        bongocat_reset_for_display();
      }
    }
    
    if (current_image == 3) {
      // Bongo cat animation (case 3)
      bongocat_draw();
    } else {
      // Static images (cases 0-2)
      oled_images_draw_current();
    }
  }
  return false;
}
#endif // OLED_ENABLE
