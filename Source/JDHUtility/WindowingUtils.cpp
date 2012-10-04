/**
 * Class:	WindowingUtils.cpp
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <JDHUtility/OpenGL.h>
#include "WindowingUtils.h"

#ifdef GLUT_WINDOWING
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
#elif defined(IOS_WINDOWING)
namespace JDHUtility
{
	const Point2f &WindowingUtils::getWindowPosition(void)
	{
        return Point2f(0.0f, 0.0f);
	}
    
	const Vector2f &WindowingUtils::getWindowDimensions(void)
	{
		return Vector2f(1024.0f, 768.0f);
	}
}
#endif 