/**
 * Class:	Stick
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "SimpleObject.h"

namespace PhysicsSynth
{
	class Stick :
		public SimpleObject
	{
	public:
		Stick(	bool		isLocked	= DEFAULT_IS_LOCKED,
				float		size		= DEFAULT_SIZE,
				SoundConfig	*sound		= &Sounds::NO_SOUND,
				float		friction	= DEFAULT_FRICTION,
				float		restitution	= DEFAULT_RESTITUTION);
		~Stick(void);

		void				addToWorld		(b2World *world, const Point2f &position);	
		bool				contains		(const FingerEventArgs &e) const;
		PhysicsObjectType	getObjectType	(void) const;
		void				render			(void);
		void				renderThumbnail (void);
		void				setSize			(float size);

	private:
		static const float STICK_THICKNESS;

		unsigned int backgroundDl;
		unsigned int borderDl;

		void renderShape(void);
		void setupShape	(b2Shape *shape);
	};
}

