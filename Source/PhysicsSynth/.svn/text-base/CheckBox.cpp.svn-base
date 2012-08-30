/**
 * Class:	CheckBox
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
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
		checkedDl		= -1;
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
			if(checkedDl == -1)
			{
				checkedDl = glGenLists(1);
				glNewList(checkedDl, GL_COMPILE);

				float px = getSizef(position.getX());
				float py = getSizef(position.getY());

				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glTranslatef(px, py, 0.0f);

				float w = getSizef(dimensions.getX());
				float h = getSizef(dimensions.getY());
				float b	= getSizef(BORDER);

				glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				VALUE_COLOUR.use();
				glBegin(GL_QUADS);
					glVertex3f(b,		b,		0.0f);
					glVertex3f(w - b,	b,		0.0f);
					glVertex3f(w - b,	h - b,	0.0f);
					glVertex3f(b,		h - b,	0.0f);
				glEnd();

				glPopAttrib();
				glPopMatrix();
				glEndList();
			}
			glCallList(checkedDl);
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
