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

namespace JDHUtility { class GLTexture; }

namespace PhysicsSynth
{
	class Finger;
	class LoopPointer;

	class DynamicObject :
		public PhysicsObject
	{
	public:
		static const unsigned int PATTERN_LENGTH;

		DynamicObject	(std::string	texturePath,
						float			rate		= DEFAULT_RATE,
						unsigned int	pattern		= DEFAULT_PATTERN,
						float			size		= DEFAULT_SIZE,
						SoundConfig		*sound		= &Sounds::NO_SOUND,
						float			friction	= DEFAULT_FRICTION,
						float			restitution	= DEFAULT_RESTITUTION);
		~DynamicObject	(void);

		virtual void	addToWorld			(b2World *world, const Point2f &position);
		bool			contains			(const FingerEventArgs &e) const;
		void			fingerAdded			(const FingerEventArgs &e);
		void			fingerUpdated		(const FingerEventArgs &e);
		void			fingerRemoved		(const FingerEventArgs &e);
		virtual float	getBoundingRegion	(void) const;
		unsigned int	getPattern			(void) const;
		float			getRate				(void) const;
		virtual void	render				(void);
		void			renderThumbnail		(void);
		virtual void	setPattern			(unsigned int pattern);
		void			setRate				(float rate);
		virtual void	sync				(void);
		virtual void	update				(void);

	protected:
		static const unsigned int	DEFAULT_PATTERN;
		static const float			DEFAULT_RATE;
		static const float			ICON_SIZE;

		LoopPointer		*loop;
		unsigned int	pattern;
		float			rate;

		virtual	void	onPatternTick	(void) = 0;
		void			updateLockedMass(void);

	private:
		static const unsigned int	CIRCLE_VERTICES;
		static const float			THUMBNAIL_SCALE;

		Finger			*finger;
		bool			fingerDown;
		unsigned int	lastTick;
        GLTexture       *texture;
		std::string		texturePath;	

		void renderIcon(void);
	};
}

