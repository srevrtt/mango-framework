#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Windows.h>

#include "include/winevent.h"
#include "include/winwindow.h"

MSG msg;

int windows_event_closeRequested()
{
  return GetMessageW(&msg, NULL, 0, 0) == 0;
}

void windows_event_poll()
{
  TranslateMessage(&msg);
  DispatchMessageW(&msg);
}
