/**
 * Class:	SquareWorld
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "World.h"

namespace PhysicsSynth
{
	class SquareWorld :
		public World
	{
	public:
		SquareWorld(unsigned char		track,
					const Point2f		&position	= DEFAULT_POSITION, 
					const Vector2f		&gravity	= DEFAULT_GRAVITY, 
					float				size		= DEFAULT_SIZE);
		~SquareWorld(void);

		bool		contains	(const FingerEventArgs &e) const;
		WorldType	getWorldType(void) const;

	private:
		bool contains		(const Point2f &p) const;
		void initHandles	(void);
		void initLimits		(void);
		void limitTranslate	(Point2f &position, float boundingRadius);

	};
}

