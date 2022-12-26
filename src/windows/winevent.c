#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Windows.h>

#include "include/winevent.h"
#include "include/winwindow.h"

MSG msg;
int closeRequested = 0;


// Returns a boolean determining if the user is trying to close the Win32 window
int windows_event_closeRequested()
{
  return closeRequested;
}

// Polls for events
void windows_event_poll()
{
  while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if (msg.message == WM_QUIT)
    {
      closeRequested = 1;
    }

    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
}

// Waits for events
void windows_event_wait()
{
  if (GetMessageW(&msg, NULL, 0, 0) == 0)
  {
    closeRequested = 1;
  }

  TranslateMessage(&msg);
  DispatchMessageW(&msg);
}
