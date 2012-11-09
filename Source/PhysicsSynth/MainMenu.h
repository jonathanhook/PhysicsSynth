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
#include "FastDelegate.h"
#include "Menu.h"
#include "OptionGrid.h"

using namespace fastdelegate;

namespace PhysicsSynth
{
	class OptionGrid;

	class MainMenu :
		public Menu
	{
	public:
        enum MenuState { WORLDS, OBJECTS, SETTINGS, SOUNDS };
		
		typedef FastDelegate0<>	ObjectsSelectedCallback;
		typedef FastDelegate0<>	SettingsSelectedCallback;
		typedef FastDelegate0<>	SoundsSelectedCallback;
		typedef FastDelegate0<> WorldsSelectedCallback;

		static const std::string OBJECTS_LABEL;
		static const std::string SETTINGS_LABEL;		
		static const std::string SOUNDS_LABEL;
		static const std::string WORLDS_LABEL;

		MainMenu(const Point2i &position, unsigned int width);
		~MainMenu(void);

		void initMenuItems					(void);
		void setChecked						(MenuState checked);
		void setObjectsSelectedCallback		(ObjectsSelectedCallback objectsSelected);
		void setSettingsSelectedCallback	(SettingsSelectedCallback settingsSelected);
		void setSoundsSelectedCallback		(SoundsSelectedCallback soundsSelected);
		void setWorldsSelectedCallback		(WorldsSelectedCallback worldSelected);
		void setValues						(void);

	private:
		OptionGrid					*grid;
		ObjectsSelectedCallback		objectsSelected;
		SettingsSelectedCallback	settingsSelected;
		SoundsSelectedCallback		soundsSelected;
		WorldsSelectedCallback		worldsSelected;

		void optionGrid_SelectionChanged(const OptionGrid::Option &selection);
		void resetToDefaults			(void);
	};
}

