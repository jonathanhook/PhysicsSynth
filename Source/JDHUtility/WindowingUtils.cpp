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