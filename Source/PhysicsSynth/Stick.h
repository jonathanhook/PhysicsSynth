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
#include "SimpleObject.h"

namespace PhysicsSynth
{
	class Stick :
		public SimpleObject
	{
	public:
		Stick(	bool		isLocked	= DEFAULT_IS_LOCKED,
				float		size		= DEFAULT_SIZE,
				SoundConfig	*sound		= &Sounds::NO_SOUND,
				float		friction	= DEFAULT_FRICTION,
				float		restitution	= DEFAULT_RESTITUTION);
		~Stick(void);

		void				addToWorld		(b2World *world, const Point2f &position);	
		bool				contains		(const FingerEventArgs &e) const;
		PhysicsObjectType	getObjectType	(void) const;
		void				render			(void);
		void				renderThumbnail (void);
		void				setSize			(float size);

	private:
		static const float STICK_THICKNESS;

		void renderShape(void);
		void setupShape	(b2Shape *shape);
	};
}

