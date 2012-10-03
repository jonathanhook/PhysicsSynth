/**
 * Class:	Finger
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <JDHUtility/CrossPlatformTime.h>
#include <math.h>
#include "Finger.h"

namespace PhysicsSynth
{
	/* Constructors */
	Finger::Finger(unsigned int id, const Point2f &position)
	{
		this->id			= id;
		this->position		= position;
		this->lastPosition	= position;
		this->firstPosition = position;

		marked		= false;
		timeCreated = CrossPlatformTime::getTimeMillis();
	}

	Finger::~Finger(void)
	{
	}

	/* Public Member Functions */
	unsigned int Finger::getId(void) const
	{
		return id;
	}

	Vector2f Finger::getDelta(void) const
	{
		float dx = position.getX() - lastPosition.getX();
		float dy = position.getY() - lastPosition.getY();

		Vector2f delta(dx, dy);
		return delta;
	}

	float Finger::getDistanceMoved(void) const
	{
		float dx = position.getX() - firstPosition.getX();
		float dy = position.getY() - firstPosition.getY();

		return sqrt((dx * dx) + (dy * dy));
	}

	const Point2f &Finger::getFirstPosition(void) const
	{
		return firstPosition;
	}

	const Point2f &Finger::getLastPosition(void) const
	{
		return lastPosition;
	}

	const Point2f &Finger::getPosition(void) const
	{
		return position;
	}

	unsigned int Finger::getTimeCreated(void) const
	{
		return timeCreated;
	}

	unsigned int Finger::getTimeSinceCreated(void) const
	{
		unsigned int now = CrossPlatformTime::getTimeMillis();
		return (now - timeCreated);
	}

	bool Finger::isMarked(void) const
	{
		return marked;
	}

	void Finger::setMarked(bool marked)
	{
		this->marked = marked;
	}

	void Finger::updatePosition(const Point2f &position)
	{
		lastPosition.setX(this->position.getX());
		lastPosition.setY(this->position.getY());

		this->position.setX(position.getX());
		this->position.setY(position.getY());
	}
}
