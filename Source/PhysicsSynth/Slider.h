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
#pragma once
#include <string>
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class Slider :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<float> ValueChangedCallback;

		Slider(std::string label, const Point2i &position, unsigned int width);
		~Slider(void);

		void	fingerAdded				(const FingerEventArgs &e);
		void	fingerUpdated			(const FingerEventArgs &e);
		void	fingerRemoved			(const FingerEventArgs &e);
		float	getValue				(void) const;
		void	render					(void);
		void	setValue				(float value);
		void	setValueChangedCallback	(ValueChangedCallback valueChanged);

	private:
		float					value;
		ValueChangedCallback	valueChanged;

		void updateValue(const FingerEventArgs &e);
	};
}

