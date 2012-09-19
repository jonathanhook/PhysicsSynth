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
	const double LoopPointer::DEFAULT_RATE		= 0.5;
	const double LoopPointer::RATE_MULTIPLIER	= 2.0;

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
	double LoopPointer::getLoopPosition(void) const
	{
		return loopPosition;
	}

	void LoopPointer::setLoopPosition(double loopPosition)
	{
		this->loopPosition = loopPosition;
	}

	void LoopPointer::update(double rate)
	{
		Synchronizer *sync = Synchronizer::getInstance();
		assert(sync);

		double loopLengthMs		= (double)sync->getOneBarMs();
		double now				= (double)CrossPlatformTime::getTimeMillis();
		double elapsed			= now - last;
		double positionChange	= (elapsed / loopLengthMs) * (rate * RATE_MULTIPLIER);
		last					= now;

		loopPosition = fmodf(loopPosition + positionChange, 1.0);
	}
}
