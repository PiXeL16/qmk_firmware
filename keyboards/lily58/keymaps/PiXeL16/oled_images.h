#pragma once
#include "quantum.h"

#ifdef OLED_ENABLE

// Configuration
#define NUM_OLED_IMAGES 3
#define OLED_IMAGE_ROTATION_TIME 60000  // 60 seconds in milliseconds

// OLED image data
extern const char PROGMEM ichigo_logo[];
extern const char PROGMEM pixel16_logo[];
extern const char PROGMEM third_logo[];

// OLED image management
typedef struct {
    uint8_t current_image;
    uint32_t image_timer;
} oled_image_state_t;

// Function declarations
void oled_images_init(void);
void oled_images_update(void);
uint8_t oled_images_get_current(void);
void oled_images_draw_current(void);
bool oled_images_should_clear_for_bongocat(void);

#endif // OLED_ENABLE
