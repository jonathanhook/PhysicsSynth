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
	class ParticleEmitter;
	class PatternPicker;
	class PhysicsObject;
	class Slider;
	class TargetButton;

	class ParticleEmitterMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<Menu *, PhysicsObject *> ErasedCallback;
		
		ParticleEmitterMenu(ParticleEmitter *emitter, const Point2i &position, unsigned int width, MenuMode mode);
		~ParticleEmitterMenu(void);
			
		PhysicsObject	*createObject		(void) const;
		void			initMenuItems		(void);
		void			setErasedCallback	(ErasedCallback erased);
		void			setObject			(ParticleEmitter *emitter);
		void			setValues			(void);

	private:
		Slider			*density;
		Button			*erase;
		ErasedCallback	erased;
		ParticleEmitter *emitter;
		Slider			*friction;
		TargetButton	*impulse;
		Slider			*lifespan;
		PatternPicker	*pattern;
		Slider			*rate;
		Slider			*restitution;
		Slider			*size;
		ColourPicker	*sound;
		Button			*sync;

		void erase_Clicked				(UIElement *sender);
		void friction_ValueChanged		(float value);
		void impulse_TargetChanged		(const Vector2f &target);
		void lifespan_ValueChanged		(float value);
		void pattern_PatternChanged		(unsigned int pattern);
		void rate_ValueChanged			(float value);
		void restitution_ValueChanged	(float value);
		void size_ValueChanged			(float value);
		void sound_SelectedItemChanged	(SoundConfig *sound);
		void sync_Clicked				(UIElement *sender);
	};
}

