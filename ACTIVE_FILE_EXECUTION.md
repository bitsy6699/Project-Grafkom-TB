# Active File Execution System

## 🎯 Fitur Utama

Sistem yang fleksibel untuk mengeksekusi file C++ yang sedang aktif (dibuka) di VS Code. Sempurna untuk:
- Testing kode satu file saja
- Develop multiple C++ files secara terpisah
- Quick compile & run tanpa full project build

---

## ⌨️ Shortcuts Baru

### Compile & Run Active File
```
Cmd + R
```
- Compile file yang sedang dibuka/aktif saat ini
- Run executable langsung setelah compile berhasil
- Output ditampilkan di terminal panel
- File lain tidak terpengaruh
- Auto kill previous process untuk prevent conflicts

### Kill/Stop Execution
```
Cmd + K
```
- Stop process yang sedang berjalan
- Bisa digunakan kapan saja
- Safe - tidak merusak file

---

## 🔄 Workflow

### Scenario 1: Develop Multi-File Project
```
1. Buka file1.cpp
2. Cmd + R untuk test file1.cpp
3. Buka file2.cpp (di tab lain)
4. Cmd + R untuk test file2.cpp
   (file1.cpp tidak terpengaruh)
5. ESC atau Cmd + K untuk stop
```

### Scenario 2: Quick Code Testing
```
1. Buat file test_something.cpp
2. Cmd + R untuk langsung test
3. Lihat output
4. Ubah code
5. Cmd + R lagi untuk test perubahan
```

### Scenario 3: Main Project Build
```
1. Cmd + B untuk build full project (seperti sebelumnya)
2. Cmd + D untuk debug
3. Atau Cmd + R untuk test file aktif saja
```

---

## 📋 Perintah yang Tersedia

| Perintah | Shortcut | Fungsi |
|----------|----------|--------|
| Compile & Run Active File | Cmd + R | Compile & run file yang dibuka |
| Kill Running Process | ESC atau Cmd + K | Stop eksekusi |
| Build Full Project | Cmd + B | Full project build dengan CMake |
| Clean Build | Cmd + Shift + B | Clean & rebuild full project |
| Check Syntax Only | Cmd + Shift + R | Hanya check syntax tanpa run |
| Debug Project | Cmd + D | Debug full project |

---

## 🔧 Cara Kerja Internal

### Build Script (`build_and_run.sh`)
```bash
# Mode Interaktif (Menu Selection)
./build_and_run.sh

# Mode Langsung
./build_and_run.sh [file] [workspace]
```

1. **Compile** - Menggunakan `clang++` langsung
   - Input: File `.cpp` yang aktif
   - Output: Executable di `/tmp/filename_exec`
   - Flags: `-std=c++17`, OpenGL, GLUT framework

2. **Run** - Eksekusi hasil compile
   - Jalankan executable
   - Capture output & exit code
   - Cleanup temp file setelah selesai

3. **Kill** - Stop process
   - `pkill` untuk terminate process
   - Safe cleanup

---

## 📁 File-File Terkait

```
projectcss/
├── build_and_run.sh          # Script untuk compile & run
├── src/
│   ├── main.cpp              # Main project file
│   ├── test_triangle.cpp     # Test file (contoh)
│   └── ... (file lain)
├── .vscode/
│   ├── keybindings.json      # Shortcuts (Cmd+R, ESC, Cmd+K)
│   └── tasks.json            # Tasks (Compile & Run, Kill)
└── ...
```

---

## 🎓 Contoh Penggunaan

### Test File Individual
```
1. Buka src/test_triangle.cpp
2. Tekan Cmd + R
3. Window OpenGL muncul dengan triangle
4. Edit code → Cmd + R lagi untuk test changes
5. ESC untuk close window
```

### Develop Multiple Files
```
Tab 1: src/graphics.cpp
Tab 2: src/physics.cpp

Buka Tab 1 → Cmd + R (test graphics)
Buka Tab 2 → Cmd + R (test physics)
```

### Full Project vs Active File
```
Cmd + B     = Full CMake build (untuk release/final)
Cmd + R     = Just active file (untuk development)
```

---

## ⚙️ Customization

### Ubah Shortcut
Edit `.vscode/keybindings.json`:
```json
{
    "key": "cmd+e",  // Ganti key
    "command": "workbench.action.tasks.runTask",
    "args": "Compile & Run Active File"
}
```

### Add Framework Baru
Edit `build_and_run.sh` di section `clang++`:
```bash
clang++ -std=c++17 \
    ... existing flags ...
    -lmylib \  # Tambah library baru
    "$FILE" -o "$OUTPUT"
```

### Change Output Directory
Edit script, ubah `OUTPUT` variable:
```bash
OUTPUT="${WORKSPACE}/bin/${FILEBASE}_exec"
```

---

## 🐛 Troubleshooting

### "Command not found: build_and_run.sh"
```bash
chmod +x build_and_run.sh
```

### "GLUT/OpenGL not found"
Pastikan framework sudah installed di macOS:
```bash
# Check if GLUT available
ls /System/Library/Frameworks/ | grep -i glut
```

### Process still running setelah ESC
```
Cmd + K untuk force kill
Atau: kill -9 $(pgrep _exec)
```

### Multiple windows opened
Setiap compile & run membuat executable baru di `/tmp/`
Cleanup otomatis setelah selesai

---

## ✨ Best Practices

1. **Gunakan Cmd+R untuk testing**
   - Cepat iteration saat development
   - File lain tidak terpengaruh

2. **Gunakan Cmd+B untuk final build**
   - Full project build dengan CMake
   - Before production/submission

3. **Organize test files**
   ```
   src/
   ├── main.cpp          (main program)
   ├── test_feature1.cpp (test feature 1)
   ├── test_feature2.cpp (test feature 2)
   ```

4. **ESC/Cmd+K untuk emergency stop**
   - Jika program hang
   - Jika window stuck
   - Always available

---

## 🎉 Ready to Use!

Semuanya sudah siap:
- ✅ Build script ready (`build_and_run.sh`)
- ✅ Shortcuts configured
- ✅ Test file included (`test_triangle.cpp`)
- ✅ Full project build still works

**Mulai dengan: Cmd + R di file apa saja! 🚀**
