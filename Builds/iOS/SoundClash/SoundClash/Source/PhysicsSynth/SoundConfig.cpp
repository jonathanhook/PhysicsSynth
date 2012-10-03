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
	SoundConfig::SoundConfig(const Colour3f	&colour, unsigned int sampleId, SoundConfig::Type type)
	{
		this->colour			= colour;
		this->sampleId			= sampleId;
		this->type				= type;

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

	std::map<SoundConfig::ImpulseProperty, SoundConfig::PhysicalProperty> SoundConfig::getImpulseMappings(void) const
	{
		return impulseMappings;
	}

	unsigned int SoundConfig::getSampleId(void) const
	{
		return sampleId;
	}

	SoundEvent *SoundConfig::getSoundEvent(unsigned int worldId, float positionX, float positionY, float angle, float velocity, float spin, float inertia, float contactImpulse) const
	{
		float transpose	= getMappedValue(TRANSPOSE, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float stretch	= getMappedValue(STRETCH, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float drive		= getMappedValue(DRIVE, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float frequency	= getMappedValue(FREQUENCY, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float resonance	= getMappedValue(RESONANCE, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float decay		= getMappedValue(DECAY, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);
		float pan		= getMappedValue(PAN, positionX, positionY, angle, velocity, spin, inertia, contactImpulse);

		return new ImpulseSoundEvent(worldId, sampleId, transpose, stretch, drive, frequency, resonance, decay, pan);
	}

	SoundConfig::Type SoundConfig::getType(void) const
	{
		return type;
	}

	void SoundConfig::setSampleId(unsigned int sampleId)
	{
		this->sampleId = sampleId;
	}

	void SoundConfig::setType(Type type)
	{
		this->type = type;
	}

	void SoundConfig::updateImpulseMapping(ImpulseProperty from, PhysicalProperty to)
	{
		impulseMappings[from] = to;
	}

	/* Private Member Functions */
	float SoundConfig::getMappedValue(ImpulseProperty ip, float positionX, float positionY, float angle, float velocity, float spin, float inertia, float contactImpulse) const
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
		impulseMappings[TRANSPOSE]	= POS_X;
		impulseMappings[STRETCH]	= POS_Y;
		impulseMappings[DRIVE]		= ANGLE;
		impulseMappings[FREQUENCY]	= VELOCITY;
		impulseMappings[RESONANCE]	= SPIN;
		impulseMappings[DECAY]		= INERTIA;
		impulseMappings[PAN]		= CONTACT_IMPULSE;
	}
}
