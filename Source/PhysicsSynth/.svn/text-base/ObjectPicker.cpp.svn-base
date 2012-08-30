/**
 * Class:	ObjectPicker
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/OpenGL.h>
#include "Button.h"
#include "ObjectPicker.h"
#include "ObjectPickerItem.h"
#include "PhysicsObject.h"
#include "World.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const std::string	ObjectPicker::LABEL		= "Physics Objects";
	const unsigned int	ObjectPicker::NUM_COLS	= 2;

	/* Constructors */
	ObjectPicker::ObjectPicker(const Point2i &position, unsigned int width) :
		LabelledUIElement(LABEL, position, width)
	{
		objectSelected	= NULL;
		world			= NULL;

		dimensions.setY(0);
	}

	ObjectPicker::~ObjectPicker(void)
	{
	}

	/* Public Member Functions */
	void ObjectPicker::render(void)
	{
		unsigned int count = items.size();
		if(count > 0)
		{
			LabelledUIElement::render();

			for(unsigned int i = 0; i < items.size(); i++)
			{
				ObjectPickerItem *opi = items[i];
				assert(opi);

				opi->render();
			}
		}
	}

	void ObjectPicker::setObjectSelectedCallback(ObjectSelectedCallback objectSelected)
	{
		this->objectSelected = objectSelected;
	}

	void ObjectPicker::setWorld(World *world)
	{
		this->world = world;
		init();
	}

	/* Private Member Functions */
	void ObjectPicker::clear(void)
	{
		for(unsigned int i = 0; i < items.size(); i++)
		{
			ObjectPickerItem *o = items[i];
			assert(o);

			unregisterEventHandler(o);
			NDELETE(o);
		}
		items.clear();
	}

	void ObjectPicker::init(void)
	{
		clear();
		
		assert(world);
		std::vector<PhysicsObject *> objects	= world->getObjects();
		unsigned int count						= objects.size();

		if(count > 0)
		{
			unsigned int labelHeight	= getLabelHeight();
			unsigned int height			= labelHeight * 2;
			unsigned int width			= dimensions.getX() / NUM_COLS;

			for(unsigned int i = 0; i < count; i++)
			{
				PhysicsObject *o = objects[i];
				assert(o);

				unsigned int row = i / NUM_COLS;
				unsigned int col = i % NUM_COLS;
				unsigned int x = position.getX() + (col * width);
				unsigned int y = position.getY() + (row * height) + labelHeight;
			
				ObjectPickerItem *opi = new ObjectPickerItem(o, Point2i(x, y), width);
				opi->setClickedCallback(MakeDelegate(this, &ObjectPicker::object_Clicked));

				items.push_back(opi);
				registerEventHandler(opi);
			}

			unsigned int rows = ((count - 1) / NUM_COLS) + 1;
			dimensions.setY(labelHeight + (rows * height));
		}
		else
		{
			dimensions.setY(0);
		}
	}

	void ObjectPicker::object_Clicked(UIElement *sender)
	{
		if(objectSelected != NULL)
		{
			ObjectPickerItem *opi = (ObjectPickerItem *)sender;
			assert(opi);

			PhysicsObject *p = opi->getObject();
			assert(p);

			objectSelected(this, p);
		}
	}
}