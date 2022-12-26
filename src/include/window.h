#ifndef window_h
#define window_h

void mango_window_new(unsigned int width, unsigned int height, const char *title);
void mango_window_destroy();

void mango_window_setColor(int r, int g, int b);

void mango_window_clear();
void mango_window_render();

#endif
