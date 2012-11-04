/**
 * Class:	WindowingUtils.h
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Point2f.h>
#include <JDHUtility/Vector2f.h>

namespace JDHUtility
{
	class WindowingUtils
	{
	public:
		static const Point2f getWindowPosition(void);
		static const Vector2f getWindowDimensions(void);
        
#ifdef IOS_WINDOWING
        static float DEVICE_WINDOW_WIDTH;
        static float DEVICE_WINDOW_HEIGHT;
#endif
	};
}

