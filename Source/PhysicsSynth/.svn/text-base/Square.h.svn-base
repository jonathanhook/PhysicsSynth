/**
 * Class:	Square
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "SimpleObject.h"

namespace PhysicsSynth
{
	class Square :
		public SimpleObject
	{
	public:
		Square(	bool		isLocked	= DEFAULT_IS_LOCKED,
				float		size		= DEFAULT_SIZE,
				SoundConfig	*sound		= &Sounds::NO_SOUND,
				float		friction	= DEFAULT_FRICTION,
				float		restitution	= DEFAULT_RESTITUTION);
		~Square	(void);

		void				addToWorld		(b2World *world, const Point2f &position);	
		bool				contains		(const FingerEventArgs &e) const;
		PhysicsObjectType	getObjectType	(void) const;
		void				render			(void);
		void				setSize			(float size);

	private:
		unsigned int backgroundDl;
		unsigned int borderDl;

		void renderShape(void);
		void setupShape	(b2Shape *shape);
	};
}

