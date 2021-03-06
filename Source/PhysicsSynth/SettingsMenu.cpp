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
#include <stdlib.h>
#include <JDHUtility/OSCSender.h>
#include "AddressPicker.h"
#include "Button.h"
#include "Manager.h"
#include "OptionGrid.h"
#include "SettingsMenu.h"
#include "Sounds.h"
#include "SoundConfig.h"

namespace PhysicsSynth
{
	/* Constructors */
	SettingsMenu::SettingsMenu(const Point2i &position, unsigned int width) :
		Menu(position, width, TOP | LEFT | RIGHT | BOTTOM, Menu::CREATE)
	{
#ifdef GLUT_WINDOWING
		saved = NULL;
#endif
    
		initMenuItems();
		setValues();
	}

	SettingsMenu::~SettingsMenu(void)
	{
	}

	/* Public Member Functions */
	void SettingsMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();
        
#ifdef GLUT_WINDOWING
		save = new Button("Save", position, width);
		save->setClickedCallback(MakeDelegate(this, &SettingsMenu::save_Clicked));
		addMenuItem(*save);

		quit = new Button("Quit", position, width);
		quit->setClickedCallback(MakeDelegate(this, &SettingsMenu::quit_Clicked));
		addMenuItem(*quit);
#else
        std::vector<OptionGrid::Option> options;
        options.push_back(OptionGrid::Option(PlaybackMode::INTERNAL, "Internal"));
        options.push_back(OptionGrid::Option(PlaybackMode::OSC, "Send OSC"));
        
        playbackMode = new OptionGrid(options, "Sound Playback", position, width);
        playbackMode->setSelectionChangedCallback(MakeDelegate(this, &SettingsMenu::playbackMode_SelectionChanged));
        addMenuItem(*playbackMode);
#endif
        
        addressPicker = new AddressPicker("OSC Address", position, width);
        addMenuItem(*addressPicker);
	}

	void SettingsMenu::render(void)
	{
		Menu::render();
	}

	void SettingsMenu::setValues(void)
	{
#ifdef IOS_WINDOWING
        OSCSender *sender = Manager::getOscSender();
        assert(sender);
        
        bool enabled = sender->getIsEnabled();
        if(!enabled)
        {
            playbackMode->setSelectedItem(INTERNAL);
        }
        else
        {
            playbackMode->setSelectedItem(OSC);
        }
#endif
	}

#ifdef GLUT_WINDOWING 
    void SettingsMenu::setSavedCallback(SavedCallback saved)
	{
		this->saved = saved;
	}
    
	/* Private Member Functions */
	void SettingsMenu::save_Clicked(UIElement *sender)
	{
		if(saved != NULL)
		{
			saved();
		}
	}

	void SettingsMenu::quit_Clicked(UIElement *sender)
	{
		exit(0);
	}
#else
    void SettingsMenu::playbackMode_SelectionChanged(const OptionGrid::Option & option)
    {
        OSCSender *osc = Manager::getOscSender();
        assert(osc);
        
        if(option.id == INTERNAL)
        {
            osc->setIsEnabled(false);
        }
        else
        {
            osc->setIsEnabled(true);
        }
    }
#endif
}
