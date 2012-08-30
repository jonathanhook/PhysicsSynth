/**
 * Class:	FingerQueryCallback
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Common/b2Math.h>
#include "FingerQueryCallback.h"

namespace PhysicsSynth
{
	/* Constructors */
	FingerQueryCallback::FingerQueryCallback(const b2Vec2& point, float fingerSize)
	{
		this->point			= point;
		this->fingerSize	= fingerSize;
		
		fixture	= NULL;
	}

	/* Public Member Functions */
	const b2Vec2 &FingerQueryCallback::getCollisionPoint(void) const
	{
		return collisionPoint;
	}

	b2Fixture &FingerQueryCallback::getFixture(void) const
	{
		return *fixture;
	}

	bool FingerQueryCallback::hasFixture(void) const
	{
		return (fixture != NULL);
	}

	bool FingerQueryCallback::ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body->GetType() == b2_dynamicBody)
		{
			bool inside = fixture->TestPoint(point);
			if (inside)
			{
				this->fixture	= fixture;
				collisionPoint	= point;

				return false;
			}
			else
			{
				b2RayCastInput input;
				input.p1 = point;

				// Find relative vector to origin of fixture
				b2Vec2 v = (body->GetPosition() - point);
				v.Normalize();
				v *= fingerSize;

				input.p2 = input.p1 + v;
				input.maxFraction = 1.0f;

				b2RayCastOutput output;

				bool hit = fixture->RayCast(&output, input);
				if (hit)
				{
					this->fixture = fixture;

					b2Vec2 p3(input.p2.x - input.p1.x, input.p2.y - input.p1.y);
					collisionPoint = input.p1 + output.fraction * p3;

					return false;
				}
			}
		}
		
		return true;
	}
}