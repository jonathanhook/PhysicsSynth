/**
 * Class:	SoundEvent
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include "SoundEvent.h"

namespace PhysicsSynth
{
	/* Constructors */
	SoundEvent::SoundEvent(unsigned int worldId, unsigned int sampleId)
	{
		this->worldId	= worldId;
		this->sampleId	= sampleId;
	}

	SoundEvent::~SoundEvent(void)
	{
	}
}
