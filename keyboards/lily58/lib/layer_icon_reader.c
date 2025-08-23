#include "action_layer.h"
#include <stdio.h>

// Simple text-based layer indicators for better visibility
static const char layer_text_icons[][64] = {
  // QWERTY Layer - Keyboard representation
  [0] = " QWER \n ASDF \n ZXCV \n      ",
  // SHIFT Layer - Up arrow
  [1] = "  ^   \n ^^^  \n  ^   \n SHIFT",  
  // SYMBOLS Layer - Programming symbols
  [2] = " {[]} \n <()> \n +=*/ \n SYMBL",
  // NAV Layer - Navigation arrows  
  [3] = "  ^   \n<   > \n  v   \n  NAV ",
  // RAISE Layer - Numbers
  [4] = " 123  \n 456  \n 789  \n RAISE",
  // FUNCTION Layer - F-keys
  [5] = " F1-6 \n F7-12\n MEDIA\n FUNCT",
  // EMOJI Layer - Smiley
  [6] = "  ^_^ \n (o_o)\n  \\o/ \n EMOJI", 
  // SPANISH Layer - Spanish characters
  [7] = " áéíó \n  ñ   \n ¡¿   \n ESPAÑ",
  // MOUSE Layer - Mouse representation  
  [8] = " ┌─┐ \n │ │ \n └─┘ \n MOUSE"
};



// Layer names for text display
static const char layer_names[][12] = {
  "QWERTY",    // 0
  "SHIFT",     // 1  
  "SYMBOLS",   // 2
  "NAV",       // 3
  "RAISE",     // 4
  "FUNCTION",  // 5
  "EMOJI",     // 6
  "ESPAÑOL",   // 7
  "MOUSE"      // 8
};

const char *read_layer_icon(void) {
  uint8_t current_layer = get_highest_layer(layer_state);
  if (current_layer < 9) {
    return layer_text_icons[current_layer];
  }
  return layer_text_icons[0]; // Default to QWERTY
}

const char *read_layer_name(void) {
  uint8_t current_layer = get_highest_layer(layer_state);
  if (current_layer < 9) {
    return layer_names[current_layer];
  }
  return layer_names[0]; // Default to QWERTY
}
