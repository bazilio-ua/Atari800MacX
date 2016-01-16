/* DisplayManager.m - Menu suppor class to 
   the Display menu functions for the 
   Macintosh OS X SDL port of Atari800
   Mark Grebe <atarimac@kc.rr.com>
   
   Based on the Preferences pane of the
   TextEdit application.

*/
#import "DisplayManager.h"
#import "xep80.h"

extern void SwitchFullscreen(void);
extern void PLATFORM_SwitchXep80(void);
extern int requestDoubleSizeChange;
extern int DOUBLESIZE;
extern int SCALE_MODE;
extern int scaleFactor;
extern int requestWidthModeChange;
extern int WIDTH_MODE;
extern int Screen_show_atari_speed;
extern int requestFullScreenChange;
extern int requestXEP80Change;
extern int requestFpsChange;
extern int requestScaleModeChange;
extern int requestGrabMouse;
extern int requestScreenshot;
extern int ANTIC_artif_mode;
extern int requestArtifChange;
extern int PLATFORM_xep80;

/* Functions which provide an interface for C code to call this object's shared Instance functions */
void SetDisplayManagerDoubleSize(int scale) {
    [[DisplayManager sharedInstance] setDoublesizeMenu:scale];
    }

void SetDisplayManagerWidthMode(int widthMode) {
    [[DisplayManager sharedInstance] setWidthmodeMenu:(widthMode)];
    }

void SetDisplayManagerFps(int fpsOn) {
    [[DisplayManager sharedInstance] setFpsMenu:(fpsOn)];
    }

void SetDisplayManagerScaleMode(int scaleMode) {
    [[DisplayManager sharedInstance] setScaleModeMenu:(scaleMode)];
    }

void SetDisplayManagerArtifactMode(int artifactMode) {
    [[DisplayManager sharedInstance] setArtifactModeMenu:(artifactMode)];
    }

void SetDisplayManagerGrabMouse(int mouseOn) {
    [[DisplayManager sharedInstance] setGrabmouseMenu:(mouseOn)];
    }

void SetDisplayManagerXEP80Mode(int xep80Enabled, int xep80Port, int xep80) {
    [[DisplayManager sharedInstance] setXEP80ModeMenu:(xep80Enabled):(xep80Port):(xep80)];
    }

@implementation DisplayManager

static DisplayManager *sharedInstance = nil;

+ (DisplayManager *)sharedInstance {
    return sharedInstance ? sharedInstance : [[self alloc] init];
}

- (id)init {
    if (sharedInstance) {
	[self dealloc];
    } else {
        [super init];
        sharedInstance = self;
    }
    return sharedInstance;
}

- (void)dealloc {
	[super dealloc];
}

/*------------------------------------------------------------------------------
*  setDoublesizeMenu - This method is used to set the menu text for the 
*     single/double size menu item.
*-----------------------------------------------------------------------------*/
- (void)setDoublesizeMenu:(int)scale
{
	switch(scale)
	{
		case 1:
			[scale1xItem setState:NSOnState];
			[scale2xItem setState:NSOffState];
			[scale3xItem setState:NSOffState];
			[scale4xItem setState:NSOffState];
			break;
		case 2:
			[scale1xItem setState:NSOffState];
			[scale2xItem setState:NSOnState];
			[scale3xItem setState:NSOffState];
			[scale4xItem setState:NSOffState];
			break;
		case 3:
			[scale1xItem setState:NSOffState];
			[scale2xItem setState:NSOffState];
			[scale3xItem setState:NSOnState];
			[scale4xItem setState:NSOffState];
			break;
		case 4:
			[scale1xItem setState:NSOffState];
			[scale2xItem setState:NSOffState];
			[scale3xItem setState:NSOffState];
			[scale4xItem setState:NSOnState];
			break;
	}
}

