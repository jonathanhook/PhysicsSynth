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
#include "Bomb.h"
#include "BombMenu.h"
#include "Button.h"
#include "CheckBox.h"
#include "ColourPicker.h"
#include "PatternPicker.h"
#include "Slider.h"

namespace PhysicsSynth
{
	/* Constructors */
	BombMenu::BombMenu(Bomb *bomb, const Point2i &position, unsigned int width, MenuMode mode) :
		Menu(position, width, BOTTOM | LEFT | RIGHT, mode)
	{
		this->bomb = bomb;

		erased = NULL;

		initMenuItems();
		setValues();
	}

	BombMenu::~BombMenu(void)
	{
		NDELETE(bomb); // TODO: delete or not to delete?
	}

	/* Public Member Functions */
	Bomb *BombMenu::createObject(void) const
	{
		assert(bomb);

		float			oldIntensity	= bomb->getIntensity();
		float			oldRate			= bomb->getRate();
		unsigned int	oldPattern		= bomb->getPattern();
		float			oldSize			= bomb->getSize();
		SoundConfig		*oldSound		= bomb->getSound();

		return new Bomb(oldIntensity, oldRate, oldPattern, oldSize, oldSound);
	}

	void BombMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		sound = new ColourPicker(Sounds::getSounds(), "Sound", position, width);
		sound->setSelectionChangedCallback(MakeDelegate(this, &BombMenu::sound_SelectionChanged));
		addMenuItem(*sound);

		size = new Slider("Size", position, width);
		size->setValueChangedCallback(MakeDelegate(this, &BombMenu::size_ValueChanged));
		addMenuItem(*size);

		rate = new Slider("Rate", position, width);
		rate->setValueChangedCallback(MakeDelegate(this, &BombMenu::rate_ValueChanged));
		addMenuItem(*rate);

		intensity = new Slider("Intensity", position, width);
		intensity->setValueChangedCallback(MakeDelegate(this, &BombMenu::intensity_ValueChanged));
		addMenuItem(*intensity);

		pattern = new PatternPicker(8, "Pattern", position, width);
		pattern->setPatternChangedCallback(MakeDelegate(this, &BombMenu::pattern_PatternChanged));
		addMenuItem(*pattern);

		sync = new Button("Sync", position, width);
		sync->setClickedCallback(MakeDelegate(this, &BombMenu::sync_Clicked));
		addMenuItem(*sync);

		if(mode == INSPECT)
		{
			erase = new Button("Erase", position, width);
			erase->setClickedCallback(MakeDelegate(this, &BombMenu::erase_Clicked));
			addMenuItem(*erase);
		}
	}
	
	void BombMenu::setErasedCallback(ErasedCallback erased)
	{
		this->erased = erased;
	}

	void BombMenu::setObject(Bomb *bomb)
	{
		this->bomb = bomb;
		setValues();
	}

	void BombMenu::setValues(void)
	{
		assert(bomb);

		pattern->setPattern(bomb->getPattern());
		rate->setValue(bomb->getRate());
		size->setValue(bomb->getSize());
		sound->setSelectedItem(bomb->getSound());
		intensity->setValue(bomb->getIntensity());
	}

	/* Private Member Functions */
	void BombMenu::erase_Clicked(UIElement *sender)
	{
		if(erased != NULL)
		{
			erased(this, bomb);
		}

		assert(bomb);
		bomb->setIsMarkedForDelete(true);
		bomb = NULL;
	}

	void BombMenu::intensity_ValueChanged(float value)
	{
		assert(bomb);
		bomb->setIntensity(value);
	}

	void BombMenu::pattern_PatternChanged(unsigned int pattern)
	{
		assert(bomb);
		bomb->setPattern(pattern);
	}

	void BombMenu::rate_ValueChanged(float value)
	{
		assert(bomb);
		bomb->setRate(value);
	}

	void BombMenu::size_ValueChanged(float value)
	{
		assert(bomb);
		bomb->setSize(value);
	}

	void BombMenu::sound_SelectionChanged(SoundConfig *selection)
	{
		assert(bomb);
		bomb->setSound(selection);
	}

	void BombMenu::sync_Clicked(UIElement *sender)
	{
		assert(bomb);
		bomb->sync();

		setValues();
	}
}
