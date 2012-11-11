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
		enum PhysicalProperty	{ OFF, POS_X, POS_Y, ANGLE, VELOCITY, SPIN, INERTIA, CONTACT_IMPULSE };
        
		SoundConfig	(const Colour3f	&colour, unsigned int sampleId, bool isEnabled);
		~SoundConfig(void);
        
        SoundEvent									*getSoundEvent		(unsigned int worldId,
                                                                         float positionX,
                                                                         float positionY,
                                                                         float angle,
                                                                         float velocity,
                                                                         float spin,
                                                                         float inertia,
                                                                         float contactImpulse) const;

		const Colour3f								&getColour			(void) const;
		std::map<unsigned int, PhysicalProperty>	getImpulseMappings	(void) const;
        bool                                        getIsEnabled        (void) const;
		unsigned int								getSampleId			(void) const;
		void										setSampleId			(unsigned int sampleId);
        void                                        setIsEnabled        (bool isEnabled);
		void										updateMapping(unsigned int from, PhysicalProperty to);

	private:
		Colour3f									colour;
		std::map<unsigned int, PhysicalProperty>	impulseMappings;
        bool                                        isEnabled;
		unsigned int								sampleId;

		float	getMappedValue	(unsigned int parameter,
                                 float positionX,
                                 float positionY,
                                 float angle,
                                 float velocity,
                                 float spin,
                                 float inertia,
                                 float contactImpulse) const;
		void	initMapping		(void);
	};
}

