#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "include/linwindow.h"

Display *display;
Window window;
int screen;

Atom atomWmDestroyWindow;

// Creates a new X11 (Linux) window
void linux_window_new(unsigned int width, unsigned int height, const char *title)
{
  unsigned long black, white;

  // Initialize X11
  display = XOpenDisplay((char*)0);
  screen = XDefaultScreen(display);

  black = BlackPixel(display, screen);
  white = WhitePixel(display, screen);

  // Create the window
  XSetWindowAttributes attribs;
  attribs.border_pixel = white;
  attribs.background_pixel = black;
  attribs.override_redirect = True;
  attribs.event_mask = ExposureMask;

  window = XCreateWindow(display, RootWindow(display, screen), 250, 250, width, height, 0,
    DefaultDepth(display, screen), InputOutput, DefaultVisual(display, screen), CWBackPixel | CWBorderPixel | CWEventMask, &attribs);

  if (!window)
  {
    printf("Error: Failed to create an X11 window.\n");
    exit(1);
  }

  atomWmDestroyWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &atomWmDestroyWindow, 1);

  // Set the window's title
  XSetStandardProperties(display, window, title, title, None, NULL, 0, NULL);

  // Show the window
  XClearWindow(display, window);
  XMapRaised(display, window);
}

// Closes the X11 (Linux) window
void linux_window_destroy()
{
  XDestroyWindow(display, window);
  XCloseDisplay(display);
}

// Gets the X11 display handle
Display *linux_window_getDisplay()
{
  return display;
}

// Gets the X11 closing redirect atom
Atom linux_window_getAtom()
{
  return atomWmDestroyWindow;
}
