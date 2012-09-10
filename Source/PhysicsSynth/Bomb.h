/**
 * Class:	Bomb
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "DynamicObject.h"
#include "PhysicsObject.h"

class b2Body;
class b2Fixture;
class b2Shape;

namespace PhysicsSynth
{
	class Bomb :
		public DynamicObject
	{
	public:
		Bomb(	float			intensity	= DEFAULT_INTENSITY,
				float			rate		= DEFAULT_RATE,
				unsigned int	pattern		= DEFAULT_PATTERN,
				float			size		= DEFAULT_SIZE,
				SoundConfig		*sound		= &Sounds::NO_SOUND);
		~Bomb	(void);

		void				addToWorld		(b2World *world, const Point2f &position);
		float				getIntensity	(void) const;
		PhysicsObjectType	getObjectType	(void) const;
		void				render			(void);
		void				setIntensity	(float intensity);

	private:
		static const float			BLAST_IMPULSE;
		static const float			BLAST_RADIUS_OPACITY;
		static const unsigned int	CIRCLE_VERTICES;
		static const unsigned int	DECAY_TIME;
		static const float			DEFAULT_INTENSITY;
		static const unsigned short LINE_PATTERN;
		static const int			LINE_STIPPLE_FACTOR;
		static const float			MAX_BLAST_RAD_SIZE;
		static const float			MIN_BLAST_RAD_SIZE;
		static const float			MAX_INTENSITY;
		static const float			MIN_INTENSITY;
		static const std::string	TEXTURE_PATH;

		unsigned int	backgroundDl;
		unsigned int	borderDl;
		b2Fixture		*fixture;
		float			intensity;
		unsigned int	lastBlastTime;
	
		float	getBlastAlpha		(void) const;
		float	getBlastIntensity	(void) const;
		float	getBlastRadiusSize	(void) const;
		void	renderBlastRadius	(void);
		void	onPatternTick		(void);
		void	updateFixtures		(void);
	};
}

