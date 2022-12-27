#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "include/macevent.h"
#import "include/macapp.h"

void macos_event_poll()
{
  [NSApp run];
}
