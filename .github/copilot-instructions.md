# Project C++ Setup Instructions

Project C++ dengan JSON support sudah disetup dengan lengkap.

## Status Setup

- ✅ Struktur project C++ dibuat
- ✅ CMake build system dikonfigurasi
- ✅ JSON library (nlohmann/json) siap digunakan
- ✅ VS Code tasks dan debug configuration siap
- ✅ C++17 standard enabled

## Cara Menggunakan

### 1. Build Project

Gunakan VS Code Tasks (Ctrl+Shift+B atau Cmd+Shift+B):
- **Build**: Kompile project
- **Clean Build**: Bersihkan dan rebuild
- **Run**: Build dan jalankan program

Atau via terminal:
```bash
cd /Users/rizkidzulfikaral-qatiri/projectcss
mkdir -p build
cd build
cmake ..
make
./projectcpp
```

### 2. Debug

Tekan F5 untuk start debugging dengan LLDB.

### 3. Struktur Project

- `src/main.cpp` - Main entry point
- `include/` - Header files
- `third_party/` - Third-party libraries (nlohmann/json included)
- `CMakeLists.txt` - Build configuration

## Menambah File Source Baru

1. Buat file di `src/`
2. Edit `CMakeLists.txt` dan tambahkan ke `set(SOURCES ...)`
3. Rebuild

## Contoh JSON Usage

```cpp
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Object
json obj = json::object();
obj["name"] = "value";

// Array
json arr = json::array();
arr.push_back(1);
arr.push_back("two");

// Parse string
json parsed = json::parse(R"({"key": "value"})");

// Dump to string
std::string str = obj.dump(2);
```

## Extensions Recommended

- C/C++ (ms-vscode.cpptools)
- CMake Tools (ms-vscode.cmake-tools)
- CodeLLDB (vadimcn.vscode-lldb)

## Tips

- Gunakan Cmd+Shift+B untuk quick build
- Gunakan F5 untuk debug
- Lihat output di "CMake" panel jika ada issues

---

Project siap untuk development! Mulai dengan mengedit `src/main.cpp` atau tambahkan source files baru.
