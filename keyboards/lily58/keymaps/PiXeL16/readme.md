# 🎹 PiXeL16 Keymap for Lily58

A **comprehensive, feature-rich QMK keymap** for the Lily58 keyboard featuring 9 custom layers, rotating OLED displays, WPM tracking, and extensive personalization.

## ✨ Overview

This isn't just another keymap – it's a complete keyboard personality system that adapts to your workflow with intelligent layers, beautiful visuals, and productivity-focused features.

## 🎨 Visual Features

### 🖥️ OLED Display System
- **Ichigo Logo**: Beautiful anime character art display (128x32px)
- **Custom Bitmap Graphics**: Hand-crafted pixel art logo
- **Split Display Design**: 
  - **Left OLED**: Real-time layer icons, WPM tracking, keystroke history
  - **Right OLED**: Static Ichigo logo display

### 📊 Real-Time Information Display
- **WPM Tracking**: Live typing speed monitoring
- **Custom Layer Icons**: Visual ASCII art for each layer
- **Keystroke History**: Recent key combinations shown
- **Layer Status**: Always know which layer is active

## 🗂️ Layer System (8 Active Layers, 1 Commented Out)

### 0️⃣ **QWERTY** - Base Layer
Standard QWERTY with **regular home row keys** and optimized thumb cluster for efficient layer access

### 1️⃣ **SHIFT** - Shifted Characters  
Top row symbols and shifted number row for efficient symbol input

### 2️⃣ **SYMBOLS** - Programming Layer
- **Smart Brackets**: Auto-positioning for `()`, `[]`, `{}`, `<>`
- **Programming Symbols**: All essential coding characters
- **Cursor Management**: Intelligent bracket cursor placement

### 3️⃣ **NAV** - Navigation Layer
- **Symmetric Arrow Navigation**: Arrows accessible from both hands
- **Application Navigation**: Back/Forward, Tab switching
- **Workspace Control**: macOS Mission Control integration
- **Word Navigation**: Advanced text manipulation:
  - **Word Left/Right**: Option+Arrow navigation
  - **Word Select**: Intelligent word selection macro
  - **Word Delete**: Select + delete word functionality

### 4️⃣ **RAISE** - Numbers & F-Keys
Number row, function keys, and additional navigation

### 5️⃣ **FUNCTION** - System Control
- **Function Keys**: F1-F12 in logical arrangement
- **Media Controls**: Previous, play/pause, next, volume
- **Brightness**: Display brightness controls
- **System Integration**: 
  - **Emoji Picker**: Single tap for one-shot layer, double tap for system picker
  - **Spanish Picker**: Quick access to Spanish characters

### 6️⃣ **EMOJI** - One-Shot Emoji Layer
- **Letter-to-Emoji Mapping**: Intuitive emoji selection
- **Arrow Symbols**: Unicode arrows matching navigation layer
- **Smart Typography**: Curly quotes, apostrophes
- **Instant Access**: One-shot layer with automatic return

### 7️⃣ **SPANISH** - Accented Characters
- **Complete Spanish Support**: á, é, í, ó, ú, ñ
- **Spanish Punctuation**: ¡, ¿ symbols
- **One-Shot Behavior**: Type accent, automatically return to base layer

### 8️⃣ **MOUSE** - Mouse Control Layer
- **Mouse Movement**: WASD-style mouse control
- **Click Controls**: Left, right, middle click
- **Scroll Wheel**: Vertical scrolling
- **Precision Control**: Fine mouse movement from keyboard

## 🔧 Advanced QMK Features

### ⌨️ Smart Input Features  
- **Regular Home Row Keys**: All keys (A, S, D, F, J, K, L, ;) work as normal letters - no modifier delays
- **Smart Space Layer**: Space key doubles as Shift layer access (tap for space, hold for SHIFT layer)
- **Simple Layer-Tap**: Space bar uses standard QMK layer-tap functionality - fast and reliable
- **Combo Detection**: Space+Enter combo triggers Cmd+Space

### 🌐 Unicode & International Support
- **macOS Unicode Mode**: Full emoji and special character support
- **Spanish Character Input**: Native accented character support
- **Smart Typography**: Proper curly quotes and apostrophes
- **Emoji Picker Integration**: Both custom layer and system picker access

### 🎯 Productivity Enhancements
- **Word Navigation Macros**: Professional-grade text editing
- **Application Shortcuts**: Browser navigation, tab management
- **Workspace Management**: macOS Spaces integration
- **Smart Bracket System**: Automatic cursor positioning for all bracket types

## 📁 File Structure

```
keyboards/lily58/keymaps/PiXeL16/
├── keymap.c              # Main keymap definition (985+ lines)
├── rules.mk              # Feature configuration
├── config.h              # QMK configuration
├── readme.md             # This documentation
└── oled/
    └── images/           # Source logo images
        ├── pixel16_logo.png
        ├── ichigo.png
        └── mindset_is_all.png

keyboards/lily58/lib/
├── layer_icon_reader.c       # Custom layer icons
├── rotating_display_reader.c # Logo rotation system
├── custom_logo_reader.c      # Original logo support
├── layer_state_reader.c      # Layer status display
├── keylogger.c              # Keystroke history
└── wpm_reader.c             # WPM calculation
```

## 🚀 Compilation & Setup

