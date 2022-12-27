#include <stdio.h>
#include <stdlib.h>

#include "include/window.h"
#include "include/event.h"

#include "linux/include/linwindow.h"
#include "linux/include/linevent.h"

int main(int argc, char *argv[])
{
  // mango_window_new(1280, 720, "Mango Framework Test");
  // mango_window_setColor(0, 0, 0);

  // MangoEvent event;

  // while (1)
  // {
  //   mango_event_wait(&event);

  //   if (event.closeRequested)
  //   {
  //     break;
  //   }

  //   mango_window_clear();
  //   mango_window_render();
  // }

  // mango_window_destroy();

  // Testing Linux
  linux_window_new(1280, 720, "Mango Framework Test");

  while (1)
  {
    linux_event_poll();

    if (linux_event_closeRequested() == 1)
    {
      break;
    }
  }

  linux_window_destroy();
  return 0;
}
