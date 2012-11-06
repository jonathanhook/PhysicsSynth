/**
 * Class:	SettingsMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/OpenGL.h>
#include "Menu.h"

namespace PhysicsSynth
{
    class AddressPicker;
	class Button;
    class OptionGrid;

	class SettingsMenu :
		public Menu
	{
	public:
		typedef FastDelegate0<> SavedCallback;

		SettingsMenu(const Point2i &position, unsigned int width);
		~SettingsMenu(void);

		void initMenuItems		(void);
		void render				(void);
		void setValues			(void);

#ifdef GLUT_WINDOWING
        void setSavedCallback	(SavedCallback saved);
#else
        enum PlaybackMode { INTERNAL, OSC };
#endif

	private:
        AddressPicker *addressPicker;
        
#ifdef GLUT_WINDOWING
        Button			*save;
		SavedCallback	saved;
		Button			*quit;

		void save_Clicked	(UIElement *sender);
		void quit_Clicked	(UIElement *sender);
#else
        OptionGrid *playbackMode;
        
        void playbackMode_SelectionChanged(const OptionGrid::Option & option);
#endif
	};
}

