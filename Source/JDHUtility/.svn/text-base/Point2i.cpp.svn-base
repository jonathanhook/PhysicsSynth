/**
 * Class:	Point2i
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <math.h>
#include "Point2i.h"
#include "Vector2f.h"

namespace JDHUtility
{
	/* CONSTRUCTORS */
	Point2i::Point2i(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Point2i::Point2i(void)
	{
		Point2i(0.0f, 0.0f);
	}

	Point2i::Point2i(const Point2i &position)
	{
		this->x = position.getX();
		this->y = position.getY();
	}

	Point2i::~Point2i(void)
	{

	}

	/* PUBLIC MEMBER FUNCTIONS */
	int Point2i::getX(void) const
	{
		return x;
	}

	int Point2i::getY(void) const
	{
		return y;
	}
		
	void Point2i::rotate(float theta)
	{
		int x1 = (int)(cos(theta) * (float)x - sin(theta) * (float)y);
		int y1 = (int)(sin(theta) * (float)x + cos(theta) * (float)y);

		x = x1;
		y = y1;
	}

	void Point2i::setPosition(const Point2i &position)
	{
		this->x = position.getX();
		this->y = position.getY();
	}

	void Point2i::scale(int xs, int ys)
	{
		scaleX(xs);
		scaleY(ys);
	}
		
	void Point2i::scaleX(int s)
	{
		x *= s;
	}

	void Point2i::scaleY(int s)
	{
		y *= s;
	}

	void Point2i::setX(int x)
	{
		this->x = x;
	}
		
	void Point2i::setY(int y)
	{
		this->y = y;
	}

	void Point2i::translate(int xt, int yt)
	{
		translateX(xt);
		translateY(yt);
	}

	void Point2i::translate(const Vector2f &tv)
	{
		translateX(tv.getX());
		translateY(tv.getY());
	}

	void Point2i::translateX(int t)
	{
		x += t;
	}

	void Point2i::translateY(int t)
	{
		y += t;
	}
}
