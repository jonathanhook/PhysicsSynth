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
