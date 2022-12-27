#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "include/macwindow.h"
#import "include/macapp.h"

// Creates a new Cocoa (macOS) window
void macos_window_create(unsigned int width, unsigned int height, const char *title)
{
  @autoreleasepool {
    CustomApplication *app = [CustomApplication sharedApplication];

    NSUInteger styles = NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable;

    NSRect windowRect = NSMakeRect(300, 300, width, height);
    NSWindow *window = [[NSWindow alloc] initWithContentRect:windowRect styleMask:styles backing:NSBackingStoreBuffered defer:NO];

    if (window == NULL) {
      printf("Error: Failed to create an Objective C window.\n");
      exit(1);
    }

    [window setDelegate:[WindowDelegate alloc]];
    [window setTitle:[NSString stringWithUTF8String:title]];
    [window orderFrontRegardless];
  }
}

// Closes the window
void macos_window_destroy()
{
  [NSApp terminate:nil];
}
