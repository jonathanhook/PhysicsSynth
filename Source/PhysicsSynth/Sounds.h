/**
 * Class:	Sounds
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
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