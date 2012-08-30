/**
 * Class:	ColourPickerItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "UIElement.h"

namespace PhysicsSynth
{
	class SoundConfig;

	class ColourPickerItem :
		public UIElement
	{
	public:
		typedef FastDelegate1<ColourPickerItem *> CheckedCallback;

		ColourPickerItem(SoundConfig *colour, const Point2i &position, const Point2i &dimensions);
		~ColourPickerItem(void);

		void		fingerAdded			(const FingerEventArgs &e);
		SoundConfig	*getColour			(void) const;
		bool		isChecked			(void) const;
		void		render				(void);
		void		setChecked			(bool checked);
		void		setCheckedCallback	(CheckedCallback checkedCallback);

	private:
		static const float			COLOUR_ITEM_OPACITY;
		static const unsigned int	RIM;
	
		bool				checked;
		CheckedCallback		checkedCallback;
		unsigned int		checkedDl;
		SoundConfig			*colour;
		unsigned int		colourDl;
		unsigned int		colourSelectedDl;
	};
}

