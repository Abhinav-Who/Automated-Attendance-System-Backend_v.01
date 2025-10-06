cmake_minimum_required(VERSION 3.10)
project(ImageCompareApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Source files
set(SOURCES
    src/app.cpp
    src/db.cpp
    src/attendance.cpp
    src/user.cpp
    src/image_verifier.cpp
)

# Executable
add_executable(ImageCompare ${SOURCES})

# Link libraries
target_link_libraries(ImageCompare
    ${OpenCV_LIBS}
    sqlite3
)
