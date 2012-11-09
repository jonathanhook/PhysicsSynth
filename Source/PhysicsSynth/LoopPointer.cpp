/**
 * This file is part of PhysicsSynth.
 *
 * Created by Jonathan Hook (jonathan.hook@ncl.ac.uk)
 * Copyright (c) 2010-2012 Jonathan Hook. All rights reserved.
 *
 * PhysicsSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PhysicsSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PhysicsSynth.  If not, see <http://www.gnu.org/licenses/>.
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
