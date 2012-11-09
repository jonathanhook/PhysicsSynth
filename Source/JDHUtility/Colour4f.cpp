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
#include <JDHUtility/OpenGL.h>
#include "Colour4f.h"

namespace JDHUtility
{
	/* CONSTRUCTORS */
	Colour4f::Colour4f(float r, float g, float b, float a) :
		Colour3f(r, g, b)
	{
		Colour4f::a = a;
	}

	Colour4f::Colour4f(void)
	{
		Colour4f(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Colour4f::~Colour4f(void)
	{

	}

	/* PUBLIC MEMBER FUNCTIONS */
	float Colour4f::getA() const
	{
		return a;
	}

	void Colour4f::setA(float a)
	{
		this->a = a;
	}

	void Colour4f::use(void) const
	{
		glColor4f(r, g, b, a);

	}
}
