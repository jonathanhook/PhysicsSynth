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
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class PatternPickerItem;

	class PatternPicker :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<unsigned int> PatternChangedCallback;

		PatternPicker	(unsigned int count, std::string label, const Point2i &position, unsigned int width);
		~PatternPicker	(void);

		void			fingerAdded					(const FingerEventArgs &e);
		unsigned int	getPattern					(void) const;
		void			render						(void);
		void			setPattern					(unsigned int pattern);
		void			setPatternChangedCallback	(PatternChangedCallback patternChanged);

	private:
		static const unsigned int MAX_COUNT;

		unsigned int						count;
		unsigned int						pattern;
		PatternChangedCallback				patternChanged;
		std::vector<PatternPickerItem *>	items;

		void initPatternItems(void);
	};
}

