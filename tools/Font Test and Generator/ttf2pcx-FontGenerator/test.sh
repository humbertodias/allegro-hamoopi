#!/bin/bash

# Test script for ttf2pcx-qt
# Tests basic functionality in headless mode

set -e

echo "Testing ttf2pcx-qt build and basic functionality..."

# Set up environment
export QT_QPA_PLATFORM=offscreen
BUILD_DIR="$(dirname "$0")/build"
cd "$BUILD_DIR"

# Check if executable exists
if [ ! -f "./ttf2pcx-qt" ]; then
    echo "ERROR: ttf2pcx-qt executable not found"
    exit 1
fi

echo "✓ Executable found"

# Test that the application can start (runs in background briefly)
timeout 3 ./ttf2pcx-qt &
APP_PID=$!
sleep 2

if ps -p $APP_PID > /dev/null; then
    echo "✓ Application starts successfully"
    kill $APP_PID 2>/dev/null || true
    wait $APP_PID 2>/dev/null || true
else
    echo "✗ Application failed to start"
    exit 1
fi

echo ""
echo "All tests passed!"
echo ""
echo "Note: Full functional testing (UI interaction, file export) requires a display."
echo "To test on a system with display:"
echo "  1. Build the application (cmake .. && make)"
echo "  2. Run ./ttf2pcx-qt"
echo "  3. Select a font, size, and style"
echo "  4. Configure character range and output mode"
echo "  5. Click Export to generate a PCX file"
