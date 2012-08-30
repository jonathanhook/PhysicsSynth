/**
 * Class:	ImpulseEventMenu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "MappingGrid.h"
#include "Menu.h"

namespace PhysicsSynth
{
	class SoundConfig;

	class ImpulseEventMenu :
		public Menu
	{
	public:
		ImpulseEventMenu(SoundConfig *sound, const Point2i &position, unsigned int width);
		~ImpulseEventMenu(void);

		void initMenuItems	(void);
		void setSound		(SoundConfig *sound);
		void setValues		(void);

	private:
		MappingGrid *mappingGrid;
		SoundConfig	*sound;

		void mappingGrid_MappingChanged(MappingGrid::MappingGridItem from, MappingGrid::MappingGridItem to);
	};
}

