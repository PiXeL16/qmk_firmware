# 🎹 PiXeL16 - An Advance QMK Keymap for Lily58

[![QMK](https://img.shields.io/badge/QMK-firmware-blue.svg)](https://qmk.fm/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

A **comprehensive, modular QMK keymap** for the Lily58 keyboard featuring motivational WPM messages, rotating OLED displays, advanced layer system, and clean modular architecture for easy customization.

## ✨ Key Features

### 🚀 Because it's not easy to re-learn how to type
- **Digital Participation Trophy**: Hit 90 WPM and your keyboard will shower you with praise because clearly human approval wasn't enough
- **Professionally Questionable Compliments**: Nothing says "serious developer" like your mechanical keyboard calling you a "Sexy beast!" during standup meetings
- **Brief Moment of Glory**: Enjoy 3 whole seconds of artificial confidence before reality kicks back in and you're just a person typing again

### 🖥️ Dynamic OLED Display System
- **Left OLED**: Layer status, real-time WPM tracking, keystroke history, motivational messages
- **Right OLED**: Rotating display system featuring:
  - Three customs artwork.
  - Animated bongocat that responds to typing activity
- **60-Second Rotation**: Automatically cycles through all display modes

### ⌨️ Advanced Layer System
- **9 Specialized Layers**: QWERTY, Shift, Symbols, Navigation, Raise, Function, Spanish, Mouse
- **Smart Space Layer**: Space key doubles as Shift layer access (tap/hold)
- **Combo Support**: Space+Enter triggers Cmd+Space (Spotlight)
- **Intelligent Navigation**: Word-level text manipulation, workspace control

### 🌐 Multilingual Support
- **Spanish Characters**: Complete accent support (á, é, í, ó, ú, ñ)
- **Spanish Punctuation**: ¡ ¿ symbols with proper input methods
- **One-Shot Layer**: Type accent and automatically return to base layer

### 🎯 Smart Programming Features
- **Intelligent Brackets**: Auto-cursor positioning for (), [], {}, <>
- **Programming Symbols**: All essential coding characters optimally placed
- **Word Navigation**: Professional text editing with select/delete word macros

## 🏗️ Modular Architecture

This keymap uses a **clean, maintainable modular structure** that separates concerns for easy customization:

```
keyboards/lily58/keymaps/PiXeL16/
├── keymap.c                    # Main keymap and layer definitions
├── config.h                    # QMK configuration settings
├── rules.mk                    # Feature flags and build configuration
├── readme.md                   # This documentation
│
├── motivational_messages.h     # WPM motivation system interface
├── motivational_messages.c     # WPM tracking and message logic
│
├── oled_images.h              # OLED display system interface  
├── oled_images.c              # Image rotation and display logic
│
├── bongocat_animation.h       # Bongocat animation interface
├── bongocat_animation.c       # Animation data and state management
│
└── oled/images/               # Source artwork files
    ├── ichigo.png
    ├── pixel16_logo.png
    └── mindset_is_all.png
```

### Supporting Libraries (keyboards/lily58/lib/)
```
lib/
├── layer_state_reader.c       # Layer status display
├── keylogger.c               # Keystroke history tracking  
├── rgb_state_reader.c        # RGB status (if enabled)
```

## 📋 Detailed Layer Layouts

The Lily58 has a split ergonomic design with 6×4+4 key matrix per side. Here are all the layer layouts:

### 0️⃣ **QWERTY** - Base Layer
```
 ,-----------------------------------------.                    ,-----------------------------------------.
 | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
                   |      |      |    |/SHIFT/           \      \ |      |      |      |
                   `----------------------------'           '------''--------------------'
```
**Key Features**: Standard QWERTY with smart Space/Shift layer-tap functionality

### 1️⃣ **SHIFT** - Shifted Characters Layer
```
 ,-----------------------------------------.                    ,-----------------------------------------.
 | ESC  |   ~  |   @  |   #  |   %  |      |                    |   ^  |   &  |   |  |   \  |      |BackSP|
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |   !  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   "  |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   :  |  '   |
 |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ;  |   :  |   *  |RShift|
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
                   |      |      |    |/      /         \      \ |      |      |      |
                   `----------------------------'           '------''--------------------'
```
**Key Features**: Shifted numbers, symbols, and characters for quick symbol access

### 2️⃣ **SYMBOLS** - Programming Layer
```
 ,-----------------------------------------.                    ,-----------------------------------------.
 |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |  `   |  \   |  $   |  {   |  }   |      |                    |      |      |      |      |      |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |  <   |  =   |  -   |  (   |  )   |  >   |-------.    ,-------|  ^   |  \   |  %   |  ↑   |      |      |
 |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 |      |      |      |  [   |  ]   |  +   |-------|    |-------|      |   _  |      |      |      |      |
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |▓▓▓▓▓ |MOUSE | FUNC |
                   |      |      |    |/      /         \      \ |▓▓▓▓▓ |      |      |
                   `----------------------------'           '------''--------------------'
```
**Key Features**: Smart brackets with auto-cursor positioning, essential coding symbols

### 3️⃣ **NAV** - Navigation Layer  
```
 ,-----------------------------------------.                    ,-----------------------------------------.
 |      | Back | Fwd  |TbPrv |TbNxt |      |                    |WS←   |WS→   |WS↑   |WS↓   |      |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |      |  Up  |      |      |      |                    |WLeft | WUp  |WRight|WSel  |WDel  |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |LShift| Left | Down |Right |  $   |  %   |-------.    ,-------| Left | Down |Right |      |   (  |   )  |
 |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 |LCtrl |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |  |   |
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   | LAlt |▓▓▓▓▓ |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
                   |      |▓▓▓▓▓ |    |/      /         \      \ |      |      |      |
                   `----------------------------'           '------''--------------------'
```
**Key Features**: Browser navigation, workspace control (macOS Spaces), word-level text manipulation

### 5️⃣ **FUNCTION** - System Controls
```
 ,-----------------------------------------.                    ,-----------------------------------------.
 |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |      |      |      |      |      |                    |      | Prev | Next | Play | Vol- | Vol+ |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |      | Span |      |      |      |-------.    ,-------|      |      |      |      | BrDn | BrUp |
 |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE |▓▓▓▓▓ |
                   |      |      |    |/      /         \      \ |      |      |▓▓▓▓▓ |
                   `----------------------------'           '------''--------------------'
```
**Key Features**: F1-F12 keys, media controls, brightness, Spanish character picker

### 6️⃣ **SPANISH** - Spanish Characters
```
 ,-----------------------------------------.                    ,-----------------------------------------.
 |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |  ¡   |      |      |   é  |      |      |                    |      |   ú  |   í  |   ó  |      |   ¿  |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |   á  |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 |      |      |      |      |      |      |-------|    |-------|   ñ  |      |      |      |      |      |
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |MOUSE | FUNC |
                   |      |      |    |/      /         \      \ |      |      |      |
                   `----------------------------'           '------''--------------------'
```
**Key Features**: All Spanish accented characters (á é í ó ú ñ) and punctuation (¡ ¿) with one-shot behavior

### 7️⃣ **MOUSE** - Mouse Control
```
 ,-----------------------------------------.                    ,-----------------------------------------.
 |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |      |WheelU|  Up  |WheelD|      |                    |      | Btn1 | Btn3 | Btn2 |      |      |
 |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 |      |      | Left | Down |Right |      |-------.    ,-------|      |WheelL|WheelD|WheelU|WheelR|      |
 |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 `-----------------------------------------/       /     \      \-----------------------------------------'
                   | LAlt | NAV  |LGUI| /Space/         \Enter \  |SYMBO |▓▓▓▓▓ | FUNC |
                   |      |      |    |/      /         \      \ |      |▓▓▓▓▓ |      |
                   `----------------------------'           '------''--------------------'
```
**Key Features**: Complete mouse control - movement, left/right/middle click, scroll wheel

## 🎛️ Layer Access Summary

| Layer Access | Key Combination | Use Case |
|-------------|------------------|----------|
| **SHIFT** | Hold Space | Symbols, shifted characters |
| **NAV** | Left thumb (2nd) | Navigation, text manipulation |
| **SYMBOLS** | Right thumb (1st) | Programming symbols, brackets |
| **MOUSE** | Right thumb (2nd) | Mouse control |
| **FUNCTION** | Right thumb (3rd) | System controls, media keys |
| **SPANISH** | FUNC + S | Spanish character picker |
| **Spotlight** | Space + Enter | Cmd+Space combo |

## 🚀 Installation & Compilation

### Prerequisites
```bash
# Install QMK if you haven't already
pip3 install qmk
qmk setup
```

### Step-by-Step Compilation
1. **Copy this keymap** to your QMK installation:
   ```
   keyboards/lily58/keymaps/PiXeL16/
   ```

2. **Compile the firmware** from the root of the qmk_firmware directory:
   ```bash
   # Option 1: Using make command
   make lily58:PiXeL16
   
   # Option 2: Using qmk compile command  
   qmk compile -kb lily58/rev1 -km PiXeL16
   ```

3. **Locate the firmware file**: 
   - New `.hex` file will be generated in the root of the qmk_firmware folder
   - File will be named: `lily58_rev1_PiXeL16.hex`

4. **Flash the firmware**:
   ```bash
   # Option 1: Direct flash (put keyboard in bootloader mode first)
   qmk flash -kb lily58/rev1 -km PiXeL16
   
   # Option 2: Using QMK Toolbox
   # Move the .hex file to your desired folder and flash via QMK Toolbox GUI
   ```

### Firmware Specifications
- **Target**: AVR atmega32u4 (Lily58 Rev1)
- **Size**: Optimized to fit within 28,672 byte limit
- **Features**: All functionality enabled while staying within memory constraints

## ⚙️ Configuration

### Feature Flags (rules.mk)
```makefile
OLED_ENABLE = yes              # Dynamic OLED displays
WPM_ENABLE = yes               # Words per minute tracking  
MOUSEKEY_ENABLE = yes          # Mouse control layer
EXTRAKEY_ENABLE = yes          # Media keys
COMBO_ENABLE = yes             # Key combinations
LTO_ENABLE = yes               # Link time optimization
```

### Key Customization Options

#### Motivational Messages
Edit `motivational_messages.c`:
```c
static const char* motivational_messages[] = {
    "Your message here!",
    "Another motivating phrase!",
    // Add your own messages
};
```

#### WPM Threshold  
Modify `motivational_messages.h`:
```c
#define WPM_THRESHOLD 90        // Change trigger speed
#define MESSAGE_DISPLAY_DURATION 3000  // Change display time
```

#### OLED Display Timing
Edit `oled_images.c`:
```c
if (timer_elapsed32(logo_timer) > 60000) {  // Change rotation interval
```

#### Custom Graphics
Replace the image arrays in `oled_images.c` with your own 128×32 pixel bitmap data.

## 🎮 Usage Guide

### Essential Shortcuts
| Combo | Action | Layer |
|-------|--------|-------|
| `Space` (tap) | Space character | Any |
| `Space` (hold) | Access SHIFT layer | Base |
| `Space + Enter` | Cmd+Space (Spotlight) | Any |
| `Fn + S` | Spanish character picker | Function |

### Navigation Features
- **Word Left/Right**: NAV layer + W←/W→
- **Word Select**: NAV layer + WSel (selects current word)
- **Word Delete**: NAV layer + WDel (deletes current word)
- **Workspace Control**: NAV layer + WS←/WS→/WS↑/WS↓

### Smart Brackets
On SYMBOLS layer, bracket keys automatically:
1. Insert opening bracket
2. Insert closing bracket  
3. Position cursor between them

## 🔧 Customization

### Adding New Motivational Messages
1. Edit `motivational_messages.c`
2. Add your message to the array
3. Recompile firmware

### Creating Custom OLED Graphics

This keymap includes three custom OLED images that rotate on the right display:

#### 📸 Current OLED Images
The keymap includes these artwork files in `oled/images/`:
- **`ichigo.png`** - Anime character artwork (128×32)
- **`pixel16_logo.png`** - Custom PiXeL16 branding logo (128×32)
- **`mindset_is_all.png`** - Motivational third logo (128×32)

#### 🎨 How to Replace OLED Images

1. **Create your image**:
   - Dimensions: **128×32 pixels** (required for Lily58 OLED)
   - Format: Monochrome/1-bit (black and white only)
   - Save as PNG or other common format

2. **Convert to C array using image2cpp**:
   - Go to [image2cpp online converter](http://javl.github.io/image2cpp/)
   - Upload your 128×32 image
   - Settings:
     - Canvas size: 128×32
     - Background color: Black
     - Invert image colors: ☑ (check this)
     - Brightness/alpha threshold: 128
     - Output format: Arduino code
     - Identifier: `your_image_name`

3. **Replace image data in `oled_images.c`**:
   ```c
   // Replace one of these arrays with your converted data:
   const char PROGMEM ichigo_logo[] = { /* your new data here */ };
   const char PROGMEM pixel16_logo[] = { /* your new data here */ };  
   const char PROGMEM third_logo[] = { /* your new data here */ };
   ```

4. **Rebuild firmware**:
   ```bash
   qmk compile -kb lily58/rev1 -km PiXeL16
   ```

#### 💡 Image Tips
- **Use high contrast**: Simple black/white designs work best
- **Avoid fine details**: 128×32 is quite small, bold shapes work better
- **Test your design**: Preview at actual size before converting
- **Consider the rotation**: Images change every 60 seconds, design accordingly

### Modifying Layer Behavior
- Layer definitions: `keymap.c`
- Layer icons: `lib/layer_state_reader.c`
- Custom key behaviors: `process_record_user()` in `keymap.c`



## 🙏 Acknowledgments

- QMK Community for the incredible firmware framework
- Lily58 keyboard design and community
- Open source contributors who make custom keyboards possible