## C++ Project Setup - Quick Reference

### ✅ Installed & Configured
- CMake build system
- C++17 Standard
- OpenGL Framework (GLUT)
- nlohmann/json library v3.11.2
- LLDB debugger integration
- VS Code tasks & debug config

### 🎯 Keyboard Shortcuts
| Command | Shortcut |
|---------|----------|
| Build | `Ctrl+Shift+B` |
| Debug | `F5` |
| Stop | `Ctrl+Shift+F5` |

### 📝 Key Files
- `src/main.cpp` - Main program (OpenGL + JSON example)
- `CMakeLists.txt` - Build configuration
- `third_party/nlohmann/json.hpp` - JSON library
- `.vscode/launch.json` - Debugger config

### 🔨 Common Commands
```bash
# Build
cd build && cmake .. && make

# Run
./build/projectcpp

# Clean rebuild
rm -rf build && mkdir build && cd build && cmake .. && make
```

### 💡 Features Ready to Use
- **Graphics**: Draw 2D/3D shapes with OpenGL
- **Config**: Load/save settings with JSON
- **Window**: Handle window events with GLUT

---
See `SETUP_GUIDE.md` for complete documentation
