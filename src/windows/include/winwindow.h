#ifndef winwindow_h
#define winwindow_h

#include <Windows.h>

void windows_window_new(unsigned int width, unsigned int height, const char *title);
void windows_window_destroy();
HWND windows_window_getHandle();

#endif
