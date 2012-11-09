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
#include <MultiTouchEvents/MultiTouchEventHandler.h>
#include <JDHUtility/Point2f.h>
#include "FastDelegate.h"

using namespace fastdelegate;
using namespace MultiTouchEvents;
using namespace JDHUtility;

namespace JDHUtility
{
    class GLVbo;
}

namespace PhysicsSynth
{
	class PressAndHold
	{
	public:
		typedef FastDelegate1<const PressAndHold &>						CancelledCallback;
		typedef FastDelegate2<const PressAndHold &, const Point2f &>	CompletedCallback;
		typedef FastDelegate1<const PressAndHold &>						HalfWayCallback;

		PressAndHold(const Point2f &position, const Point2f &createPosition, unsigned int fingerId);
		~PressAndHold(void);

		bool getMarkedForDelete		(void) const;
		void render					(void);
		void setCancelledCallback	(CancelledCallback cancelled);
		void setCompletedCallback	(CompletedCallback completed);
		void setHalfWayCallback		(HalfWayCallback halfWay);
		void setMarkedForDelete		(bool markedForDelete);
		void update					(void);
		void updateFingerPosition	(const Point2f &newPosition);

	private:
		static const unsigned int	CIRCLE_SEGS;
		static const float			INNER_RAD;
		static const float			MAX_FILL_OPACITY;
        static const float			MAX_LINE_OPACITY;
		static const float			OUTER_RAD;
		static const float			THRESHOLD;
		static const unsigned int	TIMEOUT;

		CancelledCallback	cancelled;
		Point2f				createPosition;
		CompletedCallback	completed;
		bool				dirty;
		unsigned int		fingerId;
		HalfWayCallback		halfWay;
		bool				halfWayFired;
		bool				markedForDelete;
		Point2f				position;
		float				progress;
		unsigned int		timeCreated;
        GLVbo               *fillVbo;
        GLVbo               *innerLineVbo;
        GLVbo               *outerLineVbo;
	};
}

