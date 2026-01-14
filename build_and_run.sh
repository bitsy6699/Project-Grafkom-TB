#!/bin/bash

# Script untuk compile dan run file C++ yang sedang aktif
# Usage: ./build_and_run.sh [file] [workspace]

FILE="${1}"
WORKSPACE="${2:-.}"

if [ -z "$FILE" ]; then
    echo "=========================================="
    echo "📂 Select a file to execute:"
    echo "=========================================="
    
    # Get list of cpp files in src/
    # Store in array for easy access
    i=1
    declare -a files
    
    # Loop through files in src/
    while IFS= read -r file; do
        if [ "$file" != "" ]; then
            echo "$i) $(basename "$file")"
            files[$i]="$file"
            i=$((i+1))
        fi
    done < <(find "${WORKSPACE}/src" -name "*.cpp" -maxdepth 1 | sort)
    
    echo "=========================================="
    read -p "Enter number (or 0 to cancel): " selection
    
    if [ "$selection" -eq 0 ] || [ -z "$selection" ]; then
        echo "Cancelled."
        exit 0
    fi
    
    # Validate selection
    if [ -n "${files[$selection]}" ]; then
        FILE="${files[$selection]}"
        echo "Selected: $FILE"
    else
        echo "❌ Invalid selection!"
        exit 1
    fi
fi

# Extract filename tanpa path
FILENAME=$(basename "$FILE")
FILEBASE="${FILENAME%.*}"
OUTPUT="/tmp/${FILEBASE}_exec"

# Kill any existing process dengan nama file ini
pkill -f "${FILEBASE}_exec" 2>/dev/null || true
sleep 0.1

echo "=========================================="
echo "🔨 Compiling: $FILENAME"
echo "=========================================="

# Compile dengan clang++
clang++ -std=c++17 \
    -DGL_SILENCE_DEPRECATION \
    -I"${WORKSPACE}/include" \
    -I"${WORKSPACE}/third_party" \
    -framework OpenGL \
    -framework GLUT \
    "$FILE" -o "$OUTPUT" 2>&1

COMPILE_STATUS=$?

if [ $COMPILE_STATUS -ne 0 ]; then
    echo ""
    echo "❌ Compilation failed!"
    exit 1
fi

echo ""
echo "✅ Compilation successful!"
echo ""
echo "=========================================="
echo "▶️  Running: $FILEBASE"
echo "=========================================="
echo ""

# Run the executable
"$OUTPUT"

RUN_STATUS=$?

# Cleanup
rm -f "$OUTPUT" 2>/dev/null || true

echo ""
echo "=========================================="
if [ $RUN_STATUS -eq 0 ] || [ $RUN_STATUS -eq 127 ]; then
    echo "✅ Execution completed"
else
    echo "⚠️  Process exited with code: $RUN_STATUS"
fi
echo "=========================================="

exit $RUN_STATUS
