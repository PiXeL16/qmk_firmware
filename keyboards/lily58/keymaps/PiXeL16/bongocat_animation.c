#include "bongocat_animation.h"
#include "matrix.h"

#ifdef OLED_ENABLE

extern matrix_row_t matrix[MATRIX_ROWS];

// Bongo cat font data
const uint8_t bongofont[] PROGMEM = { 
    0xC1, 0xC1, 0xC2, 0x04, 0x08, 0x10, 
    0xC0, 0x38, 0x04, 0x03, 0x00, 0x00, 
    0xA0, 0x22, 0x24, 0x14, 0x12, 0x12, 
    0xA0, 0x21, 0x22, 0x12, 0x11, 0x11, 
    0x83, 0x7C, 0x41, 0x41, 0x40, 0x40, 
    0x82, 0x82, 0x84, 0x08, 0x10, 0x20, 
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
    0x80, 0x70, 0x19, 0x06, 0x00, 0x00, 
    0x80, 0x70, 0x0C, 0x03, 0x00, 0x00, 
    0x80, 0x00, 0x30, 0x30, 0x00, 0xC0, 
    0x80, 0x00, 0x30, 0x30, 0x00, 0x00, 
    0x49, 0x88, 0x08, 0x08, 0x08, 0x00, 
    0x44, 0x84, 0x04, 0x04, 0x00, 0x00, 
    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
    0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 
    0x3C, 0xC2, 0x01, 0x01, 0x02, 0x02, 
    0x35, 0x01, 0x8A, 0x7C, 0x00, 0x00, 
    0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 
    0x20, 0x21, 0x22, 0x12, 0x11, 0x11, 
    0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 
    0x1E, 0xE1, 0x00, 0x00, 0x01, 0x01, 
    0x1C, 0xE2, 0x01, 0x01, 0x02, 0x02, 
    0x18, 0x64, 0x82, 0x02, 0x02, 0x02, 
    0x18, 0x60, 0x80, 0x00, 0x00, 0x00, 
    0x18, 0x18, 0x1B, 0x03, 0x00, 0x40, 
    0x18, 0x06, 0x05, 0x98, 0x99, 0x84, 
    0x12, 0x0B, 0x08, 0x08, 0x08, 0x08, 
    0x11, 0x09, 0x08, 0x08, 0x08, 0x08, 
    0x10, 0x10, 0xD0, 0x11, 0x0F, 0x21, 
    0x10, 0x10, 0x10, 0x11, 0x0F, 0x01, 
    0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 
    0x10, 0x08, 0x04, 0x02, 0x02, 0x04, 
    0x0C, 0x30, 0x40, 0x80, 0x00, 0x00, 
    0x0C, 0x0C, 0x0D, 0x01, 0x00, 0x40, 
    0x08, 0xE8, 0x08, 0x07, 0x10, 0x24, 
    0x08, 0x30, 0x40, 0x80, 0x00, 0x00, 
    0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 
    0x08, 0x08, 0x04, 0x02, 0x02, 0x02, 
    0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 
    0x05, 0x05, 0x09, 0x09, 0x10, 0x10, 
    0x04, 0x38, 0x40, 0x80, 0x00, 0x00, 
    0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
    0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 
    0x02, 0x02, 0x81, 0x80, 0x80, 0x00, 
    0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 
    0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 
    0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 
    0x01, 0xE1, 0x1A, 0x06, 0x09, 0x31, 
    0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0x40, 0x40, 0x20, 0x20, 
    0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 
    0x00, 0x00, 0x60, 0x60, 0x00, 0x81, 
    0x00, 0x00, 0x01, 0x01, 0x00, 0x40, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t bongo_line_x[] = {51, 49, 48, 57};
const uint8_t bongo_line_y[] = {0, 8, 16, 24};
const uint8_t bongo_line_len[] = {5, 7, 8, 6};

const uint8_t bongo_line_data[8][26] PROGMEM = {
    { //idle1
    60, 52, 19, 30, 35,
    22, 47, 51, 60, 9, 0, 17,
    1, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle2
    60, 52, 19, 30, 35,
    22, 47, 51, 60, 9, 0, 17,
    1, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle3
    60, 53, 14, 31, 23,
    15, 43, 60, 60, 54, 5, 13,
    7, 56, 24, 2, 26, 39, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle4
    6, 52, 19, 38, 32,
    20, 47, 51, 60, 9, 0, 17,
    8, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //idle5
    60, 52, 19, 37, 40,
    21, 47, 51, 60, 9, 0, 17,
    8, 57, 33, 3, 27, 41, 29, 50,
    45, 36, 60, 60, 60, 60},
    { //prep
    6, 52, 19, 38, 32,
    20, 44, 51, 60, 10, 48, 16,
    8, 25, 4, 18, 27, 42, 46, 50,
    60, 60, 60, 60, 60, 60},
    { //tap1
    6, 52, 19, 38, 32,
    20, 44, 51, 60, 10, 49, 17,
    8, 25, 4, 18, 27, 41, 28, 11,
    60, 60, 60, 60, 58, 59},
    { //tap2
    6, 52, 19, 38, 32,
    20, 47, 51, 60, 10, 48, 16,
    8, 60, 55, 3, 27, 42, 46, 50,
    45, 34, 12, 60, 60, 60}
};

// Animation state
static bongocat_state_t bongocat_state = {0};

void bongocat_init(void) {
    bongocat_state.anim_state = idle;
    bongocat_state.idle_timeout_timer = 0;
    bongocat_state.anim_timer = 0;
    bongocat_state.current_idle_frame = 0;
    bongocat_state.current_tap_frame = 6;
    bongocat_state.last_bongo_frame = 12;
}

void bongocat_reset_for_display(void) {
    bongocat_state.last_bongo_frame = 12; // Force redraw
    bongocat_draw_table();
}

void bongocat_write_char_at_pixel_xy(uint8_t x, uint8_t y, uint8_t data, bool invert) {
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

bool bongocat_is_key_down(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > 0) {
            return true;
        }
    }
    return false;
}

