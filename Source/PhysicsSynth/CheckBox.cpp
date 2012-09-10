/**
 * Class:	CheckBox
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Vector2f.h>
#include "CheckBox.h"

namespace PhysicsSynth
{
	/* Constructors */
	CheckBox::CheckBox(std::string label, const Point2i &position, unsigned int width) :
		Button(label, position, width)
	{
		checkedChanged	= NULL;
		isChecked		= false;
	}

	CheckBox::~CheckBox(void)
	{
	}

	/* Public Member Functions */
	void CheckBox::fingerAdded(const FingerEventArgs &e)
	{
		UIElement::fingerAdded(e);

		isChecked = !isChecked;

		if(checkedChanged != NULL)
		{
			checkedChanged(isChecked);
		}
	}
	
	void CheckBox::render(void)
	{
		if(isChecked)
		{
            float px    = getSizef(position.getX());
            float py    = getSizef(position.getY());
            float w     = getSizef(dimensions.getX());
            float h     = getSizef(dimensions.getY());
            float b     = getSizef(BORDER);
            
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(px + b, py + b, 0.0f);
            glScalef(w, h, 1.0f);

            glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            VALUE_COLOUR.use();
            GLPrimitives::getInstance()->renderSquare();
            
            glPopAttrib();
            glPopMatrix();
		}

		Button::render();
	}

	void CheckBox::setCheckedChangedCallback(CheckedChangedCallback checkedChanged)
	{
		this->checkedChanged = checkedChanged;
	}

	void CheckBox::setIsChecked(bool isChecked)
	{
		this->isChecked = isChecked;
	}
}
