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
#pragma once

namespace JDHUtility
{
	class Point2f;
	class Vector2f;

	class PointInclusion
	{
	public:
		static bool circle				(const Point2f &p, float radius, const Point2f &centre = Point2f(0.0f, 0.0f));
		static bool circleInCircle		(const Point2f &iCentre, float iRadius, const Point2f &oCentre, float oRadius);
		static bool circleInRectangle	(const Point2f &iCentre, float iRadius, const Point2f &oCentre, const Vector2f &oDimensions);
		static bool rectangle			(const Point2f &p, const Vector2f &dimensions, const Point2f &position = Point2f(0.0f, 0.0f), bool centred = true);
		static bool triangle			(const Point2f &p, const Point2f &a, const Point2f &b, const Point2f &c);
	};
}

