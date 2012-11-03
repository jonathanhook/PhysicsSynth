/**
 * Class:	RegionQueryCallback
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <Box2D/Dynamics/b2Fixture.h>
#include "RegionQueryCallback.h"

namespace PhysicsSynth
{
	/* Constructors */
	RegionQueryCallback::RegionQueryCallback(void)
	{
	}

	/* Public Member Functions */
	const std::vector<b2Fixture *> &RegionQueryCallback::getFixtures(void) const
	{
		return fixtures;
	}

	bool RegionQueryCallback::hasFixtures(void) const
	{
		return fixtures.size() > 0;
	}

	bool RegionQueryCallback::ReportFixture(b2Fixture* fixture)
	{
		//b2Body* body = fixture->GetBody();
		//if (body->GetType() == b2_dynamicBody) // possibly check if is physicsobject using dynamic_cast instead
		//{
			fixtures.push_back(fixture);
			return true;
		//}

		//return true;
	}
}
