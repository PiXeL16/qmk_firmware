#include QMK_KEYBOARD_H

// Function declarations
void set_keylog(uint16_t keycode, keyrecord_t *record);

enum layer_number {
  _QWERTY = 0,
  _SHIFT,
  _SYMBOLS,
  _NAV,
  _RAISE,
  _FUNCTION,
  _SPANISH,
  _MOUSE,
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
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
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
  KC_LCTL,  MT(MOD_LSFT, KC_A), MT(MOD_LGUI, KC_S), MT(MOD_LALT, KC_D), KC_F, KC_G, KC_H, KC_J, MT(MOD_RALT, KC_K), MT(MOD_RGUI, KC_L), MT(MOD_RSFT, KC_SCLN), KC_QUOT,
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
 * | ` ~  |  \ | |  $ & |  { } |  " ' |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  < > |  =   |  -   |  (   |  )   |  > < |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |  [   |  ]   |  +   |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYMBOLS] = LAYOUT(
  KC_GRV,  KC_BSLS, KC_DLR,  KC_LCBR, KC_RCBR, _______,                   _______, _______, _______, _______, _______, _______,
  KC_LABK, KC_EQL, KC_MINS, KC_LPRN, KC_RPRN, KC_RABK,                   _______, MT(MOD_RCTL, KC_J), MT(MOD_RALT, KC_K), MT(MOD_RGUI, KC_L), MT(MOD_RSFT, KC_SCLN), _______,
  _______, _______, _______, KC_LBRC, KC_RBRC, KC_PLUS,                   _______, KC_UNDS, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* FUNCTION 
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   S  |      |      |      |                    |      | Prev | Next | Play | Vol- | Vol+ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      | BrDn | BrUp |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_FUNCTION] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, _______, SPANISH_PICKER, _______, _______, _______,       KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, KC_BRMD, KC_BRMU, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT, MO(_NAV), KC_LGUI, LT(_SHIFT, KC_SPC), KC_ENT, MO(_SYMBOLS), MO(_MOUSE), MO(_FUNCTION)
),
/* SPANISH (Español)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |   é  |      |      |                    |      |   ú  |   í  |   ó  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ¡   |      |      |      |      |      |                    |      |      |      |      |      |   ¿  |
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
  TO(_QWERTY), _______, _______, ES_E, _______, _______,              _______, ES_U, ES_I, ES_O, _______, _______,
  ES_EXCL, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, ES_QUEST,
  _______, ES_A, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, ES_N, _______, _______, _______, _______, _______,
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
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |                    |WLeft | WUp  |WRight|WSel  |WDel  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift| Left | Down |Right |  $   |  %   |-------.    ,-------| Left | Down | Right|      |   (  |   )  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |  |   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | NAV  |LGUI| /SPC/SFT/       \Enter \  |SYMBO |MOUSE | FUNC |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAV] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, KC_UP,   _______, _______, _______,                   WORD_LEFT, KC_UP, WORD_RIGHT, WORD_SELECT, WORD_DELETE, _______,
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
 * |LShift|  F1  |  F2  |  F3  |  F4  |  F5  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
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
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return state;
}

void keyboard_post_init_user(void) {
  // Basic initialization
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

    // Spanish accented characters (temporarily using regular chars)
    case ES_A:
      if (record->event.pressed) {
        tap_code(KC_A); // temporary - will add unicode later
        layer_off(_SPANISH);
      }
      return false;
    case ES_E:
      if (record->event.pressed) {
        tap_code(KC_E); // temporary - will add unicode later
        layer_off(_SPANISH);
      }
      return false;
    case ES_I:
      if (record->event.pressed) {
        tap_code(KC_I); // temporary - will add unicode later
        layer_off(_SPANISH);
      }
      return false;
    case ES_O:
      if (record->event.pressed) {
        tap_code(KC_O); // temporary - will add unicode later
        layer_off(_SPANISH);
      }
      return false;
    case ES_U:
      if (record->event.pressed) {
        tap_code(KC_U); // temporary - will add unicode later
        layer_off(_SPANISH);
      }
      return false;
    case ES_N:
      if (record->event.pressed) {
        tap_code(KC_N); // temporary - will add unicode later
        layer_off(_SPANISH);
      }
      return false;
    case ES_EXCL:
      if (record->event.pressed) {
        tap_code(KC_1); // temporary - will add unicode later
        layer_off(_SPANISH);
      }
      return false;
    case ES_QUEST:
      if (record->event.pressed) {
        tap_code(KC_SLSH); // temporary - will add unicode later
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
const char *read_logo(void);
const char *read_keylog(void);
const char *read_keylogs(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE