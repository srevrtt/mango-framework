#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import "include/macapp.h"
#include "include/macevent.h"

int closeRequested = false;

@implementation CustomApplication
- (void)run {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  NSEvent *event = [self
    nextEventMatchingMask:NSEventMaskAny
    untilDate:[NSDate distantFuture]
    inMode:NSDefaultRunLoopMode
    dequeue:YES];

  [self sendEvent:event];
  [self updateWindows];

  [pool release];
}
@end

@implementation WindowDelegate
- (BOOL)windowShouldClose:(id)sender {
  closeRequested = 1;
  return YES;
}
@end

// Returns an integer determining if the window should close
int macos_event_closeRequested()
{
  return closeRequested;
}
