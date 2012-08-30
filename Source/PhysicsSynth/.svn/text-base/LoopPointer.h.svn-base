/**
 * Class:	LoopPointer
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once

namespace JDHUtility
{

}

namespace PhysicsSynth
{
	class LoopPointer
	{
	public:
		LoopPointer(float loopPosition);
		~LoopPointer(void);

		float	getLoopPosition	(void) const;
		void	setLoopPosition	(float loopPosition);
		void	update			(float rate = DEFAULT_RATE);

	private:
		static const float DEFAULT_RATE;
		static const float RATE_MULTIPLIER;

		float last;
		float loopPosition;
	};
}

