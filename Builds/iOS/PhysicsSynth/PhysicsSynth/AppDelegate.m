//
//  AppDelegate.m
//  PhysicsSynth
//
//  Created by Jonathan Hook on 05/10/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@implementation AppDelegate

- (void)dealloc
{
    [_window release];
    [_viewController release];
    [super dealloc];
}

@synthesize audioController = audioController_;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController" bundle:nil] autorelease];
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    /*
    self.audioController = [[[PdAudioController alloc] init] autorelease];
	[self.audioController configurePlaybackWithSampleRate:44100 numberChannels:2 inputEnabled:NO mixingEnabled:YES];
	[PdBase openFile:@"internal.pd" path:[[NSBundle mainBundle] resourcePath]];
	[self.audioController setActive:YES];
    */
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    self.viewController.paused = YES;
    [self.audioController setActive:NO];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    [self.viewController save];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    self.viewController.paused = NO;
    [self.audioController setActive:YES];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [self.viewController save];
}

@end
