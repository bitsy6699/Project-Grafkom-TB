# Project C++

Sebuah project C++ modern dengan dukungan JSON menggunakan nlohmann/json library.

## Fitur

- Modern C++ (C++17)
- JSON support via nlohmann/json
- CMake build system
- Siap untuk development

## Struktur Project

```
projectcss/
├── src/               # Source files
│   └── main.cpp      # Entry point
├── include/          # Header files
├── third_party/      # Third-party libraries
├── build/            # Build directory
├── CMakeLists.txt    # CMake configuration
├── README.md         # This file
└── .vscode/          # VS Code configuration
```

## Build & Run

### Prerequisites

- macOS dengan Xcode Command Line Tools
- CMake 3.10+
- C++ compiler (clang atau g++)

### Compile

```bash
cd /Users/rizkidzulfikaral-qatiri/projectcss
mkdir -p build
cd build
cmake ..
make
```

### Run

```bash
./projectcpp
```

## JSON Library

Project ini menggunakan [nlohmann/json](https://github.com/nlohmann/json) - sebuah library JSON header-only yang powerful untuk C++.

### Contoh Penggunaan

```cpp
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Create object
json obj;
obj["key"] = "value";

// Parse JSON string
json parsed = json::parse(R"({"name": "John", "age": 30})");

// Dump to string
std::string jsonStr = obj.dump(2);
```

## Development

File-file penting:
- [CMakeLists.txt](CMakeLists.txt) - Build configuration
- [src/main.cpp](src/main.cpp) - Main source code
- [include/](include/) - Header files untuk project Anda

## Tips

1. **Tambah Source Files**: Edit `CMakeLists.txt` dan tambahkan file di `set(SOURCES ...)`
2. **Tambah Headers**: Letakkan di folder `include/`
3. **Tambah Libraries**: Update `target_link_libraries()` di `CMakeLists.txt`
4. **Rebuild**: Hapus folder build dan jalankan cmake lagi jika ada perubahan besar

---

Happy coding! 🚀
