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
	class ColourPicker;
	class ObjectPicker;
	class Slider;
	class SoundConfig;
	class TargetButton;
	class World;

	class WorldMenu :
		public Menu
	{
	public:
		typedef FastDelegate0<> ErasedCallback;

		WorldMenu(const Point2i &position, unsigned int width, MenuMode mode);
		~WorldMenu(void);

		World			*createWorld		(void);
		virtual	void	initMenuItems		(void);
		void			setErasedCallback	(ErasedCallback erased);
		virtual void	setValues			(void);
		void			setWorld			(World *world);

	private:
		static const std::string CIRCLE_WORLD_LABEL;
		static const std::string SQUARE_WORLD_LABEL;

		Button			*erase;
		ErasedCallback	erased;
		TargetButton	*gravity;
		Slider			*size;
		ObjectPicker	*objects;
		OptionGrid		*type;
		World			*world;

		World	*cloneWorld				(World::WorldType cloneType);
		void	erase_Clicked			(UIElement *sender);
		void	gravity_TargetChanged	(const Vector2f &targetPosition);
		void	objects_ObjectSelected	(ObjectPicker *sender, PhysicsObject *obj);
		void	size_ValueChanged		(float size);
		void	type_SelectionChanged	(const OptionGrid::Option &selection);
	};
}

