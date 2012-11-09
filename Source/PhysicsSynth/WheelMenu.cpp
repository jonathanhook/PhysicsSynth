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
#include "Wheel.h"
#include "WheelMenu.h"
#include "Button.h"
#include "CheckBox.h"
#include "ColourPicker.h"
#include "PatternPicker.h"
#include "Slider.h"

namespace PhysicsSynth
{
	/* Constructors */
	WheelMenu::WheelMenu(Wheel *wheel, const Point2i &position, unsigned int width, MenuMode mode) :
		Menu(position, width, BOTTOM | LEFT | RIGHT, mode)
	{
		this->wheel = wheel;

		erased = NULL;

		initMenuItems();
		setValues();
	}

	WheelMenu::~WheelMenu(void)
	{
		NDELETE(wheel); // TODO: delete or not to delete?
	}

	/* Public Member Functions */
	Wheel *WheelMenu::createObject(void) const
	{
		assert(wheel);

		float			oldRate			= wheel->getRate();
		unsigned int	oldPattern		= wheel->getPattern();
		float			oldSize			= wheel->getSize();
		SoundConfig		*oldSound		= wheel->getSound();

		return new Wheel(oldRate, oldPattern, oldSize, oldSound);
	}

	void WheelMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		sound = new ColourPicker(Sounds::getSounds(), "Sound", position, width);
		sound->setSelectionChangedCallback(MakeDelegate(this, &WheelMenu::sound_SelectionChanged));
		addMenuItem(*sound);

		size = new Slider("Size", position, width);
		size->setValueChangedCallback(MakeDelegate(this, &WheelMenu::size_ValueChanged));
		addMenuItem(*size);

		rate = new Slider("Rate", position, width);
		rate->setValueChangedCallback(MakeDelegate(this, &WheelMenu::rate_ValueChanged));
		addMenuItem(*rate);

		pattern = new PatternPicker(8, "Pattern", position, width);
		pattern->setPatternChangedCallback(MakeDelegate(this, &WheelMenu::pattern_PatternChanged));
		addMenuItem(*pattern);

		sync = new Button("Sync", position, width);
		sync->setClickedCallback(MakeDelegate(this, &WheelMenu::sync_Clicked));
		addMenuItem(*sync);

		if(mode == INSPECT)
		{
			erase = new Button("Erase", position, width);
			erase->setClickedCallback(MakeDelegate(this, &WheelMenu::erase_Clicked));
			addMenuItem(*erase);
		}
	}
	
	void WheelMenu::setErasedCallback(ErasedCallback erased)
	{
		this->erased = erased;
	}

	void WheelMenu::setObject(Wheel *wheel)
	{
		this->wheel = wheel;
		setValues();
	}

	void WheelMenu::setValues(void)
	{
		assert(wheel);

		pattern->setPattern(wheel->getPattern());
		rate->setValue(wheel->getRate());
		size->setValue(wheel->getSize());
		sound->setSelectedItem(wheel->getSound());
	}

	/* Private Member Functions */
	void WheelMenu::erase_Clicked(UIElement *sender)
	{
		if(erased != NULL)
		{
			erased(this, wheel);
		}

		assert(wheel);
		wheel->setIsMarkedForDelete(true);
		wheel = NULL;
	}

	void WheelMenu::pattern_PatternChanged(unsigned int pattern)
	{
		assert(wheel);
		wheel->setPattern(pattern);
	}

	void WheelMenu::rate_ValueChanged(float value)
	{
		assert(wheel);
		wheel->setRate(value);
	}

	void WheelMenu::size_ValueChanged(float value)
	{
		assert(wheel);
		wheel->setSize(value);
	}

	void WheelMenu::sound_SelectionChanged(SoundConfig *selection)
	{
		assert(wheel);
		wheel->setSound(selection);
	}

	void WheelMenu::sync_Clicked(UIElement *sender)
	{
		assert(wheel);
		wheel->sync();

		setValues();
	}
}
