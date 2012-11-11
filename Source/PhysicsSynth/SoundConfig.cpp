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
#include <assert.h>
#include "ImpulseSoundEvent.h"
#include "SoundConfig.h"
#include "SoundEvent.h"

namespace PhysicsSynth
{
	/* Constructors */
	SoundConfig::SoundConfig(const Colour3f	&colour, unsigned int sampleId, bool isEnabled)
	{
		this->colour    = colour;
		this->sampleId  = sampleId;
        this->isEnabled = isEnabled;

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
    
    bool SoundConfig::getIsEnabled() const
    {
        return isEnabled;
    }

	unsigned int SoundConfig::getSampleId(void) const
	{
		return sampleId;
	}

	SoundEvent *SoundConfig::getSoundEvent(unsigned int worldId,
                                           float positionX,
                                           float positionY,
                                           float angle,
                                           float velocity,
                                           float spin,
                                           float inertia,
                                           float contactImpulse) const
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
    
    void SoundConfig::setIsEnabled(bool isEnabled)
    {
        this->isEnabled = isEnabled;
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
            case OFF:
                return 0.5f;
                
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
		impulseMappings[0] = OFF;
		impulseMappings[1] = OFF;
		impulseMappings[2] = OFF;
		impulseMappings[3] = OFF;
		impulseMappings[4] = OFF;
		impulseMappings[5] = OFF;
		impulseMappings[6] = OFF;
	}
}