/*------------------------------------------------------------------------------
*  setWidthmodeMenu - This method is used to set the menu text for the 
*     short/default/full width menu item.
*-----------------------------------------------------------------------------*/
- (void)setWidthmodeMenu:(int)widthMode
{
	switch(widthMode)
	{
		case 0:
			[widthModeNarrowItem setState:NSOnState];
			[widthModeDefaultItem setState:NSOffState];
			[widthModeFullItem setState:NSOffState];
			break;
		case 1:
			[widthModeNarrowItem setState:NSOffState];
			[widthModeDefaultItem setState:NSOnState];
			[widthModeFullItem setState:NSOffState];
			break;
		case 2:
			[widthModeNarrowItem setState:NSOffState];
			[widthModeDefaultItem setState:NSOffState];
			[widthModeFullItem setState:NSOnState];
			break;
	}

}

/*------------------------------------------------------------------------------
*  setGrabmouseMenu - This method is used to set/clear the enabled check for the 
*     Grab mouse menu item.
*-----------------------------------------------------------------------------*/
- (void)setGrabmouseMenu:(int)mouseOn
{
    if (mouseOn)
        [grabMouseItem setTarget:self];
    else
        [grabMouseItem setTarget:nil];
}

/*------------------------------------------------------------------------------
*  setFpsMenu - This method is used to set/clear the enabled check for the 
*     display frames per second menu item.
*-----------------------------------------------------------------------------*/
- (void)setFpsMenu:(int)fpsOn
{
    if (fpsOn)
        [displayFpsItem setState:NSOnState];
    else
        [displayFpsItem setState:NSOffState];
}

/*------------------------------------------------------------------------------
*  setScaleModeMenu - This method is used to set the menu text for the
*     normal/scanline/smooth scale mode menu item.
*-----------------------------------------------------------------------------*/
- (void)setScaleModeMenu:(int)scaleMode
{
	switch(scaleMode)
	{
		case 0:
			[scaleModeNormalItem setState:NSOnState];
			[scaleModeScanlineItem setState:NSOffState];
			[scaleModeSmoothItem setState:NSOffState];
			break;
		case 1:
			[scaleModeNormalItem setState:NSOffState];
			[scaleModeScanlineItem setState:NSOnState];
			[scaleModeSmoothItem setState:NSOffState];
			break;
		case 2:
			[scaleModeNormalItem setState:NSOffState];
			[scaleModeScanlineItem setState:NSOffState];
			[scaleModeSmoothItem setState:NSOnState];
			break;
	}
}

/*------------------------------------------------------------------------------
*  setArtifactModeMenu - This method is used to set the menu text for the
*     artifact mode menu item.
*-----------------------------------------------------------------------------*/
- (void)setArtifactModeMenu:(int)artifactMode
{
	switch(artifactMode)
	{
		case 0:
			[NoArtifactItem setState:NSOnState];
			[revXLXEGTIAItem setState:NSOffState];
			[XLXEGTIAItem setState:NSOffState];
			[GTIA400800Item setState:NSOffState];
			[CTIA400800Item setState:NSOffState];
			break;
		case 1:
			[NoArtifactItem setState:NSOffState];
			[revXLXEGTIAItem setState:NSOnState];
			[XLXEGTIAItem setState:NSOffState];
			[GTIA400800Item setState:NSOffState];
			[CTIA400800Item setState:NSOffState];
			break;
		case 2:
			[NoArtifactItem setState:NSOffState];
			[revXLXEGTIAItem setState:NSOffState];
			[XLXEGTIAItem setState:NSOnState];
			[GTIA400800Item setState:NSOffState];
			[CTIA400800Item setState:NSOffState];
			break;
		case 3:
			[NoArtifactItem setState:NSOffState];
			[revXLXEGTIAItem setState:NSOffState];
			[XLXEGTIAItem setState:NSOffState];
			[GTIA400800Item setState:NSOnState];
			[CTIA400800Item setState:NSOffState];
			break;
		case 4:
			[NoArtifactItem setState:NSOffState];
			[revXLXEGTIAItem setState:NSOffState];
			[XLXEGTIAItem setState:NSOffState];
			[GTIA400800Item setState:NSOffState];
			[CTIA400800Item setState:NSOnState];
			break;
	}
}

