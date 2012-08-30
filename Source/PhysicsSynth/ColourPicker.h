/**
 * Class:	ColourPicker
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Colour3f.h>
#include "FastDelegate.h"
#include "LabelledUIElement.h"

using namespace fastdelegate;
using namespace JDHUtility;

namespace PhysicsSynth
{
	class ColourPickerItem;
	class SoundConfig;

	class ColourPicker : 
		public LabelledUIElement
	{
	public:
		typedef FastDelegate1<SoundConfig *> SelectionChangedCallback;

		ColourPicker(std::vector<SoundConfig *> items, std::string label, const Point2i &position, unsigned int width);
		~ColourPicker(void);

		void render						(void);
		void setPosition				(const Point2i &position);
		void setSelectedItem			(ColourPickerItem *item);
		void setSelectedItem			(SoundConfig *item);
		void setSelectionChangedCallback(SelectionChangedCallback selectionChanged);

	private:
		static const unsigned int	COLUMNS;
		static const unsigned int	PICKER_HEIGHT;

		std::vector<ColourPickerItem *> colours;
		SelectionChangedCallback		selectionChanged;

		void colourPickerItem_Checked	(ColourPickerItem *item);
		void init						(std::vector<SoundConfig *> items);
	};
}

