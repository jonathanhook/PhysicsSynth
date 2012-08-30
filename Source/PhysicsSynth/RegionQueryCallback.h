/**
 * Class:	QueryCallback
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <vector>

struct b2Vec2;

namespace PhysicsSynth
{
	class RegionQueryCallback : 
		public b2QueryCallback
	{
	public:
		RegionQueryCallback(void);

		const std::vector<b2Fixture *>	&getFixtures	(void) const;
		bool							hasFixtures		(void) const;
		bool							ReportFixture	(b2Fixture* fixture);

	private:
		std::vector<b2Fixture *> fixtures;
	};
}