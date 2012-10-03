/**
 * Class:	ImpulseEventMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include "ImpulseEventMenu.h"
#include "MappingGrid.h"
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
		unsigned int width = dimensions.getX();

		std::vector<MappingGrid::MappingGridItem> tos;
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::POS_X, "Pos X"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::POS_Y, "Pos Y"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::ANGLE, "Angle"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::VELOCITY, "Velocity"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::SPIN, "Spin"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::INERTIA, "Inertia"));
		tos.push_back(MappingGrid::MappingGridItem(SoundConfig::CONTACT_IMPULSE, "Hit force"));

		std::vector<MappingGrid::MappingGridItem> froms;
		froms.push_back(MappingGrid::MappingGridItem(SoundConfig::TRANSPOSE, "Param 0"));
		froms.push_back(MappingGrid::MappingGridItem(SoundConfig::STRETCH, "Param 1"));
		froms.push_back(MappingGrid::MappingGridItem(SoundConfig::DRIVE, "Param 2"));
		froms.push_back(MappingGrid::MappingGridItem(SoundConfig::FREQUENCY, "Param 3"));
		froms.push_back(MappingGrid::MappingGridItem(SoundConfig::RESONANCE, "Param 4"));
		froms.push_back(MappingGrid::MappingGridItem(SoundConfig::DECAY, "Param 5"));
		froms.push_back(MappingGrid::MappingGridItem(SoundConfig::PAN, "Param 6"));

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

		std::map<SoundConfig::ImpulseProperty, SoundConfig::PhysicalProperty> impulseMappings = sound->getImpulseMappings();
		
		std::map<SoundConfig::ImpulseProperty, SoundConfig::PhysicalProperty>::iterator it;
		for(it = impulseMappings.begin(); it != impulseMappings.end(); it++)
		{
			mappingGrid->setMapping((*it).first, (*it).second);
		}
	}

	/* Private Member Functions */
	void ImpulseEventMenu::mappingGrid_MappingChanged(MappingGrid::MappingGridItem from, MappingGrid::MappingGridItem to)
	{
		assert(sound);
		sound->updateImpulseMapping((SoundConfig::ImpulseProperty)from.item, (SoundConfig::PhysicalProperty)to.item);
	}
}