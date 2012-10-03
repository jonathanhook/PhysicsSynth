/**
 * Class:	ObjectPickerItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include "Button.h"

namespace PhysicsSynth
{
	class PhysicsObject;

	class ObjectPickerItem :
		public Button
	{
	public:
		ObjectPickerItem(PhysicsObject *object, const Point2i &position, unsigned int width);
		~ObjectPickerItem(void);

		PhysicsObject	*getObject					(void) const;
		void			render						(void);

	private:
		PhysicsObject			*object;
	};
}
