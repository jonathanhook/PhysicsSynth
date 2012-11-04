/**
 * Class:	ParticleEmitter
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <Box2D/Common/b2Math.h>
#include <string>
#include <JDHUtility/Vector2f.h>
#include "DynamicObject.h"
#include "FastDelegate.h"
#include "PhysicsObject.h"

using namespace fastdelegate;
using namespace JDHUtility;

namespace JDHUtility
{
    class GLVbo;
}

class b2Fixture;

namespace PhysicsSynth
{
	class ParticleEmitter :
		public DynamicObject
	{
	public:
		ParticleEmitter(	const Vector2f		&impulse	= DEFAULT_IMPULSE,
							float				lifespan	= DEFAULT_LIFESPAN,
							float				rate		= DEFAULT_RATE,
							unsigned int		pattern		= DEFAULT_PATTERN,
							float				size		= DEFAULT_SIZE,
							SoundConfig			*sound		= &Sounds::NO_SOUND,
							float				friction	= DEFAULT_FRICTION,
							float				restitution	= DEFAULT_RESTITUTION);
		~ParticleEmitter	(void);

		void				addToWorld				(b2World *world, const Point2f &position);
		void				collide					(b2Body *cb, float cx, float cy);
		const Vector2f		&getImpulse				(void) const;
		float				getLifespan				(void) const;
		PhysicsObjectType	getObjectType			(void) const;
		void				render					(void);
		void				setImpulse				(const Vector2f &impulse);
		void				setLifespan				(float lifespan);
		void				update					(void);

	private:
		static const unsigned int	CIRCLE_VERTICES;
		static const Vector2f		DEFAULT_IMPULSE;
		static const float			DEFAULT_LIFESPAN;
		static const unsigned int	LIFESPAN_BARS;
		static const float			MAX_IMPULSE;
		static const unsigned int	MAX_PARTICLE_COUNT = 64;
		static const float			MAX_PARTICLE_SIZE;
		static const float			MIN_PARTICLE_SIZE;
		static const std::string	TEXTURE_PATH;

		static unsigned int globalParticleCounter;
		
		struct Particle
		{
			bool			active;
			b2Body			*body;
			bool			collided;
			unsigned int	created;
			float			cx;
			float			cy;
			b2Fixture		*fixture;
			unsigned int	lifespan;
			float			size;

			Particle(void)
			{
				active		= false;
				body		= NULL;
				collided	= false;
				created		= 0;
				cx			= 0.0f;
				cy			= 0.0f;
				fixture		= NULL;
				lifespan	= 0;
				size		= 0.0f;
			}
		};

        GLVbo               *centreLineVbo;
		Vector2f			impulse;
		float				lifespan;
		unsigned int		particlePtr;
		Particle			particles[MAX_PARTICLE_COUNT];
		
		void			addParticle			(void);
		b2Vec2			getInitialImpulse	(float mass) const;
		unsigned int	getLifespanMs		(void) const;
		float			getNewParticleSize	(void) const;
		SoundEvent		*getSoundEvents		(bool &isArray, unsigned int &count);
		void			initParticles		(void);
		void			onPatternTick		(void);
		void			renderParticles		(void);
		void			updateFixtures		(void);
		void			updateParticles		(void);

	};
}

