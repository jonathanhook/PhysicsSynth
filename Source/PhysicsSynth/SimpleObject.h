/**
 * Class:	SimpleObject
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "PhysicsObject.h"

class b2Body;
class b2Fixture;
class b2MouseJoint;
class b2Shape;
class b2World;

namespace PhysicsSynth
{
	class SoundEvent;

	class SimpleObject : 
		public PhysicsObject
	{
	public:
		SimpleObject(bool				isLocked	= DEFAULT_IS_LOCKED,
					float				size		= DEFAULT_SIZE,
					SoundConfig			*sound		= &Sounds::NO_SOUND,
					float				friction	= DEFAULT_FRICTION,
					float				restitution	= DEFAULT_RESTITUTION);
		~SimpleObject(void);

		virtual void			addToWorld		(b2World *world, const Point2f &position) = 0;			
		virtual bool			contains		(const FingerEventArgs &e) const = 0;
		void					fingerAdded		(const FingerEventArgs &e);
		void					fingerUpdated	(const FingerEventArgs &e);
		void					fingerRemoved	(const FingerEventArgs &e);
		const Point2f			&getPosition	(void);
		void					renderThumbnail (void);
		void					setPosition		(const Point2f &position);
		void					update			(void);

	protected:
		static const float THUMBNAIL_SCALE;

		b2Fixture	*fixture;

		void			createFixture		(b2Body &body, const b2Shape &shape);
		virtual void	renderShape			(void) = 0;
		virtual void	setupShape			(b2Shape *shape) = 0;
		void			updateLockedMass	(void);

	private:
		void updateFixtures(void);

	};
}

