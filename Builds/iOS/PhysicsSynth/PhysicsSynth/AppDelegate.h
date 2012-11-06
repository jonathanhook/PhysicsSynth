//
//  AppDelegate.h
//  PhysicsSynth
//
//  Created by Jonathan Hook on 05/10/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PdAudioController.h"
#import "PdBase.h"

@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) ViewController *viewController;
@property (nonatomic, retain) PdAudioController *audioController;

@end
