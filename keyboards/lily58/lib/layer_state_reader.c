#include "action_layer.h"
#include <stdio.h>

// Layer numbers (matching keymap.c enum layer_number)
#define L_QWERTY 0
#define L_SHIFT 1
#define L_SYMBOLS 2
#define L_NAV 3
#define L_RAISE 4
#define L_FUNCTION 5
#define L_SPANISH 6
#define L_MOUSE 7
#define L_EMOJI 8

char layer_state_str[24];

const char *read_layer_state(void) {
  uint8_t current_layer = get_highest_layer(layer_state);
  
  switch (current_layer)
  {
  case L_QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "QWERTY");
    break;
  case L_SHIFT:
    snprintf(layer_state_str, sizeof(layer_state_str), "SHIFT");
    break;
  case L_SYMBOLS:
    snprintf(layer_state_str, sizeof(layer_state_str), "SYMBOLS");
    break;
  case L_NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "NAV");
    break;
  case L_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "RAISE");
    break;
  case L_FUNCTION:
    snprintf(layer_state_str, sizeof(layer_state_str), "FUNCTION");
    break;
  case L_SPANISH:
    snprintf(layer_state_str, sizeof(layer_state_str), "ESPANOL");
    break;
  case L_MOUSE:
    snprintf(layer_state_str, sizeof(layer_state_str), "MOUSE");
    break;
  case L_EMOJI:
    snprintf(layer_state_str, sizeof(layer_state_str), "EMOJI");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Undef");
  }

  return layer_state_str;
}
