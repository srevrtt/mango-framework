cmake_minimum_required(VERSION 3.0)
project(MangoFramework VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_OBJC_STANDARD 11)
set(CMAKE_OBJC_STANDARD_REQUIRED TRUE)

if(MSVC OR MINGW)
  set(PLATFORM_SRCS src/windows/winwindow.c src/windows/winevent.c)
endif(MSVC OR MINGW)

set(SRCS ${PLATFORM_SRCS} src/main.c src/window.c)

add_subdirectory(external/lua)
include_directories(external/lua/src)
include_directories(external)

add_executable(MangoFramework ${SRCS})

if(MSVC OR MINGW)
  target_link_libraries(MangoFramework user32 gdi32 opengl32 kernel32)
endif(MSVC OR MINGW)
