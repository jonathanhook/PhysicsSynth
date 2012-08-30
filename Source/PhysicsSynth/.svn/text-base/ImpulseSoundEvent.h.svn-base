/**
 * Class:	ImpulseSoundEvent
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "SoundEvent.h"

namespace PhysicsSynth
{
	class ImpulseSoundEvent :
		public SoundEvent
	{
	public:
		ImpulseSoundEvent(	unsigned int worldId,
							unsigned int sampleId,	
							float transpose,
							float stretch,
							float drive,
							float frequency,
							float resonance,
							float decay,
							float pan);
		~ImpulseSoundEvent	(void);

		void send(void) const;

	private:
		static const char *PROFILE;

		float transpose;
		float stretch;
		float drive;
		float frequency;
		float resonance;
		float decay;
		float pan;
	};
}

