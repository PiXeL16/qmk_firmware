#!/bin/bash
# Build script for PiXeL16's Lily58 Custom Firmware
# This script can be run from anywhere and will build/flash the firmware

# Configuration
KEYBOARD="lily58"
KEYMAP="PiXeL16"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}🎹 [Lily58]${NC} $1"
}

print_success() {
    echo -e "${GREEN}✅ [Success]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠️  [Warning]${NC} $1"
}

print_error() {
    echo -e "${RED}❌ [Error]${NC} $1"
}

# Check if we're in the right directory
if [[ ! -f "Makefile" ]] || [[ ! -d "keyboards" ]]; then
    print_error "Not in QMK root directory. Changing to script directory..."
    cd "$SCRIPT_DIR" || {
        print_error "Failed to change to script directory!"
        exit 1
    }
fi

# Function to show help
show_help() {
    echo ""
    echo -e "${BLUE}🎹 PiXeL16's Lily58 Firmware Build Script${NC}"
    echo ""
    echo "Usage: ./build_lily58.sh [command]"
    echo ""
    echo "Commands:"
    echo "  build       - Build the firmware (.hex file)"
    echo "  flash       - Flash firmware to keyboard (requires bootloader mode)"
    echo "  clean       - Clean build files"
    echo "  size        - Build and show firmware size"
    echo "  check       - Check QMK installation"
    echo "  help        - Show this help message"
    echo ""
    echo "Examples:"
    echo "  ./build_lily58.sh build       # Build firmware"
    echo "  ./build_lily58.sh flash       # Flash to keyboard"
    echo "  ./build_lily58.sh             # Build firmware (default)"
    echo ""
}

# Function to build firmware
build_firmware() {
    print_status "Building ${KEYBOARD}:${KEYMAP} firmware..."
    
    if make "${KEYBOARD}:${KEYMAP}"; then
        print_success "Build completed successfully!"
        
        # Check if hex file was created (QMK includes revision in filename)
        HEX_FILE="${KEYBOARD}_rev1_${KEYMAP}.hex"
        ALT_HEX_FILE="${KEYBOARD}_${KEYMAP}.hex"
        
        if [[ -f "$HEX_FILE" ]]; then
            print_success "Firmware file created: $HEX_FILE"
            FOUND_HEX="$HEX_FILE"
        elif [[ -f "$ALT_HEX_FILE" ]]; then
            print_success "Firmware file created: $ALT_HEX_FILE"
            FOUND_HEX="$ALT_HEX_FILE"
        else
            # Try to find any hex file with our keymap name
            FOUND_HEX=$(ls -t *${KEYMAP}*.hex 2>/dev/null | head -n1)
            if [[ -n "$FOUND_HEX" ]]; then
                print_success "Firmware file found: $FOUND_HEX"
            else
                print_warning "Build succeeded but .hex file not found in root directory"
                return
            fi
        fi
        
        if [[ -n "$FOUND_HEX" ]]; then
            
            # Show file size
            FILE_SIZE=$(stat -f%z "$FOUND_HEX" 2>/dev/null || stat -c%s "$FOUND_HEX" 2>/dev/null)
            if [[ -n "$FILE_SIZE" ]]; then
                FILE_SIZE_KB=$((FILE_SIZE / 1024))
                print_status "Firmware size: ${FILE_SIZE_KB}KB (${FILE_SIZE} bytes)"
                
                # Warn if firmware is getting close to size limit
                if [[ $FILE_SIZE_KB -gt 75 ]]; then
                    print_warning "Firmware size is quite large (${FILE_SIZE_KB}KB). Consider optimizing if approaching limit."
                fi
            fi
        fi
    else
        print_error "Build failed!"
        exit 1
    fi
}

# Function to flash firmware
flash_firmware() {
    print_status "Flashing ${KEYBOARD}:${KEYMAP} firmware..."
    print_warning "Make sure your keyboard is in bootloader mode!"
    print_status "For Lily58: Press reset button or use the reset key combo"
    
    echo ""
    read -p "Press Enter when your keyboard is in bootloader mode, or Ctrl+C to cancel..."
    
    if make "${KEYBOARD}:${KEYMAP}:flash"; then
        print_success "Flash completed successfully!"
    else
        print_error "Flash failed!"
        exit 1
    fi
}

# Function to clean build files
clean_build() {
    print_status "Cleaning build files..."
    if make clean; then
        print_success "Clean completed!"
    else
        print_error "Clean failed!"
        exit 1
    fi
}

# Function to check QMK installation
check_qmk() {
    print_status "Checking QMK installation..."
    
    if command -v qmk &> /dev/null; then
        print_success "QMK CLI found"
        qmk hello
        print_success "QMK installation is working!"
    else
        print_warning "QMK CLI not found, but make should still work"
    fi
    
    # Check if we have the necessary files
    if [[ -f "keyboards/${KEYBOARD}/keymaps/${KEYMAP}/keymap.c" ]]; then
        print_success "Keymap file found"
    else
        print_error "Keymap file not found: keyboards/${KEYBOARD}/keymaps/${KEYMAP}/keymap.c"
        exit 1
    fi
    
    if [[ -f "keyboards/${KEYBOARD}/keymaps/${KEYMAP}/rules.mk" ]]; then
        print_success "Rules file found"
    else
        print_error "Rules file not found: keyboards/${KEYBOARD}/keymaps/${KEYMAP}/rules.mk"
        exit 1
    fi
}

# Function to show firmware size
show_size() {
    print_status "Building and analyzing firmware size..."
    
    # Build first
    if ! build_firmware; then
        exit 1
    fi
    
    # Try to get detailed size info using QMK if available
    if command -v qmk &> /dev/null; then
        print_status "Detailed size analysis:"
        qmk compile -kb "${KEYBOARD}" -km "${KEYMAP}" 2>&1 | grep -E "(bytes|%|Size|Memory)" || true
    fi
}

# Main script logic
case "${1:-build}" in
    "build")
        build_firmware
        ;;
    "flash")
        flash_firmware
        ;;
    "clean")
        clean_build
        ;;
    "size")
        show_size
        ;;
    "check")
        check_qmk
        ;;
    "help"|"-h"|"--help")
        show_help
        ;;
    *)
        print_error "Unknown command: $1"
        show_help
        exit 1
        ;;
esac
