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

		soundConfig = new ColourPicker(Sounds::getSounds(false), "Sounds", position, width);
		soundConfig->setSelectionChangedCallback(MakeDelegate(this, &SoundMenu::soundConfig_SelectionChanged));
		addMenuItem(*soundConfig);

		Point2i pos = position;
		pos.translateY(soundConfig->getDimensions().getY());
		impulseMenu = new ImpulseEventMenu(selectedSound, pos, width);

		// init menu
		soundConfig->setSelectedItem(selectedSound);
	}

	void SoundMenu::render(void)
	{
		Menu::render();

		if(selectedSound->getType() == SoundConfig::IMPULSE)
		{
			assert(impulseMenu);
			impulseMenu->render();
		}
	}

	void SoundMenu::setValues(void)
	{
		assert(selectedSound);
		assert(soundConfig);
		assert(impulseMenu);
		
		impulseMenu->setSound(selectedSound);

		updateTypeState();		
	}

	/* Private Member Functions */
	void SoundMenu::eventType_SelectionChanged(const OptionGrid::Option &option)
	{
		assert(selectedSound);
		selectedSound->setType((SoundConfig::Type)option.id);
		updateTypeState();
	}

	void SoundMenu::soundConfig_SelectionChanged(SoundConfig *selectedSound)
	{
		this->selectedSound = selectedSound;
		setValues();
	}

	void SoundMenu::updateTypeState(void)
	{
		if(selectedSound->getType() == SoundConfig::IMPULSE)
		{
			borderState	= (TOP | LEFT | RIGHT);
			menuDl		= -1;
	
			registerEventHandler(impulseMenu);
		}
		else
		{
			borderState	= (TOP | BOTTOM | LEFT | RIGHT);
			menuDl		= -1;

			registerEventHandler(impulseMenu);
		}
	}
}
