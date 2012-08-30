/**
 * Class:	Synchronizer
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <math.h>
#include <JDHUtility/Ndelete.h>
#include <stdio.h>
#include <stdlib.h>
#include "LoopPointer.h"
#include "Synchronizer.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int	Synchronizer::BEATS_IN_BAR		= 4;
	const float			Synchronizer::DEFAULT_BPM		= 140;
	const float			Synchronizer::MULTIPLIER		= 2.0f;
	const float			Synchronizer::SNAP_INCREMENT	= 0.25f;	

	/* Public Static Variables */
	Synchronizer *Synchronizer::instance = NULL;

	/* Public Static Functions */
	Synchronizer *Synchronizer::getInstance(void)
	{
		if(instance == NULL)
		{
			instance = new Synchronizer();
		}

		return instance;
	}

	/* Constructors */
	Synchronizer::Synchronizer(float bpm)
	{
		this->bpm = bpm;

		loop = new LoopPointer(0.0f);
	}

	Synchronizer::~Synchronizer(void)
	{
		NDELETE(loop);
	}

	/* Public Member Functions */
	float Synchronizer::getBpm(void) const
	{
		return bpm;
	}

	unsigned int Synchronizer::getOneBarMs(void) const
	{
		return (unsigned int)(60000.0f / bpm) * BEATS_IN_BAR;
	}

	float Synchronizer::getSnappedSliderVal(float sliderVal)
	{
		float f = sliderVal * 4.0f;
		f = floorf(f + 0.5f);
		return f / 4.0f;
	}

	void Synchronizer::setBpm(float bpm)
	{
		this->bpm = bpm;
	}

	void Synchronizer::syncLoop(LoopPointer *l)
	{
		assert(l);
		assert(loop);

		l->setLoopPosition(loop->getLoopPosition());
	}

	void Synchronizer::update(void)
	{
		assert(loop);
		loop->update();
	}
}
