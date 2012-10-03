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

		double	getLoopPosition	(void) const;
		void	setLoopPosition	(double loopPosition);
		void	update			(double rate = DEFAULT_RATE);

	private:
		static const double DEFAULT_RATE;
		static const double RATE_MULTIPLIER;

		double last;
		double loopPosition;
	};
}

