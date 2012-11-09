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
#include <JDHUtility/OpenGL.h>
#include "Menu.h"

namespace PhysicsSynth
{
    class AddressPicker;
	class Button;
    class OptionGrid;

	class SettingsMenu :
		public Menu
	{
	public:
		typedef FastDelegate0<> SavedCallback;

		SettingsMenu(const Point2i &position, unsigned int width);
		~SettingsMenu(void);

		void initMenuItems		(void);
		void render				(void);
		void setValues			(void);

#ifdef GLUT_WINDOWING
        void setSavedCallback	(SavedCallback saved);
#else
        enum PlaybackMode { INTERNAL, OSC };
#endif

	private:
        AddressPicker *addressPicker;
        
#ifdef GLUT_WINDOWING
        Button			*save;
		SavedCallback	saved;
		Button			*quit;

		void save_Clicked	(UIElement *sender);
		void quit_Clicked	(UIElement *sender);
#else
        OptionGrid *playbackMode;
        
        void playbackMode_SelectionChanged(const OptionGrid::Option & option);
#endif
	};
}

