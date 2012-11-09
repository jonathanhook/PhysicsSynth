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
#include <map>
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class MappingButton;

	class MappingGrid :
		public LabelledUIElement
	{
	public:
        struct MappingGridItem
		{
			unsigned int	item;
			std::string		label;

			MappingGridItem(unsigned int item, std::string label)
			{
				this->item	= item;
				this->label = label;
			}

			MappingGridItem(void)
			{
				item	= 0;
				label	= "";
			}
		};

		typedef FastDelegate2<MappingGridItem, MappingGridItem> MappingChangedCallback;

		MappingGrid(std::vector<MappingGridItem> froms, std::vector<MappingGridItem> tos, std::string label, const Point2i &position, const Point2i &dimensions);
		~MappingGrid(void);

		void render						(void);
		void setMapping					(unsigned int from, unsigned int to);
		void setMappingChangedCallback	(MappingChangedCallback mappingChanged);

	private:
		std::vector<MappingGridItem>	froms;
		std::vector<MappingButton *>	mappingButtons;
		MappingChangedCallback			mappingChanged;
		std::vector<MappingGridItem>	tos;

		void init							(void);
		void mappingButton_MappingChanged	(MappingGridItem from, MappingGridItem to);
	};
}

