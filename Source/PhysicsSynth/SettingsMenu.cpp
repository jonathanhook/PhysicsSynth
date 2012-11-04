/**
 * Class:	SettingsMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <stdlib.h>
#include "Button.h"
#include "Manager.h"
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
#endif
	}

	void SettingsMenu::render(void)
	{
		Menu::render();
	}

	void SettingsMenu::setValues(void)
	{

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
#endif
}
