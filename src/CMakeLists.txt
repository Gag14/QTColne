cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Add your source files
set(SOURCES
    window.cpp
    color.cpp
    main.cpp
)

# Add any include directories
include_directories(/usr/include/freetype2)
include_directories(/usr/include/libpng16)

# Create an executable
add_executable(app ${SOURCES})

# Link the executable to libraries
target_link_libraries(app freetype Xft X11)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

