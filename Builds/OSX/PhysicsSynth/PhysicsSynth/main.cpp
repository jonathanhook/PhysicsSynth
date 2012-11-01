#include <assert.h>
#include <stdio.h>
#include <GLUT/glut.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/DebugTimer.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/OSCSender.h>
#include <JDHUtility/Point2i.h>
#include <JDHUtility/GLTextureFont.h>
#include <JDHUtility/WindowingUtils.h>
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/FileLocationUtility.h>
#include <MultiTouchEvents/FingerEventArgs.h>
#include <PhysicsSynth/Manager.h>
#include <PhysicsSynth/Synchronizer.h>
#include <PhysicsSynth/World.h>

using namespace JDHUtility;
using namespace MultiTouchEvents;
using namespace PhysicsSynth;

const unsigned int	DEFAULT_HEIGHT			= 600;
const unsigned int	DEFAULT_WIDTH			= 1024;
const char			*DEFAULT_OSC_ADDRESS	= "127.0.0.1";
const char			*WINDOW_TITLE			= "Physics Synth";
const unsigned int	UPDATE_RATE				= 16;

void idle				(void);
void initPhysicsSynth	(unsigned int width, const char *address, unsigned int port);
void keyboard			(unsigned char key, int x, int y);
void mouse				(int button, int state, int x, int y);
void motion				(int x, int y);
void render				(void);
void resize				(int width, int height);
void setupProjection	(unsigned int width, unsigned int height);
void toggleFullscreen	(void);
void update				(void);

bool			frameLimiter	= true;
bool			fullscreen		= false;
unsigned int	lastUpdated		= 0;
Manager			*manager		= NULL;
bool			mouseDown		= false;
int             now				= 0;
int             elapsed			= 0;
Point2i			savedWinDims	(DEFAULT_WIDTH, DEFAULT_HEIGHT);
Point2i			savedWinPos		(0, 0);
float			zoom			= 1.0f;

void idle(void)
{
	update();
    
	now		= CrossPlatformTime::getTimeMillis();
	elapsed	= now - lastUpdated;
    
	if(elapsed >= UPDATE_RATE || !frameLimiter)
	{
		glutPostRedisplay();
		lastUpdated = now;
	}
}

void initPhysicsSynth(unsigned int width, const char *address, unsigned int port)
{
    FileLocationUtility::setResourcePath("Resources");
    
	manager = new Manager(width, false);
	Manager::setOscSender(new OSCSender(address, port));

	manager->load();
}

void keyboard(unsigned char key, int x, int y)
{
	const Vector2f &dims = WindowingUtils::getWindowDimensions();
    
	float ratio	= dims.getX() / dims.getY();
	float px	= (float)x / dims.getX();
	float py	= ((float)y / dims.getY()) / ratio;
    
	Point2f p(px, py);
    
	switch(key)
	{
		case 'f':
		case 'F':
			toggleFullscreen();
			break;
		case 'e':
		case 'E':
			assert(manager);
			manager->eraseAllObjects();
			break;
		case 'w':
		case 'W':
			assert(manager);
			manager->eraseAllWorlds();
			break;
		case 's':
		case 'S':
			assert(manager);
			manager->save();
			break;
		case 'o':
		case 'O':
			assert(manager);
			manager->load();
			break;
		case 't':
		case 'T':
			DebugTimer::printAll();
			break;
		case 'l':
		case 'L':
			frameLimiter = !frameLimiter;
			break;
		case '-':
		case '_':
			if(zoom > 1.125f)
			{
				zoom *= 0.9f;
				manager->zoom(0.9f, p);
			}
			break;
		case '+':
		case '=':
			if(zoom < 3.0f)
			{
				zoom *= 1.1f;
				manager->zoom(1.1f, p);
			}
			break;
		default:
			manager->raiseKeyEvent((unsigned char)key,  true);
			break;
	}
}


void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
	{
		int width	= glutGet(GLUT_WINDOW_WIDTH);
		float fx = (float)x / (float)width;
		float fy = (float)y / (float)width;
        
		mouseDown						= (state == GLUT_DOWN);
		FingerEventArgs::EventType type = mouseDown ? FingerEventArgs::FINGER_ADDED : FingerEventArgs::FINGER_REMOVED;
        
		manager->raiseEvent(0, fx, fy, type);
	}
}

void motion(int x, int y)
{
	if(mouseDown)
	{
		int width	= glutGet(GLUT_WINDOW_WIDTH);
		float fx = (float)x / (float)width;
		float fy = (float)y / (float)width;
        
		manager->raiseEvent(0, fx, fy, FingerEventArgs::FINGER_UPDATED);
	}
}

void render(void)
{
	assert(manager != NULL);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	manager->render();

    glutSwapBuffers();
    
#ifdef _DEBUG
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("OpenGL error: %i\n", error);
	}
#endif
}

void resize(int width, int height)
{
	setupProjection(width, height);
}

void setupProjection(unsigned int width, unsigned int height)
{
	if(height == 0)
	{
		height = 1;
	}
    
	float ratio = (float)width / (float)height;
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glOrtho(0.0f, 1.0f, 1.0f / ratio, 0.0f, 0.0f, 100.0f);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void toggleFullscreen(void)
{
	if(fullscreen)
	{
		glutReshapeWindow(savedWinDims.getX(), savedWinDims.getY());
		glutPositionWindow(savedWinPos.getX(), savedWinPos.getY());
	}
	else
	{
		unsigned int w = glutGet(GLUT_WINDOW_WIDTH);
		unsigned int h = glutGet(GLUT_WINDOW_HEIGHT);
		unsigned int x = glutGet(GLUT_WINDOW_X);
		unsigned int y = glutGet(GLUT_WINDOW_Y);
        
		savedWinDims.setX(w);
		savedWinDims.setY(h);
		savedWinPos.setX(x);
		savedWinPos.setY(y);
        
		glutFullScreen();
	}
    
	fullscreen = !fullscreen;
}

void update(void)
{
	assert(manager);
	manager->update();
    
	Synchronizer *sync = Synchronizer::getInstance();
	assert(sync);
	sync->update();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
	glutCreateWindow(WINDOW_TITLE);
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
    
	glutIdleFunc(idle); 
    
	initPhysicsSynth(DEFAULT_WIDTH, DEFAULT_OSC_ADDRESS, 3333);
	glutMainLoop();
    
	return 0;
}