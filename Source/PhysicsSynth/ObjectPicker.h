/**
 * Class:	ObjectPicker
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/Vector2f.h>
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	class ObjectPickerItem;
	class PhysicsObject;
	class World;

	class ObjectPicker :
		public LabelledUIElement
	{
	public:
		typedef FastDelegate2<ObjectPicker *, PhysicsObject *> ObjectSelectedCallback;

		ObjectPicker(const Point2i &position, unsigned int width);
		~ObjectPicker(void);

		void render						(void);
		void setObjectSelectedCallback	(ObjectSelectedCallback objectSelected);
		void setWorld					(World *world);

	private:
		static const std::string	LABEL;
		static const unsigned int	NUM_COLS;

		std::vector<ObjectPickerItem *>	items;
		ObjectSelectedCallback			objectSelected;
		World							*world;

		void clear			(void);
		void init			(void);
		void object_Clicked	(UIElement *sender);
	};
}
