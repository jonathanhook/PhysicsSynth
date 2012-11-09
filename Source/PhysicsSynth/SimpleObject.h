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
#include "PhysicsObject.h"

class b2Body;
class b2Fixture;
class b2MouseJoint;
class b2Shape;
class b2World;

namespace PhysicsSynth
{
	class SoundEvent;

	class SimpleObject : 
		public PhysicsObject
	{
	public:
		SimpleObject(bool				isLocked	= DEFAULT_IS_LOCKED,
					float				size		= DEFAULT_SIZE,
					SoundConfig			*sound		= &Sounds::NO_SOUND,
					float				friction	= DEFAULT_FRICTION,
					float				restitution	= DEFAULT_RESTITUTION);
		~SimpleObject(void);

		virtual void			addToWorld		(b2World *world, const Point2f &position) = 0;			
		virtual bool			contains		(const FingerEventArgs &e) const = 0;
		void					fingerAdded		(const FingerEventArgs &e);
		void					fingerUpdated	(const FingerEventArgs &e);
		void					fingerRemoved	(const FingerEventArgs &e);
		const Point2f			&getPosition	(void);
		void					renderThumbnail (void);
		void					setPosition		(const Point2f &position);
		void					update			(void);

	protected:
		static const float THUMBNAIL_SCALE;

		b2Fixture	*fixture;

		void			createFixture		(b2Body &body, const b2Shape &shape);
		virtual void	renderShape			(void) = 0;
		virtual void	setupShape			(b2Shape *shape) = 0;
		void			updateLockedMass	(void);

	private:
		void updateFixtures(void);

	};
}

