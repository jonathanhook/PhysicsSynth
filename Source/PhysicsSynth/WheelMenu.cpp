/**
 * Class:	WheelMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/Ndelete.h>
#include "Wheel.h"
#include "WheelMenu.h"
#include "Button.h"
#include "CheckBox.h"
#include "ColourPicker.h"
#include "PatternPicker.h"
#include "Slider.h"

namespace PhysicsSynth
{
	/* Constructors */
	WheelMenu::WheelMenu(Wheel *wheel, const Point2i &position, unsigned int width, MenuMode mode) :
		Menu(position, width, BOTTOM | LEFT | RIGHT, mode)
	{
		this->wheel = wheel;

		erased = NULL;

		initMenuItems();
		setValues();
	}

	WheelMenu::~WheelMenu(void)
	{
		NDELETE(wheel); // TODO: delete or not to delete?
	}

	/* Public Member Functions */
	Wheel *WheelMenu::createObject(void) const
	{
		assert(wheel);

		float			oldRate			= wheel->getRate();
		unsigned int	oldPattern		= wheel->getPattern();
		float			oldSize			= wheel->getSize();
		SoundConfig		*oldSound		= wheel->getSound();

		return new Wheel(oldRate, oldPattern, oldSize, oldSound);
	}

	void WheelMenu::initMenuItems(void)
	{
		unsigned int width = dimensions.getX();

		sound = new ColourPicker(Sounds::getSounds(), "Sound", position, width);
		sound->setSelectionChangedCallback(MakeDelegate(this, &WheelMenu::sound_SelectionChanged));
		addMenuItem(*sound);

		size = new Slider("Size", position, width);
		size->setValueChangedCallback(MakeDelegate(this, &WheelMenu::size_ValueChanged));
		addMenuItem(*size);

		rate = new Slider("Rate", position, width);
		rate->setValueChangedCallback(MakeDelegate(this, &WheelMenu::rate_ValueChanged));
		addMenuItem(*rate);

		pattern = new PatternPicker(8, "Pattern", position, width);
		pattern->setPatternChangedCallback(MakeDelegate(this, &WheelMenu::pattern_PatternChanged));
		addMenuItem(*pattern);

		sync = new Button("Sync", position, width / 2);
		sync->setClickedCallback(MakeDelegate(this, &WheelMenu::sync_Clicked));
		addMenuItem(*sync);

		if(mode == INSPECT)
		{
			erase = new Button("Erase", position, width / 2);
			erase->setClickedCallback(MakeDelegate(this, &WheelMenu::erase_Clicked));
			addMenuItem(*erase);
		}
	}
	
	void WheelMenu::setErasedCallback(ErasedCallback erased)
	{
		this->erased = erased;
	}

	void WheelMenu::setObject(Wheel *wheel)
	{
		this->wheel = wheel;
		setValues();
	}

	void WheelMenu::setValues(void)
	{
		assert(wheel);

		pattern->setPattern(wheel->getPattern());
		rate->setValue(wheel->getRate());
		size->setValue(wheel->getSize());
		sound->setSelectedItem(wheel->getSound());
	}

	/* Private Member Functions */
	void WheelMenu::erase_Clicked(UIElement *sender)
	{
		if(erased != NULL)
		{
			erased(this, wheel);
		}

		assert(wheel);
		wheel->setIsMarkedForDelete(true);
		wheel = NULL;
	}

	void WheelMenu::pattern_PatternChanged(unsigned int pattern)
	{
		assert(wheel);
		wheel->setPattern(pattern);
	}

	void WheelMenu::rate_ValueChanged(float value)
	{
		assert(wheel);
		wheel->setRate(value);
	}

	void WheelMenu::size_ValueChanged(float value)
	{
		assert(wheel);
		wheel->setSize(value);
	}

	void WheelMenu::sound_SelectionChanged(SoundConfig *selection)
	{
		assert(wheel);
		wheel->setSound(selection);
	}

	void WheelMenu::sync_Clicked(UIElement *sender)
	{
		assert(wheel);
		wheel->sync();

		setValues();
	}
}
