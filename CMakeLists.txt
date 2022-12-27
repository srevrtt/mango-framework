cmake_minimum_required(VERSION 3.0)
project(MangoFramework VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_OBJC_STANDARD 11)
set(CMAKE_OBJC_STANDARD_REQUIRED TRUE)

if(MSVC OR MINGW)
  set(PLATFORM_SRCS src/windows/winwindow.c src/windows/winevent.c src/windows/wincontext.c)
endif(MSVC OR MINGW)

if(UNIX AND NOT APPLE)
  set(PLATFORM_SRCS src/linux/linwindow.c src/linux/linevent.c)
endif(UNIX AND NOT APPLE)

if(APPLE)
  set(PLATFORM_SRCS src/macos/macwindow.m src/macos/macapp.m src/macos/macevent.m)
  set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -framework Foundation -framework Cocoa")
endif(APPLE)

set(SRCS external/glad/glad.c ${PLATFORM_SRCS} src/main.c src/window.c src/event.c)

add_subdirectory(external/lua)
include_directories(external/lua/src)
include_directories(external)

add_executable(MangoFramework ${SRCS})

if(MSVC OR MINGW)
  target_link_libraries(MangoFramework user32 gdi32 opengl32 kernel32)
endif(MSVC OR MINGW)

if(UNIX AND NOT APPLE)
  target_link_libraries(MangoFramework X11 dl GL)
endif(UNIX AND NOT APPLE)
