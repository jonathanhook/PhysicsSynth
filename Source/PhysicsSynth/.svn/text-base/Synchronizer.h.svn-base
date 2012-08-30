/**
 * Class:	Synchronizer
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once

namespace JDHUtility
{
	class LoopPointer;
}

namespace PhysicsSynth
{
	class Synchronizer
	{
	public:
		static Synchronizer	*getInstance(void);
		
		float			getBpm				(void) const;
		unsigned int	getOneBarMs			(void) const;
		float			getSnappedSliderVal (float sliderVal);
		void			setBpm				(float bpm);
		void			syncLoop			(LoopPointer *l);
		void			update				(void);
	
	private:
		static const unsigned int	BEATS_IN_BAR;
		static const float			DEFAULT_BPM;
		static const float			MULTIPLIER;
		static const float			SNAP_INCREMENT;

		static Synchronizer	*instance;

		Synchronizer(float bpm = DEFAULT_BPM);
		~Synchronizer(void);
		
		LoopPointer		*loop;
		float			bpm;
	};
}
