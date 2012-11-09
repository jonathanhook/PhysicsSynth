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
#pragma once
#include <JDHUtility/Colour4f.h>

class b2Body;
class b2MouseJoint;
struct b2Vec2;
class b2World;

namespace JDHUtility { class GLVbo; }
using namespace JDHUtility;

namespace PhysicsSynth
{
	class PhysicsObject;

	class FingerJoint
	{
	public:
		FingerJoint(PhysicsObject *object, b2Body *body, const b2Vec2 &target, b2World *world);
		~FingerJoint(void);

		const b2Body	*getBody	(void) const;
		PhysicsObject	*getObject	(void) const;
		void			render		(void);
		void			updateTarget(const b2Vec2 &target);

	private:
		static const float		END_POINT_SIZE;
		static const Colour4f	VALUE_COLOUR;

		b2Body			*body;
		b2Body			*groundBody;
		b2MouseJoint	*joint;
		PhysicsObject	*object;
		b2World			*world;
        GLVbo           *pointVbo;
        GLVbo           *lineVbo;
		
		void init(const b2Vec2 &target);
	};
}

