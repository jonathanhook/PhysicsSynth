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
#include "World.h"

namespace PhysicsSynth
{
	class CircularWorld :
		public World
	{
	public:
		CircularWorld(	unsigned char		track,
						const Point2f		&position	= DEFAULT_POSITION,  
						const Vector2f		&gravity	= DEFAULT_GRAVITY, 
						float				size		= DEFAULT_SIZE);
		~CircularWorld	(void);

		bool		contains	(const FingerEventArgs &e) const;
		WorldType	getWorldType(void) const;

	private:
		static const unsigned int CIRCLE_RESOLUTION;

		bool contains		(const Point2f &p) const;
		void initHandles	(void);
		void initLimits		(void);
		void limitTranslate	(Point2f &position, float boundingRadius);
	};
}


