/**
 * Class:	PointQueryCallback
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <Box2D/Dynamics/b2Fixture.h>
#include "PointQueryCallback.h"

namespace PhysicsSynth
{
	/* Constructors */
	PointQueryCallback::PointQueryCallback(const b2Vec2& point)
	{
		this->point	= point;
		fixture		= NULL;
	}

	/* Public Member Functions */
	b2Fixture &PointQueryCallback::getFixture(void) const
	{
		return *fixture;
	}

	bool PointQueryCallback::hasFixture(void) const
	{
		return (fixture != NULL);
	}

	bool PointQueryCallback::ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body->GetType() == b2_dynamicBody)
		{
			bool inside = fixture->TestPoint(point);
			if (inside)
			{
				this->fixture = fixture;
				return false;
			}
		}

		return true;
	}
}
