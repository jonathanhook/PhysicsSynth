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
#ifndef Colour4f_H
#define Colour4f_H

#include "Colour3f.h"

namespace JDHUtility
{
	class Colour4f : 
		public Colour3f
	{
	public:
		Colour4f	(float r, float g, float b, float a);
		Colour4f	(void);
		~Colour4f	(void);
	
		float	getA	(void) const;
		void	setA	(float a);
		void	use		(void) const;

	protected:
		float a;

	};
}
#endif
