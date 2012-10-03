/**
 * Class:	BombMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Menu.h"

namespace PhysicsSynth
{
	class Bomb;
	class Button;
	class CheckBox;
	class ColourPicker;
	class PatternPicker;
	class Slider;

	class BombMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<Menu *, PhysicsObject *> ErasedCallback;

		BombMenu(Bomb *bomb, const Point2i &position, unsigned int width, MenuMode mode);
		~BombMenu(void);

		Bomb	*createObject		(void) const;
		void	initMenuItems		(void);
		void	setErasedCallback	(ErasedCallback erased);
		void	setObject			(Bomb *Bomb);
		void	setValues			(void);

	private:
		Bomb			*bomb;
		Button			*erase;
		ErasedCallback	erased;
		Slider			*intensity;
		PatternPicker	*pattern;
		Slider			*rate;
		Slider			*size;
		ColourPicker	*sound;
		Button			*sync;

		void erase_Clicked				(UIElement *sender);
		void intensity_ValueChanged		(float value);
		void pattern_PatternChanged		(unsigned int pattern);
		void rate_ValueChanged			(float value);
		void size_ValueChanged			(float value);
		void sound_SelectionChanged		(SoundConfig *sound);
		void sync_Clicked				(UIElement *sender);
	};
}

