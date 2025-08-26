#include "motivational_messages.h"

#ifdef WPM_ENABLE

// Motivational messages for high WPM
static const char* motivational_messages[] = {
    "Sexy beast!", 
    "Beast mode!",
    "RAMPAGE!"        // Removed "Crushing it!" to save another ~12 bytes
};

static motivational_state_t motivational_state = {0};

void motivational_init(void) {
    motivational_state.show_motivational_msg = false;
    motivational_state.motivational_msg_timer = 0;
    motivational_state.current_message_index = 0;
    motivational_state.was_above_threshold = false;
}

void motivational_update(void) {
    uint8_t current_wpm = get_current_wpm();
    uint32_t current_time = timer_read32();
    
    // Check if WPM crosses the threshold
    if (current_wpm >= WPM_THRESHOLD && !motivational_state.was_above_threshold) {
        // Just crossed above threshold - show new message
        motivational_state.was_above_threshold = true;
        motivational_state.show_motivational_msg = true;
        motivational_state.motivational_msg_timer = current_time;
        
        // Select a random message (using timer as pseudo-random seed)
        motivational_state.current_message_index = (current_time / 1000) % (sizeof(motivational_messages) / sizeof(motivational_messages[0]));
    } else if (current_wpm < WPM_THRESHOLD && motivational_state.was_above_threshold) {
        // Dropped below threshold
        motivational_state.was_above_threshold = false;
    }
    
    // Hide message after display duration
    if (motivational_state.show_motivational_msg && timer_elapsed32(motivational_state.motivational_msg_timer) > MESSAGE_DISPLAY_DURATION) {
        motivational_state.show_motivational_msg = false;
    }
}

bool motivational_should_show_message(void) {
    return motivational_state.show_motivational_msg;
}

const char* motivational_get_current_message(void) {
    return motivational_messages[motivational_state.current_message_index];
}

#endif // WPM_ENABLE
