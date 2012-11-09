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
#include <JDHUtility/Vector2f.h>
#include "DynamicObject.h"

class b2Fixture;

namespace JDHUtility { class GLVbo; }

namespace PhysicsSynth
{
	class Wheel :
		public DynamicObject
	{
	public:
		Wheel(	float			rate		= DEFAULT_RATE,
				unsigned int	pattern		= DEFAULT_PATTERN,
				float			size		= DEFAULT_SIZE,
				SoundConfig		*sound		= &Sounds::NO_SOUND);
		~Wheel(void);

		void				addToWorld			(b2World *world, const Point2f &position);
		float				getBoundingRegion	(void) const;
		PhysicsObjectType	getObjectType		(void) const;
		void				render				(void);
		void				setPattern			(unsigned int pattern);
		void				setPosition			(const Point2f &position);
		void				setSize				(float size);
		void				update				(void);

	private:
		static const float			BOUNDS_OPACITY;
		static const unsigned int	CIRCLE_VERTICES;
		static const float			HUB_RADIUS;
		static const unsigned short LINE_PATTERN;
		static const int			LINE_STIPPLE_FACTOR;
		static const float			MAX_SPOKE_RAD;
		static const float			MIN_SPOKE_RAD;
		static const float			SPOKE_END;
		static const float			SPOKE_OPACITY;
		static const std::string	TEXTURE_PATH;

		b2Body						*body;
		std::vector<b2Fixture *>	fixtures;
		float						spokeAngle;
        GLVbo                       *spokeVbo;

		float	getSpokeRad		(void) const;
		void	initSpokes		(void);
		void	renderBounds	(void);
		void	renderSpokes	(void);
		void	onPatternTick	(void);
		void	updateSpokeAngle(float angle);
		void	updateSpokePos	(const Point2f &position);
		void	updateFixtures	(void);
	};
}

