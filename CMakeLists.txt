cmake_minimum_required(VERSION 3.10)
project(ProjectCPP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suppress OpenGL deprecation warnings on macOS
add_compile_options(-DGL_SILENCE_DEPRECATION)

# Find required packages
find_package(OpenGL REQUIRED)

# macOS GLUT setup
if(APPLE)
    find_library(GLUT_LIBRARY GLUT)
    find_path(GLUT_INCLUDE_DIR GLUT/glut.h)
else()
    find_package(GLUT REQUIRED)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OPENGL_INCLUDE_DIR})
if(APPLE)
    include_directories(${GLUT_INCLUDE_DIR})
endif()

# Add nlohmann/json library (header-only)
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_SOURCE_DIR}/third_party)

# Source files
set(SOURCES
    src/main.cpp
)

# Create executable
add_executable(projectcpp ${SOURCES})

# Link libraries
target_link_libraries(projectcpp 
    PRIVATE 
        nlohmann_json
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
)

# Enable testing
enable_testing()

# Add your tests here if needed
