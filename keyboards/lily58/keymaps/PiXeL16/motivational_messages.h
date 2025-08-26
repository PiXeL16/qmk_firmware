#pragma once
#include "quantum.h"

#ifdef WPM_ENABLE
#include "wpm.h"

// Configuration
#define WPM_THRESHOLD 90
#define MESSAGE_DISPLAY_DURATION 3000  // 3 seconds in milliseconds

// Motivational messages are defined in motivational_messages.c

// State tracking
typedef struct {
    bool show_motivational_msg;
    uint32_t motivational_msg_timer;
    uint8_t current_message_index;
    bool was_above_threshold;
} motivational_state_t;

// Function declarations
void motivational_init(void);
void motivational_update(void);
bool motivational_should_show_message(void);
const char* motivational_get_current_message(void);

#endif // WPM_ENABLE
