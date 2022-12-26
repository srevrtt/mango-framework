#ifndef event_h
#define event_h

typedef struct
{
  int closeRequested;
} MangoEvent;

void mango_event_poll(MangoEvent *event);
void mango_event_wait(MangoEvent *event);

#endif
