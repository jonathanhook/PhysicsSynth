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
#include "Menu.h"
#include "OptionGrid.h"
#include "PhysicsObject.h"

namespace PhysicsSynth
{
	class BombMenu;
	class ParticleEmitterMenu;
	class SimpleObjectMenu;
	class WheelMenu;

	class ObjectMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<ObjectMenu *, PhysicsObject *> ErasedCallback;

		ObjectMenu(const Point2i &position, unsigned int width, MenuMode mode);
		~ObjectMenu(void);

		PhysicsObject	*createObject				(void) const;
		void			initMenuItems				(void);
		void			render						(void);
		void			setErasedCallback			(ErasedCallback erased);
		void			setObject					(PhysicsObject *object);
		void			setValues					(void);

	private:
		static const PhysicsObject::PhysicsObjectType DEFAULT_STATE;

		BombMenu							*bombMenu;
		SimpleObjectMenu					*circleMenu;
		ErasedCallback						erased;
		ParticleEmitterMenu					*particleEmitterMenu;
		SimpleObjectMenu					*squareMenu;
		PhysicsObject::PhysicsObjectType	state;
		SimpleObjectMenu					*triangleMenu;
		OptionGrid							*type;
		WheelMenu							*wheelMenu;
		
		void object_Erased			(Menu *sender, PhysicsObject *obj);
		void type_SelectionChanged	(const OptionGrid::Option &option);
		void updateState			(void);
	};
}
