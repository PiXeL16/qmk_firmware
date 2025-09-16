# 🎹 PiXeL16's Lily58 Firmware Build Guide

This guide explains how to build and flash your updated Lily58 firmware with all the new ZMK-inspired features.

## 🚀 Quick Start

### Option 1: Using the Build Script (Recommended)
From the QMK root directory, run:
```bash
# Build firmware
./build_lily58.sh build

# Flash to keyboard (requires bootloader mode)
./build_lily58.sh flash

# Other commands
./build_lily58.sh help      # Show all options
./build_lily58.sh size      # Build and show size info
./build_lily58.sh clean     # Clean build files
./build_lily58.sh check     # Verify QMK installation
```

### Option 2: Using the Keymap Makefile
From the keymap directory (`keyboards/lily58/keymaps/PiXeL16/`):
```bash
make build       # Build firmware
make flash       # Flash to keyboard
make help        # Show all available commands
make config      # Show current configuration
```

### Option 3: Using Standard QMK Commands
From the QMK root directory:
```bash
# Build
make lily58:PiXeL16

# Flash
make lily58:PiXeL16:flash

# Using QMK CLI
qmk compile -kb lily58 -km PiXeL16
qmk flash -kb lily58 -km PiXeL16
```

## 📦 What's New in This Firmware

Your firmware now matches your ZMK configuration with these features:

### ✨ New Functionality
- **Raycast Window Management**: Snap windows to halves, maximize, center
- **Advanced Clipboard Workflows**: Copy, paste, cut, paste-match
- **URL to Notes Workflow**: Automated link copying to notes app
- **Screenshot Selection**: Quick screenshot capture
- **Caps Word**: Smart caps lock for programming

### 🎯 Enhanced Combos
- **DF keys**: URL to Notes workflow
- **CV keys**: Copy (Cmd+C)
- **QW keys**: Screenshot selection
- **ZX keys**: Paste (Cmd+V)
- **GH keys**: Cut (Cmd+X)
- **JK keys**: Paste and match style
- **Left Shift + = key**: Caps Word toggle

### 🗂️ Updated Layers
- **NAV Layer**: Full Raycast integration with window management
- **FUNCTION Layer**: Caps Word on first key
- **Removed**: Spanish layer (as requested)

## 🔧 Build Configuration

Your firmware uses these settings (from `rules.mk`):

### Enabled Features
- `COMBO_ENABLE = yes` - For all the new combo functionality
- `OLED_ENABLE = yes` - For your custom OLED displays
- `WPM_ENABLE = yes` - Words per minute tracking
- `MOUSEKEY_ENABLE = yes` - Mouse control functionality
- `LTO_ENABLE = yes` - Link time optimization for smaller firmware

### Custom Source Files
- `motivational_messages.c` - WPM-based motivational messages
- `oled_images.c` - Custom image rotation system
- `bongocat_animation.c` - Animated bongo cat
- Additional lib files for layer/key logging

## 🔄 Flashing Process

1. **Build the firmware**:
   ```bash
   ./build_lily58.sh build
   ```

2. **Put keyboard in bootloader mode**:
   - Press the reset button on your Lily58
   - Or use your configured reset key combo
   - The keyboard should appear as a USB device

3. **Flash the firmware**:
   ```bash
   ./build_lily58.sh flash
   ```

4. **Verify the flash**:
   - Test the new combos (DF, CV, QW, etc.)
   - Try Raycast window management on NAV layer
   - Check that Spanish layer is removed

## 🐛 Troubleshooting

### Build Errors
```bash
# Clean and rebuild
./build_lily58.sh clean
./build_lily58.sh build

# Check QMK installation
./build_lily58.sh check
```

### Flash Errors
- Ensure keyboard is in bootloader mode
- Try a different USB cable/port
- Check that no other QMK tools are running

### Feature Testing
Test each major feature:

1. **Combos**: 
   - DF → Should trigger URL to Notes workflow
   - CV → Should copy (Cmd+C)
   - QW → Should take screenshot selection

2. **NAV Layer**:
   - Raycast shortcuts should work for window management
   - Navigation keys should work as expected

3. **FUNCTION Layer**:
   - First key should toggle Caps Word
   - Media keys should work

## 📁 File Structure

```
keyboards/lily58/keymaps/PiXeL16/
├── keymap.c           # Main keymap with all your customizations
├── rules.mk           # Build configuration
├── config.h           # Keyboard configuration
├── Makefile           # Convenient build commands
├── BUILD_GUIDE.md     # This guide
├── *.c/*.h            # Custom feature implementations
└── oled/              # OLED images and assets
```

## 🎯 Next Steps

1. **Build and flash** your updated firmware
2. **Test all combos** to ensure they work as expected
3. **Customize Raycast shortcuts** if needed (they're in `keymap.c`)
4. **Enjoy your enhanced keyboard** with ZMK-inspired functionality!

---

**Built with ❤️ for enhanced productivity and seamless workflow integration.**
