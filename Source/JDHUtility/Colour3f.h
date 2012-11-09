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
#ifndef Colour3f_H
#define Colour3f_H

#include <string>

namespace JDHUtility
{
	class Colour3f
	{
	public:
		Colour3f	(float r, float g, float b);
		Colour3f	(void);
		~Colour3f	(void);

		float	getR	(void) const;
		float	getG	(void) const;
		float	getB	(void) const;
		void	setR	(float r);
		void	setG	(float g);
		void	setB	(float b);
		void	use		(void) const;

	protected:
		float r, g, b;
	};
}
#endif