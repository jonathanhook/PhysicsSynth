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
#include "Button.h"

namespace JDHUtility { class GLVbo; }

namespace PhysicsSynth
{
	class TargetButton :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<const Vector2f &> TargetChangedCallback;

		TargetButton(std::string text, const Point2i &position, unsigned int width);
		~TargetButton(void);

		void			fingerAdded				(const FingerEventArgs &e);
		void			fingerUpdated			(const FingerEventArgs &e);
		void			fingerRemoved			(const FingerEventArgs &e);
		const Vector2f	&getTargetPosition		(void) const;
		void			render					(void);
		void			setTargetChangedCallback(TargetChangedCallback targetChanged);
		void			setTargetPosition		(const Vector2f &targetPosition);

	private:
		static const float SNAP_THRESHOLD;
        static const float TARGET_SIZE;

		TargetChangedCallback	targetChanged;
		Vector2f				targetPosition;
        GLVbo                   *hVbo;
        GLVbo                   *vVbo;
        
        
		void updateTargetPosition(const FingerEventArgs &e);
	};
}

