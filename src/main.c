#include <stdio.h>
#include <stdlib.h>

#include "include/window.h"

int main(int argc, char *argv[])
{
  mango_window_new(1280, 720, "Mango Framework Test");
  
  while (1)
  {
    
  }

  mango_window_destroy();

  return 0;
}
