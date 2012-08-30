/**
 * Class:	LoopPointer
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <JDHUtility/CrossPlatformTime.h>
#include "LoopPointer.h"
#include "Synchronizer.h"

using namespace JDHUtility;

namespace PhysicsSynth
{
	/* Private Constants */
	const float LoopPointer::DEFAULT_RATE		= 0.5f;
	const float LoopPointer::RATE_MULTIPLIER	= 2.0f;

	/* Constructors */
	LoopPointer::LoopPointer(float loopPosition)
	{
		this->loopPosition	= loopPosition;

		last = (float)CrossPlatformTime::getTimeMillis();
	}

	LoopPointer::~LoopPointer(void)
	{
	}

	/* Public Member Functions */
	float LoopPointer::getLoopPosition(void) const
	{
		return loopPosition;
	}

	void LoopPointer::setLoopPosition(float loopPosition)
	{
		this->loopPosition = loopPosition;
	}

	void LoopPointer::update(float rate)
	{
		Synchronizer *sync = Synchronizer::getInstance();
		assert(sync);

		float loopLengthMs		= (float)sync->getOneBarMs();
		float now				= (float)CrossPlatformTime::getTimeMillis();
		float elapsed			= now - last;
		float positionChange	= (elapsed / loopLengthMs) * (rate * RATE_MULTIPLIER);
		last					= now;

		loopPosition = fmodf(loopPosition + positionChange, 1.0f);
	}
}
