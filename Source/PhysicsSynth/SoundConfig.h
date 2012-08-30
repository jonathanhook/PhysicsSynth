/**
 * Class:	SoundConfig
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Colour3f.h>
#include <map>

using namespace JDHUtility;

namespace PhysicsSynth
{
	class SoundEvent;

	class SoundConfig
	{
	public:
		typedef enum ImpulseProperty	{ TRANSPOSE, STRETCH, DRIVE, FREQUENCY, RESONANCE, DECAY, PAN };
		typedef enum PhysicalProperty	{ POS_X, POS_Y, ANGLE, VELOCITY, SPIN, INERTIA, CONTACT_IMPULSE };
		typedef enum Type				{ RAW, IMPULSE };

		SoundConfig	(const Colour3f	&colour, unsigned int sampleId, Type type);
		~SoundConfig(void);

		const Colour3f								&getColour			(void) const;
		std::map<ImpulseProperty, PhysicalProperty>	getImpulseMappings	(void) const;
		unsigned int								getSampleId			(void) const;
		SoundEvent									*getSoundEvent		(unsigned int worldId, float positionX, float positionY, float angle, float velocity, float spin, float inertia, float contactImpulse) const;
		Type										getType				(void) const;
		void										setSampleId			(unsigned int sampleId);
		void										setType				(Type type);
		void										updateImpulseMapping(ImpulseProperty from, PhysicalProperty to);

	private:
		Colour3f									colour;
		std::map<ImpulseProperty, PhysicalProperty>	impulseMappings;
		unsigned int								sampleId;
		Type										type;

		float	getMappedValue	(ImpulseProperty ip, float positionX, float positionY, float angle, float velocity, float spin, float inertia, float contactImpulse) const;
		void	initMapping		(void);
	};
}