/*------------------------------------------------------------------------------
*  setXEP80ModeMenu - This method is used to set the menu text for the
*     XEP80 mode menu items.
*-----------------------------------------------------------------------------*/
- (void)setXEP80ModeMenu:(int)xep80Enabled:(int)xep80Port:(int)xep80;
{
	if (xep80Enabled) {
		[xep80Item setTarget:self];
		[xep80Mode0Item setState:NSOffState];
		if (xep80Port == 0) {
			[xep80Mode1Item setState:NSOnState];
			[xep80Mode2Item setState:NSOffState];
			}
		else {
			[xep80Mode1Item setState:NSOffState];
			[xep80Mode2Item setState:NSOnState];
			}
		if (xep80)
			[xep80Item setState:NSOnState];
		else
			[xep80Item setState:NSOffState];
		}
	else {
		[xep80Item setState:NSOffState];
		[xep80Item setTarget:nil];
		[xep80Mode0Item setState:NSOnState];
		[xep80Mode1Item setState:NSOffState];
		[xep80Mode2Item setState:NSOffState];
		}
}

/*------------------------------------------------------------------------------
*  doubleSize - This method handles the single/double size menu selection.
*-----------------------------------------------------------------------------*/
- (IBAction)doubleSize:(id)sender
{
    requestDoubleSizeChange = [sender tag];
}

/*------------------------------------------------------------------------------
*  fullScreen - This method handles the windowed/fullscreen menu selection.
*-----------------------------------------------------------------------------*/
- (IBAction)fullScreen:(id)sender
{
    requestFullScreenChange = 1;
}

/*------------------------------------------------------------------------------
*  xep80 - This method handles the normal/XEP80 menu selection.
*-----------------------------------------------------------------------------*/
- (IBAction)xep80:(id)sender
{
    requestXEP80Change = 1;
}

/*------------------------------------------------------------------------------
*  xep80Mode - This method handles the normal/XEP80 menu selection.
*-----------------------------------------------------------------------------*/
- (IBAction)xep80Mode:(id)sender
{
	switch ([sender tag]) {
		case 0:
			XEP80_enabled = FALSE;
			if (PLATFORM_xep80)
				PLATFORM_SwitchXep80();
			break;
		case 1:
			XEP80_enabled = TRUE;
			XEP80_port = 0;
			break;
		case 2:
			XEP80_enabled = TRUE;
			XEP80_port = 1;
			break;
	}
	[self setXEP80ModeMenu:XEP80_enabled:XEP80_port:PLATFORM_xep80];
}

/*------------------------------------------------------------------------------
*  displayFps - This method handles the display frames per second menu 
*     selection.
*-----------------------------------------------------------------------------*/
- (IBAction)displayFps:(id)sender
{
    [self setFpsMenu:(1-Screen_show_atari_speed)];
    requestFpsChange = 1;
}

/*------------------------------------------------------------------------------
*  scaleMode - This method handles the normal/scanline/smooth scale mode menu
*       selection.
*-----------------------------------------------------------------------------*/
- (IBAction)scaleMode:(id)sender
{
    requestScaleModeChange = [sender tag];
}

/*------------------------------------------------------------------------------
*  displayFps - This method handles the grab mouse menu selection.
*-----------------------------------------------------------------------------*/
- (IBAction)grabMouse:(id)sender;
{
    requestGrabMouse = 1;
}

/*------------------------------------------------------------------------------
*  screenshot - This method handles the take screenshot menu selection.
*-----------------------------------------------------------------------------*/
- (IBAction)screenshot:(id)sender
{
    requestScreenshot = 1;
}

/*------------------------------------------------------------------------------
*  widthMode - This method handles the short/default/full width mode menu 
*       selection.
*-----------------------------------------------------------------------------*/
- (IBAction)widthMode:(id)sender
{
    requestWidthModeChange = [sender tag];
}

- (IBAction)artifactModeChange:(id)sender
{
	ANTIC_artif_mode = [sender tag];
	requestArtifChange = 1;
}



@end
