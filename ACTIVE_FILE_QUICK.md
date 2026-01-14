# Active File Execution - Quick Start

## ✨ Fitur Baru: Execute File yang Sedang Dibuka

Sistem yang fleksibel untuk compile & run file C++ individual tanpa perlu rebuild full project.

---

## 🚀 Shortcut Utama

| Aksi | Shortcut |
|------|----------|
| **Compile & Run File Aktif** | **Cmd + R** |
| **Stop Execution** | **Cmd + K** |

---

## 📝 Workflow Baru

### Skenario 1: Multi-File Development
```
1. Buka main.cpp
2. Cmd + R → test main.cpp
3. Buka test_triangle.cpp (tab baru)
4. Cmd + R → test hanya test_triangle.cpp
5. Back ke main.cpp
6. Cmd + R → test main.cpp lagi (independent)
```

### Skenario 2: Quick Iteration
```
1. Edit file.cpp
2. Cmd + R → compile & run
3. Lihat output
4. Edit lagi
5. Cmd + R → langsung test perubahan
```

### Skenario 3: Stop Anytime
```
1. Cmd + R untuk run program
2. Program berjalan...
3. ESC → langsung stop
atau
4. Cmd + K → force kill
```

---

## 📊 Comparison: Full Build vs Active File

| Feature | Cmd + B (Full) | Cmd + R (Active) |
|---------|---|---|
| Build type | Full CMake + Make | Direct clang++ compile |
| Scope | Entire project | Current file only |
| Speed | Slower | ⚡ Much faster |
| Use case | Production build | Development/testing |
| Other files | All affected | Isolated |
| Time | Minutes | Seconds |

---

## 🔧 Sistem Kerja

### Build Script: `build_and_run.sh`
1. Compile file `.cpp` menggunakan `clang++`
2. Link dengan OpenGL + GLUT frameworks
3. Run executable hasil compile
4. Cleanup temp file otomatis
5. Display result di terminal

### Kill System
- ESC key → trigger "Kill Running Process" task
- Task jalankan: `pkill -f '_exec|projectcpp'`
- Safe cleanup tanpa file loss

---

## 📁 File yang Siap Ditest

```
src/
├── main.cpp              # Main project (Cmd+B untuk build full)
├── test_triangle.cpp     # Test file (Cmd+R untuk test)
└── ... (tambah file lain)
```

### Menambah File Baru
```
1. Buat file baru di src/something.cpp
2. Buka file tersebut
3. Cmd + R untuk compile & run
4. ESC untuk stop
5. Selesai!
```

---

## ✅ Fitur Tersedia Sekarang

- ✅ Cmd + R = Compile & run file aktif
- ✅ ESC/Cmd + K = Stop execution  
- ✅ Cmd + B = Full project build (masih works)
- ✅ Cmd + Shift + B = Clean build (masih works)
- ✅ Cmd + D = Debug (masih works)
- ✅ Fast compilation untuk single file
- ✅ Independent file execution

---

## 🎯 Penggunaan Sehari-hari

**Development Phase:**
```
Cmd + R → Test file
Edit code
Cmd + R → Test again
ESC → Stop
```

**Final Build:**
```
Cmd + B → Full project build
Cmd + D → Debug atau langsung run
```

---

## 💡 Tips & Tricks

1. **Test multiple files cepat**
   - Tab switch + Cmd + R untuk each file

2. **Emergency stop**
   - ESC atau Cmd + K selalu tersedia

3. **Keep terminal visible**
   - Cmd + ` untuk toggle terminal panel

4. **Check output**
   - Terminal panel menampilkan semua output

---

**Semuanya ready! Mulai dengan Cmd + R.** 🚀
