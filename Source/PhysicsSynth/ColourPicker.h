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
#include <JDHUtility/Colour3f.h>
#include "FastDelegate.h"
#include "LabelledUIElement.h"

using namespace fastdelegate;
using namespace JDHUtility;

namespace PhysicsSynth
{
	class ColourPickerItem;
	class SoundConfig;

	class ColourPicker : 
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<SoundConfig *> SelectionChangedCallback;

		ColourPicker(std::vector<SoundConfig *> items, std::string label, const Point2i &position, unsigned int width);
		~ColourPicker(void);

		void render						(void);
		void setPosition				(const Point2i &position);
		void setSelectedItem			(ColourPickerItem *item);
		void setSelectedItem			(SoundConfig *item);
		void setSelectionChangedCallback(SelectionChangedCallback selectionChanged);

	private:
		static const unsigned int	COLUMNS;
		static const unsigned int	PICKER_HEIGHT;

		std::vector<ColourPickerItem *> colours;
		SelectionChangedCallback		selectionChanged;

		void colourPickerItem_Checked	(ColourPickerItem *item);
		void init						(std::vector<SoundConfig *> items);
	};
}

