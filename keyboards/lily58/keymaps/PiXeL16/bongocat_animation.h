#pragma once
#include "quantum.h"

#ifdef OLED_ENABLE

// Configuration
#define ANIM_FRAME_DURATION 100
#define IDLE_FRAMES 5
#define IDLE_TIMEOUT 750
#define SLEEP_TIMEOUT 15000

// Animation states
enum anim_states { 
    sleep, 
    idle, 
    prep, 
    tap 
};

// Bongo cat data
extern const uint8_t bongofont[] PROGMEM;
extern const uint8_t bongo_line_x[];
extern const uint8_t bongo_line_y[];
extern const uint8_t bongo_line_len[];
extern const uint8_t bongo_line_data[8][26] PROGMEM;

// Animation state
typedef struct {
    uint8_t anim_state;
    uint32_t idle_timeout_timer;
    uint32_t anim_timer;
    uint8_t current_idle_frame;
    uint8_t current_tap_frame;
    uint8_t last_bongo_frame;
} bongocat_state_t;

// Function declarations
void bongocat_init(void);
void bongocat_reset_for_display(void);
bool bongocat_is_new_tap(void);
void bongocat_eval_anim_state(void);
void bongocat_write_char_at_pixel_xy(uint8_t x, uint8_t y, uint8_t data, bool invert);
bool bongocat_is_key_down(void);
void bongocat_draw_table(void);
void bongocat_draw_frame(int framenumber);
void bongocat_draw(void);

#endif // OLED_ENABLE
