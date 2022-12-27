#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <X11/Xlib.h>

#include "include/linevent.h"
#include "include/linwindow.h"

XEvent event;
int closeRequested;

int linux_event_closeRequested()
{
  return closeRequested;
}

// Polls for events
void linux_event_poll()
{
  if (XNextEvent(linux_window_getDisplay(), &event) == 0)
  {
    if (event.type == ClientMessage)
    {
      if (event.xclient.data.l[0] == linux_window_getAtom())
      {
        closeRequested = 1;
      }
    }

    if (event.type == DestroyNotify)
    {
      closeRequested = 1;
    }
  }
}
