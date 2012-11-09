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
#include "Sounds.h"

namespace PhysicsSynth
{
	/* Private Static Variables */
	SoundConfig Sounds::NO_SOUND	= SoundConfig(Colour3f(1.0f, 1.0f, 1.0f), 0, false);
	SoundConfig Sounds::SOUND_0	= SoundConfig(Colour3f(0.93f, 0.11f, 0.14f), 1, true);
	SoundConfig Sounds::SOUND_1	= SoundConfig(Colour3f(1.0f, 0.5f, 0.15f), 2, true);
	SoundConfig Sounds::SOUND_2	= SoundConfig(Colour3f(1.0f, 0.94f, 0.0f), 3, true);
	SoundConfig Sounds::SOUND_3	= SoundConfig(Colour3f(0.13f, 0.69f, 0.29f), 4, true);
	SoundConfig Sounds::SOUND_4	= SoundConfig(Colour3f(0.63f, 0.28f, 0.64f), 5, true);
	SoundConfig Sounds::SOUND_5	= SoundConfig(Colour3f(0.0f, 1.0f, 1.0f), 6, true);
	SoundConfig Sounds::SOUND_6	= SoundConfig(Colour3f(1.0f, 0.0f, 1.0f), 7, true);

	/* Public Static Functions */
	std::vector<SoundConfig *> Sounds::getSounds(bool includeNoSound)
	{
		std::vector<SoundConfig *> sounds;
		
		if(includeNoSound)
		{
			sounds.push_back(&NO_SOUND);
		}

		sounds.push_back(&SOUND_0);
		sounds.push_back(&SOUND_1);
		sounds.push_back(&SOUND_2);
		sounds.push_back(&SOUND_3);
		sounds.push_back(&SOUND_4);
		sounds.push_back(&SOUND_5);
		sounds.push_back(&SOUND_6);

		return sounds;
	}
}