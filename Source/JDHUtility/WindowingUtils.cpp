/**
 * Class:	WindowingUtils.cpp
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
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
    // default values, set actual values using Objective-C call in main
    float WindowingUtils::DEVICE_WINDOW_WIDTH = 0.0f;
    float WindowingUtils::DEVICE_WINDOW_HEIGHT = 0.0f;
    
	const Point2f WindowingUtils::getWindowPosition(void)
	{
        return Point2f(0.0f, 0.0f);
	}
    
	const Vector2f WindowingUtils::getWindowDimensions(void)
	{
		return Vector2f(DEVICE_WINDOW_WIDTH, DEVICE_WINDOW_HEIGHT);
	}
}
#endif 