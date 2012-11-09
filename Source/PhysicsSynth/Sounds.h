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
#include <vector>
#include "SoundConfig.h"

using namespace JDHUtility;

namespace PhysicsSynth
{
	class Sounds
	{
	public:
		static SoundConfig NO_SOUND;
		static SoundConfig SOUND_0;
		static SoundConfig SOUND_1;
		static SoundConfig SOUND_2;
		static SoundConfig SOUND_3;
		static SoundConfig SOUND_4;
		static SoundConfig SOUND_5;
		static SoundConfig SOUND_6;
		static SoundConfig SOUND_7;

		static std::vector<SoundConfig *> getSounds(bool includeNoSound = true);
	};
}