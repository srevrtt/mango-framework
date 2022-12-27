#include <stdio.h>
#include <stdlib.h>

#include "include/event.h"

#ifdef _WIN32
  #include "windows/include/winevent.h"
#elif __APPLE__
  #include "macos/include/macevent.h"
#endif

// Updates each value in the event provided by polling for events
void mango_event_poll(MangoEvent *event)
{
  #ifdef _WIN32
    windows_event_poll();

    if (windows_event_closeRequested())
    {
      event->closeRequested = 1;
    }
  #elif __APPLE__
    macos_event_poll();

    if (macos_event_closeRequested())
    {
      event->closeRequested = 1;
    }
  #endif
}

// Updates each value in the event provided by waiting for events
void mango_event_wait(MangoEvent *event)
{
  #ifdef _WIN32
    windows_event_wait();

    if (windows_event_closeRequested())
    {
      event->closeRequested = 1;
    }
  #endif
}
