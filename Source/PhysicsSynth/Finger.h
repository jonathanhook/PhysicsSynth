/**
 * Class:	Finger
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Point2f.h>
#include <JDHUtility/Vector2f.h>

using namespace JDHUtility;

namespace PhysicsSynth
{
	class Finger
	{
	public:
		Finger(unsigned int id, const Point2f &position);
		~Finger(void);

		unsigned int	getId				(void) const;
		Vector2f		getDelta			(void) const;
		float			getDistanceMoved	(void) const;
		const Point2f	&getFirstPosition	(void) const;
		const Point2f	&getLastPosition	(void) const;
		const Point2f	&getPosition		(void) const;
		unsigned int	getTimeCreated		(void) const;
		unsigned int	getTimeSinceCreated	(void) const;
		bool			isMarked			(void) const;
		void			setMarked			(bool marked);
		void			updatePosition		(const Point2f &position);

	private:
		Point2f			firstPosition;
		unsigned int	id;
		Point2f			lastPosition;
		bool			marked;
		Point2f			position;
		unsigned int	timeCreated;

	};
}

