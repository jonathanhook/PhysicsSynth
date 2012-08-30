/**
 * Class:	SoundEvent
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once

namespace PhysicsSynth
{
	class SoundEvent
	{
	public:
		SoundEvent	(unsigned int worldId, unsigned int sampleId);
		~SoundEvent	(void);

		virtual void send(void) const = 0;

	protected:
		static const unsigned long	BUFFER_SIZE = 1024;

		unsigned int sampleId;
		unsigned int worldId;
	};
}

