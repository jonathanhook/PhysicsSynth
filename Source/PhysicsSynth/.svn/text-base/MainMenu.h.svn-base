/**
 * Class:	Menu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "FastDelegate.h"
#include "Menu.h"
#include "OptionGrid.h"

using namespace fastdelegate;

namespace PhysicsSynth
{
	class OptionGrid;

	class MainMenu :
		public Menu
	{
	public:
		typedef enum MenuState { WORLDS, OBJECTS, SETTINGS, SOUNDS };
		
		typedef FastDelegate0<>	ObjectsSelectedCallback;
		typedef FastDelegate0<>	SettingsSelectedCallback;
		typedef FastDelegate0<>	SoundsSelectedCallback;
		typedef FastDelegate0<> WorldsSelectedCallback;

		static const std::string OBJECTS_LABEL;
		static const std::string SETTINGS_LABEL;		
		static const std::string SOUNDS_LABEL;
		static const std::string WORLDS_LABEL;

		MainMenu(const Point2i &position, unsigned int width);
		~MainMenu(void);

		void initMenuItems					(void);
		void setChecked						(MenuState checked);
		void setObjectsSelectedCallback		(ObjectsSelectedCallback objectsSelected);
		void setSettingsSelectedCallback	(SettingsSelectedCallback settingsSelected);
		void setSoundsSelectedCallback		(SoundsSelectedCallback soundsSelected);
		void setWorldsSelectedCallback		(WorldsSelectedCallback worldSelected);
		void setValues						(void);

	private:
		OptionGrid					*grid;
		ObjectsSelectedCallback		objectsSelected;
		SettingsSelectedCallback	settingsSelected;
		SoundsSelectedCallback		soundsSelected;
		WorldsSelectedCallback		worldsSelected;

		void optionGrid_SelectionChanged(const OptionGrid::Option &selection);
		void resetToDefaults			(void);
	};
}

