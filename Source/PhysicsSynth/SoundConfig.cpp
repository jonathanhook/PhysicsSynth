/**
 * Class:	SoundConfig
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include "ImpulseSoundEvent.h"
#include "SoundConfig.h"
#include "SoundEvent.h"

namespace PhysicsSynth
{
	/* Constructors */
	SoundConfig::SoundConfig(const Colour3f	&colour, unsigned int sampleId)
	{
		this->colour			= colour;
		this->sampleId			= sampleId;

		initMapping();
	}

	SoundConfig::~SoundConfig(void)
	{
	}

	/* Public Member Functions */
	const Colour3f &SoundConfig::getColour(void) const
	{
		return colour;
	}

	std::map<unsigned int, SoundConfig::PhysicalProperty> SoundConfig::getImpulseMappings(void) const
	{
		return impulseMappings;
	}

	unsigned int SoundConfig::getSampleId(void) const
	{
		return sampleId;
	}

	SoundEvent *SoundConfig::getSoundEvent(unsigned int worldId, float positionX, float positionY, float angle, float velocity, float spin, float inertia, float contactImpulse) const
	{
		float p0 = getMappedValue(0, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float p1 = getMappedValue(1, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float p2 = getMappedValue(2, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float p3 = getMappedValue(3, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float p4 = getMappedValue(4, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float p5 = getMappedValue(5, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float p6 = getMappedValue(6, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);

		return new ImpulseSoundEvent(worldId, sampleId, p0, p1, p2, p3, p4, p5, p6);
	}

	void SoundConfig::setSampleId(unsigned int sampleId)
	{
		this->sampleId = sampleId;
	}

	void SoundConfig::updateMapping(unsigned int from, PhysicalProperty to)
	{
		impulseMappings[from] = to;
	}

	/* Private Member Functions */
	float SoundConfig::getMappedValue(unsigned int ip, float positionX, float positionY, float angle, float velocity, float spin, float inertia, float contactImpulse) const
	{
		PhysicalProperty p = (*impulseMappings.find(ip)).second;

		switch(p)
		{
			case POS_X: 
				return positionX;

			case POS_Y: 
				return positionY;

			case ANGLE: 
				return angle;

			case VELOCITY: 
				return velocity;

			case SPIN: 
				return spin;

			case INERTIA: 
				return inertia;

			case CONTACT_IMPULSE:
				return contactImpulse;
			default:
				assert(false);
				break;
		}

		return 0.0f;
	}

	void SoundConfig::initMapping(void)
	{
		impulseMappings[0] = POS_X;
		impulseMappings[1] = POS_Y;
		impulseMappings[2] = ANGLE;
		impulseMappings[3] = VELOCITY;
		impulseMappings[4] = SPIN;
		impulseMappings[5] = INERTIA;
		impulseMappings[6] = CONTACT_IMPULSE;
	}
}
