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

namespace JDHUtility
{
	class LoopPointer;
}
using namespace JDHUtility;

namespace PhysicsSynth
{
	class Synchronizer
	{
	public:
		static Synchronizer	*getInstance(void);
		
		float			getBpm				(void) const;
		unsigned int	getOneBarMs			(void) const;
		float			getSnappedSliderVal (float sliderVal);
		void			setBpm				(float bpm);
		void			syncLoop			(LoopPointer *l);
		void			update				(void);
	
	private:
		static const unsigned int	BEATS_IN_BAR;
		static const float			DEFAULT_BPM;
		static const float			MULTIPLIER;
		static const float			SNAP_INCREMENT;

		static Synchronizer	*instance;

		Synchronizer(float bpm = DEFAULT_BPM);
		~Synchronizer(void);
		
		LoopPointer		*loop;
		float			bpm;
	};
}
