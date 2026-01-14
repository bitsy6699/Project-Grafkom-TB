# macOS Keyboard Shortcuts Guide

## Build & Debug Shortcuts (macOS Optimized)

### Main Commands
| Action | Shortcut | Deskripsi |
|--------|----------|-----------|
| **Build Project** | `Cmd + B` | Compile seluruh project |
| **Clean Build** | `Cmd + Shift + B` | Hapus build files dan rebuild |
| **Debug/Run** | `Cmd + D` | Jalankan dengan debugger (LLDB) |
| **Stop Debug** | `Cmd + Shift + D` | Stop debugging session |

### Debug Controls (saat debugging aktif)
| Action | Shortcut | Deskripsi |
|--------|----------|-----------|
| **Step Over** | `Cmd + →` | Lanjut ke baris berikutnya |
| **Step Into** | `Cmd + ↓` | Masuk ke function call |
| **Step Out** | `Cmd + ↑` | Keluar dari function |
| **Continue/Pause** | `Cmd + /` | Lanjutkan atau pause execution |
| **Toggle Breakpoint** | `Cmd + L` | Tambah/hapus breakpoint di baris ini |

### Utility Shortcuts
| Action | Shortcut |
|--------|----------|
| **Check Syntax** | `Cmd + Shift + R` → Pilih "Check Syntax Only" |
| **Comment Line** | `Cmd + /` (VS Code standard) |
| **Go to Line** | `Ctrl + G` |
| **Open File** | `Cmd + P` |
| **Quick Open Commands** | `Cmd + Shift + P` |

---

## 📋 Fitur Khusus

### 1. Build Full Project
```
Cmd + B
```
- Menjalankan CMake dan Make
- Compile seluruh project
- Output ditampilkan di Terminal panel

### 2. Debug dengan LLDB
```
Cmd + D
```
- Automatic build sebelum debug
- LLDB debugger active
- Lihat variables di Debug panel
- Hover di code untuk lihat value

### 3. Check Syntax Saja (Tanpa Build Full)
```
Cmd + Shift + R
```
- Pilih "Check Syntax Only"
- Hanya check file yang aktif saat ini
- Tidak compile seluruh project
- Cepat untuk validasi syntax

### 4. Clean & Rebuild
```
Cmd + Shift + B
```
- Hapus semua build files
- Rebuild dari nol
- Gunakan jika ada issue linking

---

## 🔍 Debug Panel Features

Saat debugging (F5 / Cmd + D):
- **Variables** - Lihat nilai semua variabel lokal
- **Watch** - Tambah expression untuk monitor
- **Call Stack** - Lihat function call hierarchy
- **Breakpoints** - Kelola semua breakpoints
- **Debug Console** - Print output & evaluate expressions

---

## 💡 Pro Tips

1. **Hover untuk lihat value**
   - Saat debugging, hover di variable untuk lihat value terkini

2. **Conditional Breakpoint**
   - Right-click breakpoint → Edit Breakpoint
   - Masukkan kondisi (misal: `rotation > 180`)

3. **Syntax Highlighting**
   - macOS keybindings tidak mengganggu IntelliSense
   - Ctrl+Space untuk autocomplete

4. **Quick Build & Run**
   - Cmd + B → Build
   - Cmd + D → Debug
   - Atau Cmd + Shift + R → Check Syntax

---

## ⚙️ Customization

Edit `.vscode/keybindings.json` untuk custom shortcuts:
```json
{
    "key": "cmd+shift+t",
    "command": "workbench.action.tasks.runTask",
    "args": "Build"
}
```

---

## 🎯 Workflow Rekomendasi

### Saat Development
1. Edit code di `src/main.cpp`
2. `Cmd + B` untuk build
3. Fix errors dari output
4. `Cmd + D` untuk debug final

### Saat Debug
1. Set breakpoint dengan `Cmd + L`
2. `Cmd + D` untuk start debug
3. `Cmd + →` untuk step through code
4. Hover untuk check variable values
5. `Cmd + Shift + D` untuk stop

---

**Happy coding on macOS! 🎉**
