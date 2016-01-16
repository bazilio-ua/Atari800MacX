/* MonitorWindow.h - MonitorWindow 
 header  For the Macintosh OS X SDL port of Atari800
 Mark Grebe <atarimac@kc.rr.com>
 
 */

#import <Cocoa/Cocoa.h>


@interface MonitorWindow : NSWindow {
}

- (void)selectAll:(id)sender;
- (void)sendEvent:(NSEvent *)anEvent;

@end