### Prerequisites
```bash
# Set up QMK environment
qmk config user.keyboard=lily58
qmk config user.keymap=PiXeL16
```

### Compilation
```bash
# Compile the firmware
qmk compile -kb lily58/rev1 -km PiXeL16

# Flash to keyboard
qmk flash -kb lily58/rev1 -km PiXeL16
```

### Firmware Stats
- **Size**: 27,984 / 28,672 bytes (97% used, 688 bytes free)
- **Features**: Regular home row keys, space layer-tap, Ichigo OLED logo, combos, Spanish support
- **Performance**: Fast typing with zero modifier delays, standard QMK layer-tap for space
- **VIA Support**: Disabled to accommodate feature set
- **Memory Optimization**: Emoji functionality temporarily disabled to free up space

## ⚙️ Configuration Details

### Enabled Features
- ✅ **Standard Home Row Keys**: Regular letter keys without modifier delays for fast, natural typing
- ✅ **OLED Display**: Custom graphics and real-time info
- ✅ **WPM Tracking**: Live typing speed monitoring  
- ✅ **Unicode Support**: Full emoji and international character support
- ✅ **Mouse Keys**: Complete mouse control from keyboard
- ✅ **Extra Keys**: Media and system control
- ✅ **Custom Layers**: 8 active specialized layers (emoji layer temporarily disabled)
- ✅ **Combo Keys**: Space+Enter combo support

### Disabled Features
- ❌ **Emoji Layer**: Temporarily disabled to accommodate SM_TD library (can be re-enabled)
- ❌ **VIA Support**: Disabled to save memory for custom features
- ❌ **RGB Lighting**: Focus on OLED displays
- ❌ **Audio**: Prioritizing other features

## 🎨 Customization Options

### OLED Display Customization
```c
// In keyboards/lily58/lib/logo_reader.c
// Replace the ichigo bitmap array with your own 128x32px bitmap data
static char logo[] = { /* your bitmap data here */ };
```

### Layer-Tap Configuration
```c
// In config.h - optimized for smooth typing experience
#define TAPPING_TERM 200              // 200ms for layer-tap detection
#define TAPPING_TERM_PER_KEY          // Customizable per key
```

### Combo Configuration
```c
// In config.h - combo timing
#define COMBO_TERM 50                 // 50ms window to press both keys
```

### Layer-Tap Configuration
```c
// In keymap.c - Space bar layer-tap setup:
LT(_SHIFT, KC_SPC)  // Space = tap for space, hold for SHIFT layer

// Standard QMK tapping term (in config.h):
#define TAPPING_TERM 200   // 200ms hold time for layer access
```

### ~~Home Row Modifiers~~ - Removed for Better Typing Experience
Home row modifiers have been removed to eliminate typing delays. All keys (A, S, D, F, J, K, L, ;) now work as regular letters with instant response.

### Custom Logo Setup
To change the OLED logo, convert your 128x32px image to a bitmap array and replace the data in `keyboards/lily58/lib/logo_reader.c`.

### Layer Icon Customization
Edit `keyboards/lily58/lib/layer_icon_reader.c` to customize the ASCII art layer indicators.

## 🎯 Usage Tips

### Essential Combos
- **Spotlight Search**: Space + Enter → Cmd+Space (quick access to Spotlight)
- **Emoji Access**: Function layer → E (single tap for layer, double tap for system picker)
- **Spanish Characters**: Function layer → S → letter
- **Word Navigation**: NAV layer → W←/W→/WSel/W⌫
- **Smart Brackets**: SYMBOLS layer → any bracket pair

### Layer Access
- **Primary**: Thumb keys for most-used layers (NAV, SYMBOLS, MOUSE, FUNCTION)
- **Secondary**: Function layer triggers for specialty layers (EMOJI, SPANISH)
- **Modifiers**: Standard left/right shift keys and layer access for all modifiers

### OLED Information
- **Left Display**: Always shows current layer and typing stats  
- **Right Display**: Shows the beautiful Ichigo logo
- **Status Updates**: Real-time feedback on all layer changes

## 🧠 Philosophy

This keymap embodies the concept that your keyboard should be an extension of your personality and workflow. Every feature serves a purpose:

- **Visual Identity**: Custom logos reflect personal and professional identity
- **Productivity**: Advanced text navigation and smart input features
- **Multilingual**: Support for both English and Spanish workflows  
- **Efficiency**: Everything accessible within one key press from base layer
- **Feedback**: Constant visual feedback on keyboard state and performance

## 🌟 Inspiration & References

This keymap was heavily inspired by advanced QMK techniques from:
- [SM_TD Library](https://github.com/stasmarkin/sm_td) - Revolutionary home row modifier implementation
- [My Personalised Keyboard](https://leanrada.com/notes/my-personalised-keyboard/) - Advanced layer design and customization concepts
- **Personal Workflow Needs**: Spanish input, programming efficiency, visual personalization
- **Community QMK Examples**: Best practices from the QMK community

## 🚀 Future Enhancements

Potential additions (memory permitting):
- Additional logo rotation options
- Weather/time display integration  
- Typing statistics tracking
- Custom macro recording
- Advanced animation systems

---

**Built with ❤️ and extensive QMK customization**  
*"Mindset is All" - Every keypress reflects your personal approach to productivity*
