/**
 * Class:	Menu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/Ndelete.h>
#include "MainMenu.h"
#include "OptionGrid.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const std::string MainMenu::OBJECTS_LABEL	= "Objects";
	const std::string MainMenu::SETTINGS_LABEL	= "Settings";
	const std::string MainMenu::SOUNDS_LABEL	= "Sounds";
	const std::string MainMenu::WORLDS_LABEL	= "Worlds";

	/* Constructors */
	MainMenu::MainMenu(const Point2i &position, unsigned int width) :
		Menu(position, width)
	{
		objectsSelected		= NULL;
		settingsSelected	= NULL;
		soundsSelected		= NULL;
		worldsSelected		= NULL;

		initMenuItems();
		setValues();
	}

	MainMenu::~MainMenu(void)
	{
	}

	/* Public Member Functions */
	void MainMenu::initMenuItems(void)
	{
		unsigned int width	= dimensions.getX();

		// main option grid
		std::vector<OptionGrid::Option> options;
		options.push_back(OptionGrid::Option(WORLDS, WORLDS_LABEL));
		options.push_back(OptionGrid::Option(SOUNDS, SOUNDS_LABEL));
		options.push_back(OptionGrid::Option(OBJECTS, OBJECTS_LABEL));
		options.push_back(OptionGrid::Option(SETTINGS, SETTINGS_LABEL));

		grid = new OptionGrid(options, "Physics Synth v 1.0", position, width);
		grid->setSelectionChangedCallback(MakeDelegate(this, &MainMenu::optionGrid_SelectionChanged));
		addMenuItem(*grid);
	}

	void MainMenu::setChecked(MenuState checked)
	{
		grid->setSelectedItem(checked);
	}

	void MainMenu::setObjectsSelectedCallback(ObjectsSelectedCallback objectsSelected)
	{
		this->objectsSelected = objectsSelected;
	}

	void MainMenu::setSettingsSelectedCallback(SettingsSelectedCallback settingsSelected)
	{
		this->settingsSelected = settingsSelected;
	}

	void MainMenu::setSoundsSelectedCallback(SoundsSelectedCallback soundsSelected)
	{
		this->soundsSelected = soundsSelected;
	}

	void MainMenu::setWorldsSelectedCallback(WorldsSelectedCallback worldsSelected)
	{
		this->worldsSelected = worldsSelected;
	}

	/* Private Member Functions */
	void MainMenu::optionGrid_SelectionChanged(const OptionGrid::Option &selection)
	{
		if(selection.id == OBJECTS && objectsSelected != NULL)
		{
			objectsSelected();
		}
		else if(selection.id == WORLDS && worldsSelected != NULL)
		{
			worldsSelected();
		}
		else if(selection.id == SETTINGS && settingsSelected != NULL)
		{
			settingsSelected();
		}
		else if(selection.id == SOUNDS && soundsSelected != NULL)
		{
			soundsSelected();
		}
	}

	void MainMenu::setValues(void)
	{
		assert(grid != NULL);

		grid->setSelectedItem(WORLDS);
	}
}
