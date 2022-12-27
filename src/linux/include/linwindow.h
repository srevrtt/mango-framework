#ifndef linwindow_h
#define linwindow_h

#include <X11/Xlib.h>

void linux_window_new(unsigned int width, unsigned int height, const char *title);
void linux_window_destroy();

Display *linux_window_getDisplay();
Atom linux_window_getAtom();

#endif
