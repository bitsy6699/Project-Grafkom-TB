# C++ Project Setup Guide

## ✅ Setup Selesai

Project C++ dengan dukungan OpenGL (GLUT/freeglut) dan JSON telah dikonfigurasi sepenuhnya.

### Status Komponen

- ✅ **CMake Build System** - Konfigurasi lengkap
- ✅ **C++17 Standard** - Enabled
- ✅ **OpenGL + GLUT** - Library linked dan siap digunakan
- ✅ **nlohmann/json** - Header-only JSON library (v3.11.2)
- ✅ **VS Code Integration** - Debug dan build tasks siap
- ✅ **macOS Compatibility** - Optimized untuk Apple Silicon/Intel

---

## 🚀 Quick Start

### 1. Build Project
```bash
# Menggunakan VS Code Tasks (Ctrl+Shift+B)
# Atau via terminal:
cd build
cmake ..
make
```

### 2. Menjalankan Program
```bash
# Via VS Code Tasks (Ctrl+Shift+B → Run)
# Atau via terminal:
./build/projectcpp
```

### 3. Debug
```
Tekan F5 untuk memulai debugging dengan LLDB
```

---

## 📁 Project Structure

```
projectcss/
├── CMakeLists.txt              # Build configuration
├── src/
│   └── main.cpp               # Entry point dengan contoh OpenGL + JSON
├── include/                   # Header files (untuk ekspansi future)
├── third_party/
│   └── nlohmann/
│       └── json.hpp           # JSON library (header-only)
├── build/                     # Build directory (auto-generated)
├── .vscode/
│   ├── c_cpp_properties.json  # C++ IntelliSense configuration
│   ├── launch.json            # Debug configuration (LLDB)
│   ├── tasks.json             # Build tasks
│   └── settings.json          # Workspace settings
└── SETUP_GUIDE.md             # Dokumentasi ini
```

---

## 💻 Fitur yang Tersedia

### OpenGL (GLUT)
- Window management
- Display callbacks
- Keyboard input handling
- 2D/3D rendering

### JSON Support
- Object creation: `json obj = json::object()`
- Array operations: `json arr = json::array()`
- Parsing: `json::parse(string_data)`
- Serialization: `obj.dump(indent_level)`

---

## 📝 Contoh Kode

### Menggunakan JSON
```cpp
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Create object
json config;
config["name"] = "My App";
config["version"] = "1.0.0";

// Create array
json colors = json::array();
colors.push_back({255, 0, 0});     // Red
colors.push_back({0, 255, 0});     // Green
colors.push_back({0, 0, 255});     // Blue

// Convert to string
std::string json_str = config.dump(2);
std::cout << json_str << std::endl;
```

### Menggunakan OpenGL
```cpp
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw your graphics here
    glutSwapBuffers();
}

// Reshape callback
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);  // ESC to exit
}
```

---

## 🔧 Menambah File Source Baru

1. Buat file baru di `src/` (misal: `src/graphics.cpp`)
2. Edit `CMakeLists.txt`:
```cmake
set(SOURCES
    src/main.cpp
    src/graphics.cpp      # Tambahkan di sini
)
```
3. Rebuild: `Ctrl+Shift+B`

---

## 📦 Dependencies

Semua dependencies sudah disetup:

- **OpenGL Framework** - Bawaan macOS
- **GLUT Framework** - Bawaan macOS
- **nlohmann/json** - Header-only (sudah included)

Tidak perlu install dependencies tambahan!

---

## ⚙️ Konfigurasi VS Code

### Recommended Extensions
- **C/C++** (ms-vscode.cpptools) - IntelliSense dan debugging
- **CMake Tools** (ms-vscode.cmake-tools) - CMake integration
- **CodeLLDB** (vadimcn.vscode-lldb) - LLDB debugging

### Build pada Save (Optional)
Edit `.vscode/settings.json`:
```json
{
    "C_Cpp.default.compilerPath": "/usr/bin/clang++",
    "cmake.configureOnOpen": true
}
```

---

## 🐛 Troubleshooting

### Build Error: "GLUT not found"
macOS biasanya memiliki GLUT di framework. Jika error:
```bash
# Install via Homebrew
brew install freeglut
```

### Linking Error
Pastikan `CMakeLists.txt` memiliki:
```cmake
find_library(GLUT_LIBRARY GLUT)
target_link_libraries(projectcpp PRIVATE ${GLUT_LIBRARY})
```

### IntelliSense Issues
1. Reload VS Code: `Cmd+Shift+P` → "Reload Window"
2. Clear C++ cache: `Cmd+Shift+P` → "C/C++: Reset IntelliSense"

---

## 📚 Referensi

- **GLUT Documentation**: https://www.opengl.org/resources/libraries/glut/
- **nlohmann/json**: https://github.com/nlohmann/json
- **OpenGL**: https://www.opengl.org/

---

## ✨ Next Steps

1. Edit `src/main.cpp` untuk mulai development
2. Gunakan `Ctrl+Shift+B` untuk build
3. Tekan `F5` untuk debug
4. Explore OpenGL API dan JSON library

**Happy coding! 🎉**
