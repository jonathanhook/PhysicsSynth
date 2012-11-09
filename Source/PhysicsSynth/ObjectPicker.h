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
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class ObjectPickerItem;
	class PhysicsObject;
	class World;

	class ObjectPicker :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate2<ObjectPicker *, PhysicsObject *> ObjectSelectedCallback;

		ObjectPicker(const Point2i &position, unsigned int width);
		~ObjectPicker(void);

		void render						(void);
		void setObjectSelectedCallback	(ObjectSelectedCallback objectSelected);
		void setWorld					(World *world);

	private:
		static const std::string	LABEL;
		static const unsigned int	NUM_COLS;

		std::vector<ObjectPickerItem *>	items;
		ObjectSelectedCallback			objectSelected;
		World							*world;

		void clear			(void);
		void init			(void);
		void object_Clicked	(UIElement *sender);
	};
}
