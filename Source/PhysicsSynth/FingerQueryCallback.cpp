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