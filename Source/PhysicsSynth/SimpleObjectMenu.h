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
#include "Menu.h"

namespace PhysicsSynth
{
	class Button;
	class CheckBox;
	class ColourPicker;
	class SimpleObject;
	class Slider;

	class SimpleObjectMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<Menu *, PhysicsObject *> ErasedCallback;

		SimpleObjectMenu(SimpleObject *object, const Point2i &position, unsigned int width, MenuMode mode);
		~SimpleObjectMenu(void);

		SimpleObject	*createObject		(void) const;
		void			initMenuItems		(void);
		void			setObject			(SimpleObject *object);
		void			setErasedCallback	(ErasedCallback erased);
		void			setValues			(void);

	private:
		Button			*erase;
		ErasedCallback	erased;
		Slider			*friction;
		CheckBox		*isLocked;
		SimpleObject	*object;
		Slider			*restitution;
		Slider			*size;
		ColourPicker	*sound;

		void density_ValueChanged		(float value);
		void erase_Clicked				(UIElement *sender);
		void friction_ValueChanged		(float value);
		void isLocked_CheckedChanged	(bool checked);
		void restitution_ValueChanged	(float value);
		void size_ValueChanged			(float value);
		void sound_SelectionChanged		(SoundConfig *sound);
		
	};
}

