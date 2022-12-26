#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <Windows.h>
#include <wgl/wglext.h>

#include "include/winwindow.h"
#include "include/wincontext.h"

// OpenGL prodecures (functions)
typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext,
  const int *attribList);

typedef BOOL WINAPI wglChoosePixelFormatARB_type(HDC hdc, const int *piAttribIList,
  const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);

wglChoosePixelFormatARB_type *wglChoosePixelFormatARB;
wglCreateContextAttribsARB_type *wglCreateContextAttribsARB;

// Initializes the creation of an OpenGL context.
// Called *before* window creation.
void windows_opengl_init()
{
  // Create a fake hWnd
  WNDCLASSW wc = {0};
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = DefWindowProcW;
  wc.hInstance = GetModuleHandleA(NULL);
  wc.lpszClassName = L"tmpopengl"; // TODO: salting

  if (!RegisterClassW(&wc))
  {
    printf("Error: Failed to register a temporary window class.\n");
    exit(1);
  }

  HWND tmpHWND = CreateWindowExW(
    WS_EX_CLIENTEDGE,
    wc.lpszClassName,
    L"Temporary Window",
    0,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    NULL,
    NULL,
    wc.hInstance,
    NULL
  );

  if (!tmpHWND)
  {
    printf("Error: Failed to create a temporary window.\n");
    exit(1);
  }

  HDC tmpHdc = GetDC(tmpHWND);

  // Choose a pixel format.. the "legacy" way
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.cColorBits = 32;
  pfd.cAlphaBits = 8;
  pfd.iLayerType = PFD_MAIN_PLANE;
  pfd.cDepthBits = 24;
  pfd.cStencilBits = 8;

  int pixelFormat = ChoosePixelFormat(tmpHdc, &pfd);
  if (!SetPixelFormat(tmpHdc, pixelFormat, &pfd))
  {
    printf("Error: Failed to set the legacy pixel format.\n");
    exit(1); 
  }

  // Create the temporary context
  HGLRC context = wglCreateContext(tmpHdc);
  
  if (!context)
  {
    printf("Error: Failed to create a temporary OpenGL context.\n");
    exit(1);
  }

  if (!wglMakeCurrent(tmpHdc, context))
  {
    printf("Error: Failed to make the temporary OpenGL context current.\n");
    exit(1);
  }

  // Load the two functions we need to create a modern context
  wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)
    wglGetProcAddress("wglCreateContextAttribsARB");
  
  wglChoosePixelFormatARB = (wglChoosePixelFormatARB_type*)
    wglGetProcAddress("wglChoosePixelFormatARB");
  
  // Delete everything we don't need
  wglMakeCurrent(tmpHdc, NULL);
  wglDeleteContext(context);
  ReleaseDC(tmpHWND, tmpHdc);
  DestroyWindow(tmpHWND);
}

// Creates an OpenGL 3.3 context.
// This is called after window creation.
void windows_opengl_createContext()
{
  HDC hdc = GetDC(windows_window_getHandle());

  // Choose the pixel format the "modern" way
  int pfa[] = {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    0
  };

  int pixelFormat;
  unsigned int numFormats;
  wglChoosePixelFormatARB(hdc, pfa, 0, 1, &pixelFormat, &numFormats);

  if (!numFormats)
  {
    printf("Error: Failed to choose the OpenGL context's pixel format\n");
    exit(1);
  }

  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(hdc, pixelFormat, sizeof(pfd), &pfd);
  SetPixelFormat(hdc, pixelFormat, &pfd);
  
  // Create the actual context
  int glAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    WGL_CONTEXT_MINOR_VERSION_ARB, 3,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
  };

  HGLRC context = wglCreateContextAttribsARB(hdc, 0, glAttribs);
  wglMakeCurrent(hdc, context);

  gladLoadGL();
}
