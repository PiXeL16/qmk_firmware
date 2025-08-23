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

## Configuration Details

- **Keyboard**: lily58
- **Keymap Name**: PiXeL16
- **Target Board**: lily58/rev1
- **Generated**: Created via `qmk new-keymap` command

The keymap files are located in: `keyboards/lily58/keymaps/PiXeL16/`
