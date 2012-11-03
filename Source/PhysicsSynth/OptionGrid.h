/**
 * Class:	OptionGrid
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class OptionGridItem;

	class OptionGrid :
		public LabelledUIElement
	{
	public:
        struct Option
		{
			unsigned int	id;
			std::string		label;

			Option(unsigned int id, std::string label)
			{
				this->id	= id;
				this->label = label;
			}

			Option(void)
			{
				id		= NULL;
				label	= "";
			}
		};

		typedef FastDelegate1<const Option &> SelectionChangedCallback;

		OptionGrid	(std::vector<Option> items, std::string label, const Point2i &position, unsigned int width);
		~OptionGrid	(void);

		const OptionGridItem	&getSelectedItem		(void) const;
		void					render					(void);
		void					setPosition				(const Point2i &position);
		void					setSelectedItem			(OptionGridItem *selectedItem);
		void					setSelectedItem			(unsigned int id);
		void					setSelectionChangedCallback(SelectionChangedCallback selectionChanged);
	
	private:
		static const unsigned int COLUMNS;

		std::vector<OptionGridItem *>	options;
		SelectionChangedCallback		selectionChanged;

		void init					(std::vector<Option> items);
		void optionGridItem_Checked	(OptionGridItem *option);
	
	};
}

