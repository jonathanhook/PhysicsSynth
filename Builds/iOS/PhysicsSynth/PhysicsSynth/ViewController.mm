//
//  ViewController.m
//  SoundClash
//
//  Created by Jonathan Hook on 03/10/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//

#include <FileLocationUtility.h>
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
    
    [self setupGL];
    
    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    FileLocationUtility::setResourcePath([resourcePath UTF8String]);
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGSize screenSize = CGSizeMake(screenBounds.size.width, screenBounds.size.height);
    
    float width = screenSize.height;
    float height = screenSize.width;

    WindowingUtils::DEVICE_WINDOW_WIDTH = width;
    WindowingUtils::DEVICE_WINDOW_HEIGHT = height;
    
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

    float width = 1024.0f;
    float height = 768.0f;
    
	if(height == 0)
	{
		height = 1;
	}
    
	float ratio = (float)width / (float)height;
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
    glOrthof(0.0f, 1.0f, 1.0f / ratio, 0.0f, 0.0f, 100.0f);
    glViewport(0, 0, width, height);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    
    CGFloat x = p.x / 1024.0f;
    CGFloat y = p.y / 1024.0f;
    
    assert(manager);
    manager->raiseEvent(0, x, y, FingerEventArgs::FINGER_ADDED);
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSSet *allTouches = [event allTouches];
    
    // todo: multiple touches
    UITouch *touch = [[allTouches allObjects] objectAtIndex:(0)];
    CGPoint p = [touch locationInView:(self.view)];
    
    CGFloat x = p.x / 1024.0f;
    CGFloat y = p.y / 1024.0f;
    
    assert(manager);
    manager->raiseEvent(0, x, y, FingerEventArgs::FINGER_UPDATED);
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSSet *allTouches = [event allTouches];
    
    // todo: multiple touches
    UITouch *touch = [[allTouches allObjects] objectAtIndex:(0)];
    CGPoint p = [touch locationInView:(self.view)];
    
    CGFloat x = p.x / 1024.0f;
    CGFloat y = p.y / 1024.0f;
    
    assert(manager);
    manager->raiseEvent(0, x, y, FingerEventArgs::FINGER_REMOVED);
}

@end
