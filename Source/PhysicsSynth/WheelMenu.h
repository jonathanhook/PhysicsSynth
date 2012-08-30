/**
 * Class:	WheelMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Menu.h"

namespace PhysicsSynth
{
	class Wheel;
	class Button;
	class CheckBox;
	class ColourPicker;
	class PatternPicker;
	class Slider;

	class WheelMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<Menu *, PhysicsObject *> ErasedCallback;

		WheelMenu(Wheel *wheel, const Point2i &position, unsigned int width, MenuMode mode);
		~WheelMenu(void);

		Wheel	*createObject		(void) const;
		void	initMenuItems		(void);
		void	setErasedCallback	(ErasedCallback erased);
		void	setObject			(Wheel *Wheel);
		void	setValues			(void);

	private:
		Wheel			*wheel;
		Button			*erase;
		ErasedCallback	erased;
		PatternPicker	*pattern;
		Slider			*rate;
		Slider			*size;
		ColourPicker	*sound;
		Button			*sync;

		void erase_Clicked				(UIElement *sender);
		void pattern_PatternChanged		(unsigned int pattern);
		void rate_ValueChanged			(float value);
		void size_ValueChanged			(float value);
		void sound_SelectionChanged		(SoundConfig *sound);
		void sync_Clicked				(UIElement *sender);
	};
}

