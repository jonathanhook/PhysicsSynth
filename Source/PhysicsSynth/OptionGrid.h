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
	class OptionGridItem;

	class OptionGrid :
		public LabelledUIElement
	{
	public:
        struct Option
		{
			unsigned int	id;
			std::string		label;

			Option(unsigned int id, std::string label)
			{
				this->id	= id;
				this->label = label;
			}

			Option(void)
			{
				id		= NULL;
				label	= "";
			}
		};

		typedef FastDelegate1<const Option &> SelectionChangedCallback;

		OptionGrid	(std::vector<Option> items, std::string label, const Point2i &position, unsigned int width);
		~OptionGrid	(void);

		const OptionGridItem	&getSelectedItem		(void) const;
		void					render					(void);
		void					setPosition				(const Point2i &position);
		void					setSelectedItem			(OptionGridItem *selectedItem);
		void					setSelectedItem			(unsigned int id);
		void					setSelectionChangedCallback(SelectionChangedCallback selectionChanged);
	
	private:
		static const unsigned int COLUMNS;

		std::vector<OptionGridItem *>	options;
		SelectionChangedCallback		selectionChanged;

		void init					(std::vector<Option> items);
		void optionGridItem_Checked	(OptionGridItem *option);
	
	};
}

