/**
 * Class:	MappingGrid
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <map>
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class MappingButton;

	class MappingGrid :
		public LabelledUIElement
	{
	public:
        struct MappingGridItem
		{
			unsigned int	item;
			std::string		label;

			MappingGridItem(unsigned int item, std::string label)
			{
				this->item	= item;
				this->label = label;
			}

			MappingGridItem(void)
			{
				item	= 0;
				label	= "";
			}
		};

		typedef FastDelegate2<MappingGridItem, MappingGridItem> MappingChangedCallback;

		MappingGrid(std::vector<MappingGridItem> froms, std::vector<MappingGridItem> tos, std::string label, const Point2i &position, const Point2i &dimensions);
		~MappingGrid(void);

		void render						(void);
		void setMapping					(unsigned int from, unsigned int to);
		void setMappingChangedCallback	(MappingChangedCallback mappingChanged);

	private:
		std::vector<MappingGridItem>	froms;
		std::vector<MappingButton *>	mappingButtons;
		MappingChangedCallback			mappingChanged;
		std::vector<MappingGridItem>	tos;

		void init							(void);
		void mappingButton_MappingChanged	(MappingGridItem from, MappingGridItem to);
	};
}

