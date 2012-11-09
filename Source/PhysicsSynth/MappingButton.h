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
#include <JDHUtility/Vector2f.h>
#include "MappingGrid.h"
#include "UIElement.h"

namespace PhysicsSynth
{
	class PushButton;

	class MappingButton :
		public UIElement
	{
	public:
		typedef FastDelegate2<MappingGrid::MappingGridItem, MappingGrid::MappingGridItem> MappingChangedCallback;

		MappingButton(MappingGrid::MappingGridItem from, std::vector<MappingGrid::MappingGridItem> options, const Point2i &position, const Point2i &dimensions);
		~MappingButton(void);
		
		MappingGrid::MappingGridItem	getFrom						(void) const;
		MappingGrid::MappingGridItem	getTo						(void) const;
		void							render						(void);
		void							setMappingChangedCallback	(MappingChangedCallback mappingChanged);
		void							setTo						(MappingGrid::MappingGridItem to);

	private:
		static const std::string LEFT_TEXTURE_PATH;
		static const std::string RIGHT_TEXTURE_PATH;

		MappingGrid::MappingGridItem				from;
		PushButton									*leftButton;
		MappingChangedCallback						mappingChanged;
		std::vector<MappingGrid::MappingGridItem>	options;
		PushButton									*rightButton;
		MappingGrid::MappingGridItem				to;
		unsigned int								toId;

		void initButtons		(void);
		void leftButton_Clicked	(UIElement *sender);
		void rightButton_Clicked(UIElement *sender);

	};
}

