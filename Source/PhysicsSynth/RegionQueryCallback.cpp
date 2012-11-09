/**
 * This file is part of PhysicsSynth.
 *
 * Created by Jonathan Hook (jonathan.hook@ncl.ac.uk)
 * Copyright (c) 2010-2012 Jonathan Hook. All rights reserved.
 *
 * PhysicsSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PhysicsSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PhysicsSynth.  If not, see <http://www.gnu.org/licenses/>.
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
