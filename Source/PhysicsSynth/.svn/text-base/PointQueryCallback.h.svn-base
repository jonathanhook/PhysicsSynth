/**
 * Class:	PointQueryCallback
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>

struct b2Vec2;

namespace PhysicsSynth
{
	class PointQueryCallback : 
		public b2QueryCallback
	{
	public:
		PointQueryCallback(const b2Vec2& point);

		b2Fixture	&getFixture		(void) const;
		bool		hasFixture		(void) const;
		bool		ReportFixture	(b2Fixture* fixture);

	private:
		b2Vec2		point;
		b2Fixture	*fixture;
	};
}