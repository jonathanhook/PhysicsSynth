/**
 * Class:	SimpleObjectMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Menu.h"

namespace PhysicsSynth
{
	class Button;
	class CheckBox;
	class ColourPicker;
	class SimpleObject;
	class Slider;

	class SimpleObjectMenu :
		public Menu
	{
	public:
		typedef FastDelegate2<Menu *, PhysicsObject *> ErasedCallback;

		SimpleObjectMenu(SimpleObject *object, const Point2i &position, unsigned int width, MenuMode mode);
		~SimpleObjectMenu(void);

		SimpleObject	*createObject		(void) const;
		void			initMenuItems		(void);
		void			setObject			(SimpleObject *object);
		void			setErasedCallback	(ErasedCallback erased);
		void			setValues			(void);

	private:
		Button			*erase;
		ErasedCallback	erased;
		Slider			*friction;
		CheckBox		*isLocked;
		SimpleObject	*object;
		Slider			*restitution;
		Slider			*size;
		ColourPicker	*sound;

		void density_ValueChanged		(float value);
		void erase_Clicked				(UIElement *sender);
		void friction_ValueChanged		(float value);
		void isLocked_CheckedChanged	(bool checked);
		void restitution_ValueChanged	(float value);
		void size_ValueChanged			(float value);
		void sound_SelectionChanged		(SoundConfig *sound);
		
	};
}

