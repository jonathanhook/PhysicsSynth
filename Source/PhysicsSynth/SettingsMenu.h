/**
 * Class:	SettingsMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Menu.h"

namespace PhysicsSynth
{
	class Button;

	class SettingsMenu :
		public Menu
	{
	public:
		typedef FastDelegate0<> SavedCallback;

		SettingsMenu(const Point2i &position, unsigned int width);
		~SettingsMenu(void);

		void initMenuItems		(void);
		void render				(void);
		void setSavedCallback	(SavedCallback saved);
		void setValues			(void);

	private:
		Button			*save;
		SavedCallback	saved;
		Button			*quit;

		void save_Clicked	(UIElement *sender);
		void quit_Clicked	(UIElement *sender);
	};
}

