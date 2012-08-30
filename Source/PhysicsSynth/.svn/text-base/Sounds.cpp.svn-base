/**
 * Class:	Sounds
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include "Sounds.h"

namespace PhysicsSynth
{
	/* Private Static Variables */
	SoundConfig Sounds::NO_SOUND	= SoundConfig(Colour3f(1.0f, 1.0f, 1.0f), 0, SoundConfig::IMPULSE);
	SoundConfig Sounds::SOUND_0	= SoundConfig(Colour3f(0.93f, 0.11f, 0.14f), 1, SoundConfig::IMPULSE);
	SoundConfig Sounds::SOUND_1	= SoundConfig(Colour3f(1.0f, 0.5f, 0.15f), 2, SoundConfig::IMPULSE);
	SoundConfig Sounds::SOUND_2	= SoundConfig(Colour3f(1.0f, 0.94f, 0.0f), 3, SoundConfig::IMPULSE);
	SoundConfig Sounds::SOUND_3	= SoundConfig(Colour3f(0.13f, 0.69f, 0.29f), 4, SoundConfig::IMPULSE);
	SoundConfig Sounds::SOUND_4	= SoundConfig(Colour3f(0.63f, 0.28f, 0.64f), 5, SoundConfig::IMPULSE);
	SoundConfig Sounds::SOUND_5	= SoundConfig(Colour3f(0.0f, 1.0f, 1.0f), 6, SoundConfig::IMPULSE);
	SoundConfig Sounds::SOUND_6	= SoundConfig(Colour3f(1.0f, 0.0f, 1.0f), 7, SoundConfig::IMPULSE);

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

	void Sounds::setAll(SoundConfig::Type type)
	{
		SOUND_0.setType(type);
		SOUND_1.setType(type);
		SOUND_2.setType(type);
		SOUND_3.setType(type);
		SOUND_4.setType(type);
		SOUND_5.setType(type);
		SOUND_6.setType(type);
	}
}