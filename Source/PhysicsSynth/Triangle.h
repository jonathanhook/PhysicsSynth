/**
 * Class:	Triangle
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "SimpleObject.h"

namespace PhysicsSynth
{
	class Triangle :
		public SimpleObject
	{
	public:
		Triangle(	bool		isLocked	= DEFAULT_IS_LOCKED,
					float		size		= DEFAULT_SIZE,
					SoundConfig	*sound		= &Sounds::NO_SOUND,
					float		friction	= DEFAULT_FRICTION,
					float		restitution	= DEFAULT_RESTITUTION);
		~Triangle	(void);

		void				addToWorld		(b2World *world, const Point2f &position);	
		bool				contains		(const FingerEventArgs &e) const;
		PhysicsObjectType	getObjectType	(void) const;
		void				render			(void);
		void				renderThumbnail	(void);
		void				setSize			(float size);

	private:
		static const float THUMBNAIL_SCALE;

		unsigned int	backgroundDl;
		unsigned int	borderDl;
		Point2f			points[3];

		bool barrycentricInclusion	(const Point2f &p, const Point2f &a, const Point2f &b, const Point2f &c) const; 
		void initPoints				(void);

		void renderShape(void);
		void setupShape	(b2Shape *shape);
	};
}

