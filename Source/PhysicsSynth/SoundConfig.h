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
		enum PhysicalProperty	{ POS_X, POS_Y, ANGLE, VELOCITY, SPIN, INERTIA, CONTACT_IMPULSE };
        
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

