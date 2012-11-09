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
#include <stdio.h>
#include "JDHUtility/Singleton.h"

namespace JDHUtility
{
	/* STATIC VARS */
	Singleton *Singleton::instance = NULL;

	/* CONSTRUCTORS */
	Singleton::Singleton(void)
	{
	}

	Singleton::~Singleton(void)
	{
	}

	/* PUBLIC STATIC FUNCTIONS */
	void Singleton::clearInstance(void)
	{
		if(instance != NULL)
		{
			delete instance;
			instance = NULL;
		}
	}

	Singleton *Singleton::getInstance(void)
	{
		if(instance == NULL)
		{
			instance = new Singleton();
		}

		return instance;
	}
}
