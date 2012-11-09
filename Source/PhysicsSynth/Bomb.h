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
#include "DynamicObject.h"
#include "PhysicsObject.h"

class b2Body;
class b2Fixture;
class b2Shape;

namespace PhysicsSynth
{
	class Bomb :
		public DynamicObject
	{
	public:
		Bomb(	float			intensity	= DEFAULT_INTENSITY,
				float			rate		= DEFAULT_RATE,
				unsigned int	pattern		= DEFAULT_PATTERN,
				float			size		= DEFAULT_SIZE,
				SoundConfig		*sound		= &Sounds::NO_SOUND);
		~Bomb	(void);

		void				addToWorld		(b2World *world, const Point2f &position);
		float				getIntensity	(void) const;
		PhysicsObjectType	getObjectType	(void) const;
		void				render			(void);
		void				setIntensity	(float intensity);

	private:
		static const float			BLAST_IMPULSE;
		static const float			BLAST_RADIUS_OPACITY;
		static const unsigned int	CIRCLE_VERTICES;
		static const unsigned int	DECAY_TIME;
		static const float			DEFAULT_INTENSITY;
		static const unsigned short LINE_PATTERN;
		static const int			LINE_STIPPLE_FACTOR;
		static const float			MAX_BLAST_RAD_SIZE;
		static const float			MIN_BLAST_RAD_SIZE;
		static const float			MAX_INTENSITY;
		static const float			MIN_INTENSITY;
		static const std::string	TEXTURE_PATH;

		unsigned int	backgroundDl;
		unsigned int	borderDl;
		b2Fixture		*fixture;
		float			intensity;
		unsigned int	lastBlastTime;
	
		float	getBlastAlpha		(void) const;
		float	getBlastIntensity	(void) const;
		float	getBlastRadiusSize	(void) const;
		void	renderBlastRadius	(void);
		void	onPatternTick		(void);
		void	updateFixtures		(void);
	};
}

