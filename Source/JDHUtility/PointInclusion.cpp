/**
 * Class:	PointInclusion
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <math.h>
#include "Point2f.h"
#include "PointInclusion.h"
#include "Vector2f.h"

namespace JDHUtility
{
	/* Public Static Functions */
	bool PointInclusion::circle(const Point2f& p, float radius, const Point2f &centre)
	{
		float dx	= p.getX() - centre.getX();
		float dy	= p.getY() - centre.getY();
		float d		= sqrt((dx * dx) + (dy * dy));

		return d <= radius;
	}

	bool PointInclusion::circleInCircle(const Point2f &iCentre, float iRadius, const Point2f &oCentre, float oRadius)
	{
		Vector2f d(iCentre.getX() - oCentre.getX(), iCentre.getY() - oCentre.getY());
		float distanceFromCentre = d.getMagnitude();

		return (distanceFromCentre + iRadius) <= oRadius;
	}

	bool PointInclusion::circleInRectangle	(const const Point2f &iCentre, float iRadius, const Point2f &oCentre, const Vector2f &oDimensions)
	{
		float minX = iCentre.getX() - iRadius;
		float maxX = iCentre.getX() + iRadius;
		float minY = iCentre.getY() - iRadius;
		float maxY = iCentre.getY() + iRadius;

		return	(minX >= (oCentre.getX() - oDimensions.getX())) &&
				(maxX <= (oCentre.getX() + oDimensions.getX()))	&&
				(minY >= (oCentre.getY() - oDimensions.getY())) &&
				(maxY <= (oCentre.getY() + oDimensions.getY()));
	}

	bool PointInclusion::rectangle(const Point2f &p, const Vector2f &dimensions, const Point2f &position, bool centred)
	{
		float px	= p.getX() + position.getX();
		float py	= p.getY() + position.getY();

		if(centred)
		{
			float dimX = dimensions.getX() / 2.0f;
			float dimY = dimensions.getY() / 2.0f;

			return	(px >= -dimX)	&&
					(px <= dimX)	&&
					(py >= -dimY)	&&
					(py <= dimY);
		}
		else
		{
			float dimX = dimensions.getX();
			float dimY = dimensions.getY();

			return	(px >= 0.0f)	&&
					(px <= dimX)	&&
					(py >= 0.0f)	&&
					(py <= dimY);
		}
	}

	// uses barrycentric method
	bool PointInclusion::triangle(const Point2f &p, const Point2f &a, const Point2f &b, const Point2f &c)
	{
		// Compute vectors        
		Vector2f v0(c.getX() - a.getX(), c.getY() - a.getY());
		Vector2f v1(b.getX() - a.getX(), b.getY() - a.getY());
		Vector2f v2(p.getX() - a.getX(), p.getY() - a.getY());

		// Compute dot products
		float dot00 = v0.getDotProduct(v0);
		float dot01 = v0.getDotProduct(v1);
		float dot02 = v0.getDotProduct(v2);
		float dot11 = v1.getDotProduct(v1);
		float dot12 = v1.getDotProduct(v2);

		// Compute barycentric coordinates
		float invDenom	= 1.0f / (dot00 * dot11 - dot01 * dot01);
		float u			= (dot11 * dot02 - dot01 * dot12) * invDenom;
		float v			= (dot00 * dot12 - dot01 * dot02) * invDenom;

		// Check if point is in triangle
		return (u > 0) && (v > 0) && (u + v < 1);
	}
}
