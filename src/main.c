#include <stdio.h>
#include <stdlib.h>

#include "include/window.h"
#include "windows/include/winevent.h"

int main(int argc, char *argv[])
{
  mango_window_new(1280, 720, "Mango Framework Test");
  int running = 1;

  while (running)
  {
    windows_event_poll();

    if (windows_event_closeRequested()) {
      running = 0;
      break;
    }
  }

  mango_window_destroy();
  return 0;
}
