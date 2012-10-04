/**
 * Class:	ObjectPickerItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/GLPrimitives.h>
#include "ObjectPickerItem.h"
#include "PhysicsObject.h"

namespace PhysicsSynth
{
	/* Constructors */
	ObjectPickerItem::ObjectPickerItem(PhysicsObject *object, const Point2i &position, unsigned int width) :
		Button("", position, width)
	{
		this->object = object;
	}

	ObjectPickerItem::~ObjectPickerItem(void)
	{
	}
	
	/* Public Member Functions */
	PhysicsObject *ObjectPickerItem::getObject(void) const
	{
		return object;
	}

	void ObjectPickerItem::render(void)
	{
		float px			= getSizef(position.getX());
		float py			= getSizef(position.getY());
		float buttonHeight	= getSizef(dimensions.getY());
		float border		= getSizef(BORDER);
		float width			= getSizef(dimensions.getX());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(width - border, buttonHeight - border, 1.0f);

		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		// selected region
		if(selected)
		{
			LIGHT_COLOUR.use();
		}
		else
		{
			DARK_COLOUR.use();
		}
        
        GLPrimitives::getInstance()->renderSquare();

		glTranslatef(0.5f, 0.5f, 0.0f);	
		glScalef(1.0f / (width - border), 1.0f, 1.0f);
		glScalef(buttonHeight - border, 1.0f, 1.0f);

		assert(object);
		object->renderThumbnail();

		glPopMatrix();
	}
}
