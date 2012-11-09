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
#include "ColourPicker.h"
#include "ImpulseEventMenu.h"
#include "OptionGrid.h"
#include "Sounds.h"
#include "SoundConfig.h"
#include "SoundMenu.h"

namespace PhysicsSynth
{
	/* Constructors */
	SoundMenu::SoundMenu(const Point2i &position, unsigned int width) :
		Menu(position, width, (TOP | LEFT | RIGHT))
	{
		selectedSound = &Sounds::SOUND_0;

		initMenuItems();
		setValues();
	}

	SoundMenu::~SoundMenu(void)
	{
		NDELETE(impulseMenu);
	}

	/* Public Member Functions */
	void SoundMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		soundConfig = new ColourPicker(Sounds::getSounds(true), "Sounds", position, width);
		soundConfig->setSelectionChangedCallback(MakeDelegate(this, &SoundMenu::soundConfig_SelectionChanged));
		addMenuItem(*soundConfig);
        
        Point2i pos = position;
		pos.translateY(soundConfig->getDimensions().getY());
        
        std::vector<OptionGrid::Option> options;
		options.push_back(OptionGrid::Option(true, "Enabled"));
		options.push_back(OptionGrid::Option(false, "Disabled"));
		enabledGrid = new OptionGrid(options, "Playback", pos, dimensions.getX());
        enabledGrid->setSelectionChangedCallback(MakeDelegate(this, &SoundMenu::enabledGrid_SelectionChanged));
        addMenuItem(*enabledGrid);

        pos.translateY(enabledGrid->getDimensions().getY());
		impulseMenu = new ImpulseEventMenu(selectedSound, pos, width);
        registerEventHandler(impulseMenu);

		// init menu
		soundConfig->setSelectedItem(selectedSound);
	}

	void SoundMenu::render(void)
	{
		Menu::render();
        
        assert(impulseMenu);
        impulseMenu->render();
	}

	void SoundMenu::setValues(void)
	{
		assert(selectedSound);
		assert(soundConfig);
		assert(impulseMenu);
        assert(enabledGrid);
		
		impulseMenu->setSound(selectedSound);
        enabledGrid->setSelectedItem(selectedSound->getIsEnabled());
	}

	/* Private Member Functions */
    void SoundMenu::enabledGrid_SelectionChanged(const OptionGrid::Option &selected)
    {
        assert(selectedSound);
        selectedSound->setIsEnabled(selected.id);
    }
    
	void SoundMenu::soundConfig_SelectionChanged(SoundConfig *selectedSound)
	{
		this->selectedSound = selectedSound;
		setValues();
	}
}
