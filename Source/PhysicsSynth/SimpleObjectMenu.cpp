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
#include <assert.h>
#include <JDHUtility/Ndelete.h>
#include "Button.h"
#include "CheckBox.h"
#include "Circle.h"
#include "ColourPicker.h"
#include "SimpleObject.h"
#include "SimpleObjectMenu.h"
#include "Slider.h"
#include "Stick.h"
#include "Square.h"
#include "Triangle.h"

namespace PhysicsSynth
{
	/* Constructors */
	SimpleObjectMenu::SimpleObjectMenu(SimpleObject *object, const Point2i &position, unsigned int width, MenuMode mode) :
		Menu(position, width, LEFT | RIGHT | BOTTOM, mode)
	{
		this->object = object;

		erased = NULL;

		initMenuItems();
		setValues();
	}

	SimpleObjectMenu::~SimpleObjectMenu(void)
	{
		NDELETE(object);	// HACK: should or shouldn't be here!
	}

	/* Public Member Functions */
	SimpleObject *SimpleObjectMenu::createObject(void) const
	{
		assert(object);

		bool		oldIsStatic		= object->getIsLocked();
		float		oldSize			= object->getSize();
		SoundConfig	*oldSound		= object->getSound();
		float		oldFriction		= object->getFriction();
		float		oldRestitution	= object->getRestitution();

		SimpleObject *newObj = NULL;
		switch(object->getObjectType())
		{
			case PhysicsObject::CIRCLE:
				newObj = new Circle(oldIsStatic, oldSize, oldSound, oldFriction, oldRestitution); 
				break;
			case PhysicsObject::SQUARE:
				newObj = new Square(oldIsStatic, oldSize, oldSound, oldFriction, oldRestitution); 
				break;
			case PhysicsObject::TRIANGLE:
				newObj = new Triangle(oldIsStatic, oldSize, oldSound, oldFriction, oldRestitution); 
				break;
			case PhysicsObject::STICK:
				newObj = new Stick(oldIsStatic, oldSize, oldSound, oldFriction, oldRestitution); 
				break;
		}

		assert(newObj);
		return newObj;
	}

	void SimpleObjectMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		sound = new ColourPicker(Sounds::getSounds(), "Sound", position, width);
		sound->setSelectionChangedCallback(MakeDelegate(this, &SimpleObjectMenu::sound_SelectionChanged));
		addMenuItem(*sound);

		friction = new Slider("Friction", position, width);
		friction->setValueChangedCallback(MakeDelegate(this, &SimpleObjectMenu::friction_ValueChanged));
		addMenuItem(*friction);

		restitution = new Slider("Bouncyness", position, width);
		restitution->setValueChangedCallback(MakeDelegate(this, &SimpleObjectMenu::restitution_ValueChanged));
		addMenuItem(*restitution);

		size = new Slider("Size", position, width);
		size->setValueChangedCallback(MakeDelegate(this, &SimpleObjectMenu::size_ValueChanged));
		addMenuItem(*size);

		isLocked = new CheckBox("Locked", position, width);
		isLocked->setCheckedChangedCallback(MakeDelegate(this, &SimpleObjectMenu::isLocked_CheckedChanged));
		addMenuItem(*isLocked);

		if(mode == INSPECT)
		{
			erase = new Button("Erase", position, width);
			erase->setClickedCallback(MakeDelegate(this, &SimpleObjectMenu::erase_Clicked));
			addMenuItem(*erase);
		}
	}

	void SimpleObjectMenu::setObject(SimpleObject *object)
	{
		this->object = object;
		setValues();
	}

	void SimpleObjectMenu::setErasedCallback(ErasedCallback erased)
	{
		this->erased = erased;
	}

	void SimpleObjectMenu::setValues(void)
	{
		assert(object);

		friction->setValue(object->getFriction());
		isLocked->setIsChecked(object->getIsLocked());
		restitution->setValue(object->getRestitution());
		size->setValue(object->getSize());
		sound->setSelectedItem(object->getSound());
	}

	/* Private Member Functions */
	void SimpleObjectMenu::erase_Clicked(UIElement *sender)
	{
		if(erased != NULL)
		{
			erased(this, object);
		}
		
		assert(object);
		object->setIsMarkedForDelete(true);
		object = NULL;
	}

	void SimpleObjectMenu::friction_ValueChanged(float value)
	{
		assert(object);
		object->setFriction(value);
	}

	void SimpleObjectMenu::isLocked_CheckedChanged(bool checked)
	{
		assert(object);
		object->setIsLocked(checked);
	}

	void SimpleObjectMenu::restitution_ValueChanged(float value)
	{
		assert(object);
		object->setRestitution(value);
	}

	void SimpleObjectMenu::size_ValueChanged(float value)
	{
		assert(object);
		object->setSize(value);
	}

	void SimpleObjectMenu::sound_SelectionChanged(SoundConfig *selection)
	{
		assert(object);
		object->setSound(selection);
	}
}
