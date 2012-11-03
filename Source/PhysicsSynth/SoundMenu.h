/**
 * Class:	SoundMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Menu.h"

namespace PhysicsSynth
{
	class ColourPicker;
	class ImpulseEventMenu;

	class SoundMenu :
		public Menu
	{
	public:
		SoundMenu(const Point2i &position, unsigned int width);
		~SoundMenu(void);

		void initMenuItems	(void);
		void render			(void);
		void setValues		(void);

	private:
		ImpulseEventMenu	*impulseMenu;
		SoundConfig			*selectedSound;
		ColourPicker		*soundConfig;

		void soundConfig_SelectionChanged(SoundConfig *soundConfig);
	};
}

