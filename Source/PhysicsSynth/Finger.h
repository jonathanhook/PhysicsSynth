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
#include <JDHUtility/Point2f.h>
#include <JDHUtility/Vector2f.h>

using namespace JDHUtility;

namespace PhysicsSynth
{
	class Finger
	{
	public:
		Finger(unsigned int id, const Point2f &position);
		~Finger(void);

		unsigned int	getId				(void) const;
		Vector2f		getDelta			(void) const;
		float			getDistanceMoved	(void) const;
		const Point2f	&getFirstPosition	(void) const;
		const Point2f	&getLastPosition	(void) const;
		const Point2f	&getPosition		(void) const;
		unsigned int	getTimeCreated		(void) const;
		unsigned int	getTimeSinceCreated	(void) const;
		bool			isMarked			(void) const;
		void			setMarked			(bool marked);
		void			updatePosition		(const Point2f &position);

	private:
		Point2f			firstPosition;
		unsigned int	id;
		Point2f			lastPosition;
		bool			marked;
		Point2f			position;
		unsigned int	timeCreated;

	};
}

