# PiXeL16 Keymap for Lily58

This is a custom keymap for the Lily58 keyboard.

## Setup Commands

The following QMK commands were used to set up this keymap:

```bash
# Set the default keyboard
qmk config user.keyboard=lily58

# Set the default keymap name
qmk config user.keymap=PiXeL16

# Generate the new keymap
qmk new-keymap
```

## Compilation

To compile this keymap:

```bash
qmk compile -kb lily58/rev1 -km PiXeL16
```

## Features

This keymap implements several advanced QMK features including:

- **Home Row Modifiers**: Shift, Cmd, Alt, Ctrl on ASDF/JKL; home row keys
- **Layer Tap Keys**: Multiple layers activated by holding specific keys
- **Smart Brackets**: Automatic cursor positioning when typing brackets
- **Navigation Shortcuts**: Application and workspace navigation macros
- **Emoji Layer**: One-shot emoji layer with intuitive letter-to-emoji mappings
- **Custom Layers**: SHIFT, SYMBOLS, FUNCTION, and EMOJI layers with specialized layouts

## Configuration Details

- **Keyboard**: lily58
- **Keymap Name**: PiXeL16
- **Target Board**: lily58/rev1
- **Generated**: Created via `qmk new-keymap` command

The keymap files are located in: `keyboards/lily58/keymaps/PiXeL16/`

## References

This keymap was inspired by advanced features from:
- [My Personalised Keyboard](https://leanrada.com/notes/my-personalised-keyboard/) - Advanced QMK customization techniques and layer design concepts
