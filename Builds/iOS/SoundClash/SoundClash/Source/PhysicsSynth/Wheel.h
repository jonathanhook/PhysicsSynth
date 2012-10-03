/**
 * Class:	Wheel
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Vector2f.h>
#include "DynamicObject.h"

class b2Fixture;

namespace JDHUtility { class GLVbo; }

namespace PhysicsSynth
{
	class Wheel :
		public DynamicObject
	{
	public:
		Wheel(	float			rate		= DEFAULT_RATE,
				unsigned int	pattern		= DEFAULT_PATTERN,
				float			size		= DEFAULT_SIZE,
				SoundConfig		*sound		= &Sounds::NO_SOUND);
		~Wheel(void);

		void				addToWorld			(b2World *world, const Point2f &position);
		float				getBoundingRegion	(void) const;
		PhysicsObjectType	getObjectType		(void) const;
		void				render				(void);
		void				setPattern			(unsigned int pattern);
		void				setPosition			(const Point2f &position);
		void				setSize				(float size);
		void				update				(void);

	private:
		static const float			BOUNDS_OPACITY;
		static const unsigned int	CIRCLE_VERTICES;
		static const float			HUB_RADIUS;
		static const unsigned short LINE_PATTERN;
		static const int			LINE_STIPPLE_FACTOR;
		static const float			MAX_SPOKE_RAD;
		static const float			MIN_SPOKE_RAD;
		static const float			SPOKE_END;
		static const float			SPOKE_OPACITY;
		static const std::string	TEXTURE_PATH;

		b2Body						*body;
		std::vector<b2Fixture *>	fixtures;
		float						spokeAngle;
        GLVbo                       *spokeVbo;

		float	getSpokeRad		(void) const;
		void	initSpokes		(void);
		void	renderBounds	(void);
		void	renderSpokes	(void);
		void	onPatternTick	(void);
		void	updateSpokeAngle(float angle);
		void	updateSpokePos	(const Point2f &position);
		void	updateFixtures	(void);
	};
}

