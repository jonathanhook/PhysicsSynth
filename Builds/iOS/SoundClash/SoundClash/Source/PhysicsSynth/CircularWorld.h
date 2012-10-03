/**
 * Class:	CircularWorld
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "World.h"

namespace PhysicsSynth
{
	class CircularWorld :
		public World
	{
	public:
		CircularWorld(	unsigned char		track,
						const Point2f		&position	= DEFAULT_POSITION,  
						const Vector2f		&gravity	= DEFAULT_GRAVITY, 
						float				size		= DEFAULT_SIZE);
		~CircularWorld	(void);

		bool		contains	(const FingerEventArgs &e) const;
		WorldType	getWorldType(void) const;

	private:
		static const unsigned int CIRCLE_RESOLUTION;

		bool contains		(const Point2f &p) const;
		void initHandles	(void);
		void initLimits		(void);
		void limitTranslate	(Point2f &position, float boundingRadius);
	};
}


