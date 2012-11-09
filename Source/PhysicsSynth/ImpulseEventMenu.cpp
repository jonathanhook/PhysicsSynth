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
#include "ImpulseEventMenu.h"
#include "MappingGrid.h"
#include "OptionGrid.h"
#include "SoundConfig.h"

namespace PhysicsSynth
{
	/* Constructors */
	ImpulseEventMenu::ImpulseEventMenu(SoundConfig *sound, const Point2i &position, unsigned int width) :
		Menu(position, width, (LEFT | BOTTOM | RIGHT))
	{
		this->sound = sound;

		initMenuItems();
		setValues();
	}

	ImpulseEventMenu::~ImpulseEventMenu(void)
	{
	}

	/* Public Member Functions */
	void ImpulseEventMenu::initMenuItems(void)
	{
		std::vector<MappingGrid::MappingGridItem> tos;
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::POS_X, "Pos X"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::POS_Y, "Pos Y"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::ANGLE, "Angle"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::VELOCITY, "Velocity"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::SPIN, "Spin"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::INERTIA, "Inertia"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::CONTACT_IMPULSE, "Hit force"));

		std::vector<MappingGrid::MappingGridItem> froms;
		froms.push_back(MappingGrid::MappingGridItem(0, "Param 0"));
		froms.push_back(MappingGrid::MappingGridItem(1, "Param 1"));
		froms.push_back(MappingGrid::MappingGridItem(2, "Param 2"));
		froms.push_back(MappingGrid::MappingGridItem(3, "Param 3"));
		froms.push_back(MappingGrid::MappingGridItem(4, "Param 4"));
		froms.push_back(MappingGrid::MappingGridItem(5, "Param 5"));
		froms.push_back(MappingGrid::MappingGridItem(6, "Param 6"));
    
		mappingGrid = new MappingGrid(froms, tos, "Mappings", position, dimensions);
		mappingGrid->setMappingChangedCallback(MakeDelegate(this, &ImpulseEventMenu::mappingGrid_MappingChanged));
		addMenuItem(*mappingGrid);
	}

	void ImpulseEventMenu::setSound(SoundConfig *sound)
	{
		this->sound = sound;
		setValues();
	}

	void ImpulseEventMenu::setValues(void)
	{
		assert(sound);
		assert(mappingGrid);

		std::map<unsigned int, SoundConfig::PhysicalProperty> impulseMappings = sound->getImpulseMappings();
		
		std::map<unsigned int, SoundConfig::PhysicalProperty>::iterator it;
		for(it = impulseMappings.begin(); it != impulseMappings.end(); it++)
		{
			mappingGrid->setMapping((*it).first, (*it).second);
		}
	}

	/* Private Member Functions */
	void ImpulseEventMenu::mappingGrid_MappingChanged(MappingGrid::MappingGridItem from, MappingGrid::MappingGridItem to)
	{
		assert(sound);
		sound->updateMapping((unsigned int)from.item, (SoundConfig::PhysicalProperty)to.item);
	}
}