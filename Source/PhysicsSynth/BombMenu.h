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
	class Bomb;
	class Button;
	class CheckBox;
	class ColourPicker;
	class PatternPicker;
	class Slider;

	class BombMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<Menu *, PhysicsObject *> ErasedCallback;

		BombMenu(Bomb *bomb, const Point2i &position, unsigned int width, MenuMode mode);
		~BombMenu(void);

		Bomb	*createObject		(void) const;
		void	initMenuItems		(void);
		void	setErasedCallback	(ErasedCallback erased);
		void	setObject			(Bomb *Bomb);
		void	setValues			(void);

	private:
		Bomb			*bomb;
		Button			*erase;
		ErasedCallback	erased;
		Slider			*intensity;
		PatternPicker	*pattern;
		Slider			*rate;
		Slider			*size;
		ColourPicker	*sound;
		Button			*sync;

		void erase_Clicked				(UIElement *sender);
		void intensity_ValueChanged		(float value);
		void pattern_PatternChanged		(unsigned int pattern);
		void rate_ValueChanged			(float value);
		void size_ValueChanged			(float value);
		void sound_SelectionChanged		(SoundConfig *sound);
		void sync_Clicked				(UIElement *sender);
	};
}

