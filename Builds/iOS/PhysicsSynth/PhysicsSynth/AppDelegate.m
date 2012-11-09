/**
 * This file is part of PhysicsSynth.
 *
 * Created by Jonathan Hook (jonathan.hook@ncl.ac.uk)
 * Copyright (c) 2010-2012 Jonathan Hook. All rights reserved.
 *
 * PhysicsSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PhysicsSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PhysicsSynth.  If not, see <http://www.gnu.org/licenses/>.
 */
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
