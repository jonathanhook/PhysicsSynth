/**
 * Class:	ObjectPickerItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include "ObjectPickerItem.h"
#include "PhysicsObject.h"

namespace PhysicsSynth
{
	/* Constructors */
	ObjectPickerItem::ObjectPickerItem(PhysicsObject *object, const Point2i &position, unsigned int width) :
		Button("", position, width)
	{
		this->object = object;

		opiDl = 0;
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

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
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

		if(!opiDl)
		{
			opiDl = glGenLists(1);
			glNewList(opiDl, GL_COMPILE);

			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 1.0f, 0.0f);
			glEnd();

			glEndList();
		}
		glCallList(opiDl);

		glTranslatef(0.5f, 0.5f, 0.0f);	
		glScalef(1.0f / (width - border), 1.0f, 1.0f);
		glScalef(buttonHeight - border, 1.0f, 1.0f);

		assert(object);
		object->renderThumbnail();

		glPopAttrib();
		glPopMatrix();
	}
}
