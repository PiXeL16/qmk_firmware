LTO_ENABLE = yes            # Link Time Optimization enabled
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys enabled
EXTRAKEY_ENABLE = yes       # Audio control and System control (for media keys)
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = yes           # OLED display
WPM_ENABLE = yes            # Words Per Minute calculation
# UNICODEMAP_ENABLE = yes     # Unicode map for emojis (disabled to save memory for SM_TD)
# UNICODE_ENABLE = yes        # Unicode support for Spanish characters (temporarily disabled)
COMBO_ENABLE = yes          # Enable combo keys functionality
TAP_DANCE_ENABLE = no      # Enable tap dance functionality
# DEFERRED_EXEC_ENABLE = yes  # Commented out - not using SM_TD (was required for SM_TD library)

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/keylogger.c \
        motivational_messages.c \
        oled_images.c \
        bongocat_animation.c \
        # ./lib/logo_reader.c \  # Removed - using oled_images.c instead
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \