#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/glad.h>
#include "include/window.h"

#ifdef _WIN32
  #include "windows/include/winwindow.h"
  #include "windows/include/wincontext.h"
#elif __APPLE__
  #include "macos/include/macwindow.h"
#endif

// Window's color
int r = 0;
int g = 0;
int b = 0;

void mango_window_new(unsigned int width, unsigned int height, const char *title)
{
  #ifdef _WIN32
    windows_opengl_init();
    windows_window_new(width, height, title);
    windows_opengl_createContext();

    glViewport(0, 0, width, height);
  #elif __APPLE__
    macos_window_create(width, height, title);
  #endif
}

// Closes a window
void mango_window_destroy()
{
  #ifdef _WIN32
    windows_window_destroy();
  #elif __APPLE__
    macos_window_destroy();
  #endif
}

// Sets the color of the window
void mango_window_setColor(int red, int green, int blue)
{
  r = red;
  g = green;
  b = blue;
}

// Clears the window's renderer
void mango_window_clear()
{
  glClearColor((float)r/255.0f, (float)g/255.0f, (float)b/255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

// Swaps both window buffers
void mango_window_render()
{
  #ifdef _WIN32
    windows_opengl_render();
  #endif
}
