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
#include <JDHUtility/GLMatrixf.h>
#include <MultiTouchEvents/MultiTouchEventHandler.h>
#include "Finger.h"

using namespace JDHUtility;
using namespace MultiTouchEvents;

namespace PhysicsSynth
{
	class RSTObject : 
		public MultiTouchEventHandler
	{
	public:
		RSTObject(bool rotateEnabled = true, bool scaleEnabled = true, bool translateEnabled = true);
		~RSTObject(void);

		void			debugScale			(float z, const Point2f &p);
		virtual bool	contains			(const FingerEventArgs &e) const = 0;
		virtual void	fingerAdded			(const FingerEventArgs &e);
		virtual void	fingerUpdated		(const FingerEventArgs &e);
		virtual void	fingerRemoved		(const FingerEventArgs &e);
		bool			isRotateEnabled		(void) const;
		bool			isScaleEnabled		(void) const;
		bool			isTranslateEnabled	(void) const;
		void			setRotateEnabled	(bool rotateEnabled);
		void			setScaleEnabled		(bool scaleEnabled);
		void			setTranslateEnabled	(bool translateEnabled);

	protected:
		std::map<int, Finger *>	fingers;
		float					scale;
		float					transform[16];

		virtual void	scaleChanged	(void);
		void			translate		(const Vector2f &delta);

	private:
		static const float MAX_SCALE;
		static const float MIN_SCALE;

		bool rotateEnabled;
		bool scaleEnabled;
		bool translateEnabled;
		
		Finger	*findOtherFinger		(unsigned int fId) const;
		void	rst						(const Finger &actuator, const Finger &anchor);
		void	setTransformToIdentity	(void);
		void	translate				(const Finger &actuator);

	};
}

