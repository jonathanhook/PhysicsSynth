/**
 * Class:	FingerQueryCallback
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>

struct b2Vec2;

namespace PhysicsSynth
{
	class FingerQueryCallback : 
		public b2QueryCallback
	{
	public:
		FingerQueryCallback(const b2Vec2& point, float fingerSize);

		const b2Vec2	&getCollisionPoint	(void) const;
		b2Fixture		&getFixture			(void) const;
		bool			hasFixture			(void) const;
		bool			ReportFixture		(b2Fixture* fixture);

	private:
		b2Vec2		collisionPoint;
		b2Vec2		point;
		float		fingerSize;
		b2Fixture	*fixture;
	};
}

