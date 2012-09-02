/**
 * Class:	MappingButton
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Vector2f.h>
#include "MappingGrid.h"
#include "UIElement.h"

namespace PhysicsSynth
{
	class PushButton;

	class MappingButton :
		public UIElement
	{
	public:
		typedef FastDelegate2<MappingGrid::MappingGridItem, MappingGrid::MappingGridItem> MappingChangedCallback;

		MappingButton(MappingGrid::MappingGridItem from, std::vector<MappingGrid::MappingGridItem> options, const Point2i &position, const Point2i &dimensions);
		~MappingButton(void);
		
		MappingGrid::MappingGridItem	getFrom						(void) const;
		MappingGrid::MappingGridItem	getTo						(void) const;
		void							render						(void);
		void							setMappingChangedCallback	(MappingChangedCallback mappingChanged);
		void							setTo						(MappingGrid::MappingGridItem to);

	private:
		static const std::string LEFT_TEXTURE_PATH;
		static const std::string RIGHT_TEXTURE_PATH;

		MappingGrid::MappingGridItem				from;
		PushButton									*leftButton;
		MappingChangedCallback						mappingChanged;
		std::vector<MappingGrid::MappingGridItem>	options;
		PushButton									*rightButton;
		MappingGrid::MappingGridItem				to;
		unsigned int								toId;

		void initButtons		(void);
		void leftButton_Clicked	(UIElement *sender);
		void rightButton_Clicked(UIElement *sender);

	};
}

