/**
 * Class:	WindowingUtils.cpp
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <JDHUtility/OpenGL.h>
#include "WindowingUtils.h"

// WIN32 and APPLE
#if defined _WIN32
#include <glut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#endif

#if defined _WIN32 || defined __APPLE__
namespace JDHUtility
{
	const Point2f &WindowingUtils::getWindowPosition(void)
	{
		int w = glutGet(GLUT_WINDOW_X);
		int h = glutGet(GLUT_WINDOW_Y);

		return Point2f(w, h);
	}

	const Vector2f &WindowingUtils::getWindowDimensions(void)
	{
		int w = glutGet(GLUT_WINDOW_WIDTH);
		int h = glutGet(GLUT_WINDOW_HEIGHT);

		return Vector2f(w, h);
	}
}
#endif 