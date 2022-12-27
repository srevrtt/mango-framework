@interface CustomApplication:NSApplication
- (void)run;
@end

@protocol WindowProtocol <NSWindowDelegate>
- (BOOL)windowShouldClose:(id)sender;
@end

@interface WindowDelegate:NSObject<WindowProtocol>
@end
