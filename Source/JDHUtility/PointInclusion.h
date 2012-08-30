/**
 * Class:	PointInclusion
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
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

