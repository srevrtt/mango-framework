#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/winwindow.h"
#include <Windows.h>

HWND hwnd;
bool windowCreated = false;

// Win32 window procedure / message loop
LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
  case WM_CLOSE:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProcW(hwnd, msg, wparam, lparam);
  }

  return 0;
}

void windows_window_new(unsigned int width, unsigned int height, const char *title)
{
  if (!windowCreated)
  {
    windowCreated = true;

    // Window class
    WNDCLASSW wc;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpfnWndProc = wndproc;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"window";
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = GetModuleHandleW(NULL);

    if (!RegisterClassW(&wc))
    {
      printf("Fatal Error: Failed to create a Win32 window class.\n");
      exit(1);
    }

    // Convert UTF-8 to wide char array
    wchar_t *newtitle = malloc(4096 * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, title, -1, newtitle, 4096);

    // Create the window
    hwnd = CreateWindowExW(
      WS_EX_CLIENTEDGE,
      wc.lpszClassName,
      newtitle,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      width,
      height,
      NULL,
      NULL,
      wc.hInstance,
      NULL
    );

    if (!hwnd)
    {
      printf("Fatal Error: Failed to create a window.\n");
      exit(1);
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
  }
}

// Destroys the Win32 window
void windows_window_destroy()
{
  if (hwnd && windowCreated)
  {
    DestroyWindow(hwnd);
  }
}

// Gets the HNWD of the window
HWND windows_window_getHandle()
{
  return hwnd;
}
