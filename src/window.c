#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/window.h"

#ifdef _WIN32
#include "windows/include/winwindow.h"
#include "windows/include/wincontext.h"
#endif

void mango_window_new(unsigned int width, unsigned int height, const char *title)
{
  #ifdef _WIN32
    windows_opengl_init();
    windows_window_new(width, height, title);
    windows_opengl_createContext();
  #endif
}

// Closes a window
void mango_window_destroy()
{
  #ifdef _WIN32
    windows_window_destroy();
  #endif
}
