# Project C++ Documentation Index

## 📚 Dokumentasi Lengkap

### 🚀 Quick Start (Mulai dari sini!)
- **[ACTIVE_FILE_QUICK.md](ACTIVE_FILE_QUICK.md)** - Quick reference untuk active file execution
- **[MACOS_SETUP.md](MACOS_SETUP.md)** - macOS setup summary

### 📖 Detailed Guides
- **[ACTIVE_FILE_EXECUTION.md](ACTIVE_FILE_EXECUTION.md)** - Panduan lengkap active file execution
- **[MACOS_SHORTCUTS.md](MACOS_SHORTCUTS.md)** - Semua keyboard shortcuts untuk macOS
- **[SETUP_GUIDE.md](SETUP_GUIDE.md)** - Setup & konfigurasi project lengkap

### 🛠️ README
- **[README.md](README.md)** - Project overview

---

## 🎯 Shortcut CheatSheet

### File Execution (BARU!)
```
Cmd + R     → Compile & Run file yang sedang dibuka
ESC         → Stop/Kill execution
Cmd + K     → Alternative kill (gunakan jika ESC tidak works)
```

### Project Build
```
Cmd + B     → Build full project
Cmd + Shift + B → Clean & rebuild full project
```

### Debug
```
Cmd + D     → Start debugging
Cmd + Shift + D → Stop debugging
Cmd + →     → Step over (saat debug)
Cmd + ↓     → Step into (saat debug)
Cmd + ↑     → Step out (saat debug)
```

### Utility
```
Cmd + L     → Toggle breakpoint
Cmd + Shift + R → Check syntax only
Cmd + P     → Open file
Cmd + Shift + P → Command palette
```

---

## 🔄 Workflow Quick Tips

### Development Cycle (RECOMMENDED)
```
1. Buka file di src/ (main.cpp, test_*.cpp, dll)
2. Cmd + R → Compile & run file tersebut
3. Lihat output di terminal
4. Edit code
5. Cmd + R → Test perubahan (instant!)
6. ESC → Stop program
7. Repeat step 3-6
```

### Final Project Build
```
1. Selesai development di file individual
2. Cmd + B → Full project build
3. Cmd + D → Debug full project
atau
4. Cmd + B → build
5. Terminal: ./build/projectcpp → run
```

### Test Multiple Files
```
Tab 1: src/main.cpp → Cmd + R
Tab 2: src/test_A.cpp → Cmd + R  
Tab 3: src/test_B.cpp → Cmd + R
(Setiap file independent, tidak saling influence)
```

---

## 📁 Project Structure

```
projectcss/
├── README.md                          # Project info
├── QUICK_START.md                     # Basic shortcuts
├── MACOS_SETUP.md                     # macOS setup
├── MACOS_SHORTCUTS.md                 # Detailed shortcuts
├── ACTIVE_FILE_EXECUTION.md           # Active file feature guide
├── ACTIVE_FILE_QUICK.md               # Active file quick ref
├── SETUP_GUIDE.md                     # Full setup guide
│
├── build_and_run.sh                   # Script untuk compile & run file
├── CMakeLists.txt                     # CMake configuration
│
├── src/
│   ├── main.cpp                       # Main project file
│   └── test_triangle.cpp              # Example test file
│
├── include/                           # Header files (untuk future)
├── third_party/
│   └── nlohmann/
│       └── json.hpp                   # JSON library
│
├── build/                             # Build output (auto-generated)
│   └── projectcpp                     # Compiled executable
│
└── .vscode/
    ├── launch.json                    # LLDB debug config
    ├── tasks.json                     # Build tasks
    ├── keybindings.json               # Keyboard shortcuts
    ├── c_cpp_properties.json          # IntelliSense config
    └── settings.json                  # Workspace settings
```

---

## ✨ Key Features

| Feature | Shortcut | Status |
|---------|----------|--------|
| Compile & Run Active File | Cmd + R | ✅ NEW! |
| Stop Execution | ESC / Cmd + K | ✅ NEW! |
| Full Project Build | Cmd + B | ✅ |
| Clean Build | Cmd + Shift + B | ✅ |
| Debug | Cmd + D | ✅ |
| IntelliSense | Auto | ✅ |
| LLDB Integration | Built-in | ✅ |
| JSON Support | nlohmann/json | ✅ |
| OpenGL/GLUT | Framework | ✅ |

---

## 🎓 Recommended Reading Order

1. **First time?** → Start with [ACTIVE_FILE_QUICK.md](ACTIVE_FILE_QUICK.md)
2. **Want detailed guide?** → Read [ACTIVE_FILE_EXECUTION.md](ACTIVE_FILE_EXECUTION.md)
3. **Need keyboard shortcuts?** → Check [MACOS_SHORTCUTS.md](MACOS_SHORTCUTS.md)
4. **Full setup details?** → See [SETUP_GUIDE.md](SETUP_GUIDE.md)

---

## 🚀 Get Started Now

### Option 1: Test Active File Feature
```bash
1. Open src/test_triangle.cpp in VS Code
2. Press Cmd + R
3. Window muncul dengan triangle
4. Press ESC untuk stop
```

### Option 2: Build Full Project
```bash
1. Press Cmd + B
2. Wait untuk build selesai
3. ./build/projectcpp atau Cmd + D untuk debug
```

### Option 3: Development Workflow
```bash
1. Edit src/main.cpp
2. Cmd + R untuk quick test
3. Cmd + B untuk full project build
```

---

## 💡 Pro Tips

- **Fastest workflow**: Cmd + R untuk development, Cmd + B untuk final
- **Test quickly**: Use Cmd + R on any .cpp file individually
- **Emergency stop**: ESC atau Cmd + K always available
- **Multi-file dev**: Each file runs independently, no conflicts
- **Tab switching**: Fast tab switch + Cmd + R = quick multi-file test

---

## 🎉 Ready to Code!

Semua setup sudah complete:
- ✅ C++17 compiler ready
- ✅ OpenGL/GLUT frameworks configured
- ✅ JSON library included
- ✅ LLDB debugger integrated
- ✅ macOS keybindings optimized
- ✅ Active file execution ready
- ✅ Full project build ready

**Start coding now! Tekan Cmd + R on any file.** 🚀
