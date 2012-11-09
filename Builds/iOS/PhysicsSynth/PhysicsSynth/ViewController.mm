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
#include <FileLocationUtility.h>
#include <JDHUtility/OSCSender.h>
#include <JDHUtility/WindowingUtils.h>
#include <PhysicsSynth/Synchronizer.h>
#include <PhysicsSynth/Manager.h>
#import "ViewController.h"

@interface ViewController ()
{
}

@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ViewController

PhysicsSynth::Manager *manager;

- (void) save
{
    assert(manager);
    manager->save();
}

- (void)dealloc
{
    [_context release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1] autorelease];
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGSize screenSize = CGSizeMake(screenBounds.size.width, screenBounds.size.height);
    
    float width = screenSize.height;
    float height = screenSize.width;
    
    WindowingUtils::DEVICE_WINDOW_WIDTH = width;
    WindowingUtils::DEVICE_WINDOW_HEIGHT = height;
    
    [self setupGL];
    
    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    FileLocationUtility::setResourcePath([resourcePath UTF8String]);
    
    OSCSender *sender = new OSCSender(127, 0, 0, 1, 8080);
    manager->setOscSender(sender);
    
    manager = new PhysicsSynth::Manager(width, false);
    manager->load();
}

- (void)viewDidUnload
{    
    [super viewDidUnload];
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context)
    {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
    delete manager;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    }
    else
    {
        return YES;
    }
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];

    float width = WindowingUtils::DEVICE_WINDOW_WIDTH;
    float height = WindowingUtils::DEVICE_WINDOW_HEIGHT;
    
	if(height == 0)
	{
		height = 1;
	}
    
	float ratio = (float)width / (float)height;
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
    glOrthof(0.0f, 1.0f, 1.0f / ratio, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, width, height);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    assert(manager);
    manager->update();
    
    PhysicsSynth::Synchronizer *sync = PhysicsSynth::Synchronizer::getInstance();
    assert(sync);
    sync->update();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    
    assert(manager);
    manager->render();
    
#ifdef _DEBUG
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf("OpenGL error: %i\n", error);
    }
#endif
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSSet *allTouches = [event allTouches];
    
    // todo: multiple touches
    UITouch *touch = [[allTouches allObjects] objectAtIndex:(0)];
    CGPoint p = [touch locationInView:(self.view)];
    
    CGFloat x = p.x / WindowingUtils::DEVICE_WINDOW_WIDTH;
    CGFloat y = p.y / WindowingUtils::DEVICE_WINDOW_WIDTH;
    
    assert(manager);
    manager->raiseEvent(0, x, y, FingerEventArgs::FINGER_ADDED);
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSSet *allTouches = [event allTouches];
    
    // todo: multiple touches
    UITouch *touch = [[allTouches allObjects] objectAtIndex:(0)];
    CGPoint p = [touch locationInView:(self.view)];
    
    CGFloat x = p.x / WindowingUtils::DEVICE_WINDOW_WIDTH;
    CGFloat y = p.y / WindowingUtils::DEVICE_WINDOW_WIDTH;
    
    assert(manager);
    manager->raiseEvent(0, x, y, FingerEventArgs::FINGER_UPDATED);
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSSet *allTouches = [event allTouches];
    
    // todo: multiple touches
    UITouch *touch = [[allTouches allObjects] objectAtIndex:(0)];
    CGPoint p = [touch locationInView:(self.view)];
    
    CGFloat x = p.x / WindowingUtils::DEVICE_WINDOW_WIDTH;
    CGFloat y = p.y / WindowingUtils::DEVICE_WINDOW_WIDTH;
    
    assert(manager);
    manager->raiseEvent(0, x, y, FingerEventArgs::FINGER_REMOVED);
}

@end
