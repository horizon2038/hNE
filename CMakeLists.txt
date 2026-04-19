# CMake base configuration
cmake_minimum_required(VERSION 3.21)
include(FetchContent)

set(PROJECT_NAME "hNE")
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang" CACHE FILEPATH "" FORCE)
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++" CACHE FILEPATH "" FORCE)

# project base configuration
project(
    ${PROJECT_NAME}
    DESCRIPTION ""
    LANGUAGES C CXX
)

# C base configuration
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_EXTENSIONS OFF)

# C++ base configuration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS OFF)

# common configuration
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_subdirectory(src)
 
# Configure FLTK
FetchContent_Declare(
    fltk
    GIT_REPOSITORY "https://github.com/fltk/fltk.git"
    GIT_TAG aaabff439306215b3195dff5f2152fe6eadaa323 # v1.4.3
)
FetchContent_MakeAvailable(fltk)
if (TARGET fltk::fltk)
    target_link_libraries(${PROJECT_NAME} PRIVATE fltk::fltk)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE fltk)
endif()
