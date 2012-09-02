/**
 * Class:	PatternPickerItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLPrimitives.h>
#include "PatternPickerItem.h"

namespace PhysicsSynth
{
	/* Constructors */
	PatternPickerItem::PatternPickerItem(unsigned int mask, const Point2i &position, unsigned int width) :
		UIElement(position, Point2i(width, getLabelHeight()))
	{
		this->mask = mask;

		checked = false;

		dimensions.setY(getLabelHeight());
	}

	PatternPickerItem::~PatternPickerItem(void)
	{
	}

	/* Public Member Functions */
	bool PatternPickerItem::getChecked(void) const
	{
		return checked;
	}

	unsigned int PatternPickerItem::getMask(void) const
	{
		return mask;
	}

	void PatternPickerItem::render(void)
	{
		float px		= getSizef(position.getX());
		float py		= getSizef(position.getY());
		float border	= getSizef(BORDER);
		float width		= getSizef(dimensions.getX());
		float height	= getSizef(dimensions.getY());


		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(width - border, height - border, 1.0f);

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        if(checked)
		{
			VALUE_COLOUR.use();
		}
		else
		{
			DARK_COLOUR.use();
		}

        GLPrimitives::getInstance()->renderSquare();

		glPopAttrib(); // GL_CURRENT_BIT
		glPopMatrix();
	}

	void PatternPickerItem::setChecked(bool checked)
	{
		this->checked = checked;
	}
}