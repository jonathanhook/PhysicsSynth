/**
 * Class:	SoundMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.ukraw
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
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
		enabledGrid = new OptionGrid(options, "OSC Sending", pos, dimensions.getX());
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