void bongocat_eval_anim_state(void) {
    bool key_down;
    key_down = bongocat_is_key_down();

    switch (bongocat_state.anim_state) {
        case sleep:
            if(key_down) { bongocat_state.anim_state = tap; }
            break; 
        case idle:
            if(key_down) { bongocat_state.anim_state = tap; }
            else if (timer_elapsed32(bongocat_state.idle_timeout_timer) >= SLEEP_TIMEOUT) //prep to idle
                {
                    bongocat_state.anim_state = sleep;
                    bongocat_state.current_idle_frame = 0;
                }
            break;
        case prep:
            if(key_down) { bongocat_state.anim_state = tap; }
            else if (timer_elapsed32(bongocat_state.idle_timeout_timer) >= IDLE_TIMEOUT) //prep to idle
                {
                    bongocat_state.anim_state = idle;
                    bongocat_state.current_idle_frame = 0;
                }
            break;
        case tap:
            if (!key_down)
            {
                bongocat_state.anim_state = prep;
                bongocat_state.idle_timeout_timer = timer_read32();
            }
            break;
        default:
            break;
    }
}

void bongocat_draw_table(void) {
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

void bongocat_draw_frame(int framenumber) {
    //only redraw if the animation frame has changed
    if (framenumber != bongocat_state.last_bongo_frame) {
        bongocat_state.last_bongo_frame = framenumber;
        uint8_t i, j, current_bongochar = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < bongo_line_len[i]; j++) {
                bongocat_write_char_at_pixel_xy(bongo_line_x[i] + j*6, bongo_line_y[i], pgm_read_byte(&bongo_line_data[framenumber][current_bongochar]), false);
                current_bongochar++;
            }
        }
    }
}

bool bongocat_is_new_tap(void) {
    // Use WPM and last activity time to detect typing from both halves
    static uint8_t last_wpm = 0;
    
#ifdef WPM_ENABLE
    uint8_t current_wpm = get_current_wpm();
    uint32_t current_time = timer_read32();
    
    // Check if WPM changed or if we have recent activity
    bool wpm_changed = (current_wpm != last_wpm);
    bool recent_activity = (current_time - last_input_activity_time()) < 100; // 100ms threshold
#else
    bool wpm_changed = false;
    bool recent_activity = false;
#endif
    
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
#ifdef WPM_ENABLE
        last_wpm = current_wpm;
#endif
        return true;
    }
    
    return false;
}

void bongocat_draw(void) {
    static bool already_tapped = false;
    if (bongocat_is_new_tap()) {
        already_tapped = false;
    };
    bongocat_eval_anim_state();
    switch (bongocat_state.anim_state) {
        case sleep:
            bongocat_draw_frame(4);
            break;
        case idle:       
            bongocat_draw_frame(4 - bongocat_state.current_idle_frame);
            if (timer_elapsed32(bongocat_state.anim_timer) > ANIM_FRAME_DURATION) {
                bongocat_state.current_idle_frame = (bongocat_state.current_idle_frame + 1) % 5;
                bongocat_state.anim_timer = timer_read32();
            }
            break;
        case prep:
            bongocat_draw_frame(5);
            already_tapped = false;
            break;
        case tap:
            bongocat_draw_frame(bongocat_state.current_tap_frame);
            if (already_tapped == false) {
                if (bongocat_state.current_tap_frame == 6) {
                    bongocat_state.current_tap_frame = 7;
                }
                else {
                    bongocat_state.current_tap_frame = 6;
                }
            }
            already_tapped = true;
            break;
        default:
            bongocat_draw_frame(4);
            already_tapped = false;
            break;

    }
}

#endif // OLED_ENABLE
