/**
 * Class:	ColourPickerItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <JDHUtility/OpenGL.h>
#include "ColourPickerItem.h"
#include "SoundConfig.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float			ColourPickerItem::COLOUR_ITEM_OPACITY	= 0.75f;
	const unsigned int	ColourPickerItem::RIM					= 2;

	/* Constructors */
	ColourPickerItem::ColourPickerItem(SoundConfig *colour, const Point2i &position, const Point2i &dimensions) :
		UIElement(position, dimensions)
	{
		this->colour = colour;

		checked				= false;
		checkedDl			= -1;
		colourDl			= -1;
		colourSelectedDl	= -1;
	}

	ColourPickerItem::~ColourPickerItem(void)
	{
	}

	/* Public Member Functions */
	void ColourPickerItem::fingerAdded(const FingerEventArgs &e)
	{
		UIElement::fingerAdded(e);
		checked = true;

		if(checkedCallback != NULL)
		{
			checkedCallback(this);
		}
	}

	SoundConfig *ColourPickerItem::getColour(void) const
	{
		return colour;
	}

	bool ColourPickerItem::isChecked(void) const
	{
		return checked;
	}

	void ColourPickerItem::render(void)
	{
		float px		= getSizef(position.getX());
		float py		= getSizef(position.getY());
		float border	= getSizef(BORDER);
		float w			= getSizef(dimensions.getX());
		float h			= getSizef(dimensions.getY());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(w - border, h - border, 0.0f);

		if(colourDl == -1)
		{
			colourDl = glGenLists(1);
			glNewList(colourDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			const Colour3f &sc = colour->getColour();
			glColor4f(sc.getR(), sc.getG(), sc.getB(), COLOUR_ITEM_OPACITY);
			glBegin(GL_QUADS);
				glVertex3f(0.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	1.0f,	0.0f);
				glVertex3f(0.0f,	1.0f,	0.0f);
			glEnd();

			glPopAttrib(); // GL_ENABLE_BIT | GL_CURRENT_BIT
			glEndList();
		}
		glCallList(colourDl);

		if(selected)
		{
			if(colourSelectedDl == -1)
			{
				colourSelectedDl = glGenLists(1);
				glNewList(colourSelectedDl, GL_COMPILE);

				float border	= getSizef(BORDER);
				float w			= getSizef(dimensions.getX());
				float h			= getSizef(dimensions.getY());

				glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				LIGHT_COLOUR.use();
				glBegin(GL_QUADS);
					glVertex3f(0.0f,	0.0f,	0.0f);
					glVertex3f(1.0f,	0.0f,	0.0f);
					glVertex3f(1.0f,	1.0f,	0.0f);
					glVertex3f(0.0f,	1.0f,	0.0f);
				glEnd();

				glPopAttrib(); // GL_ENABLE_BIT | GL_CURRENT_BIT
				glEndList();
			}
			glCallList(colourSelectedDl);
		}
		glPopMatrix();

		if(checked)
		{
			float border	= getSizef(BORDER);
			float w			= getSizef(dimensions.getX());
			float h			= getSizef(dimensions.getY());
			float rim		= getSizef(RIM);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glTranslatef(px + border, py + border, 0.0f);
			glScalef(w - border, h - border, 0.0f);

			if(checkedDl == -1)
			{
				checkedDl = glGenLists(1);
				glNewList(checkedDl, GL_COMPILE);

				glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ZERO);

				VALUE_COLOUR.use();
				glBegin(GL_QUADS);
					// top
					glVertex3f(0.0f,	0.0f,	0.0f);
					glVertex3f(1.0f,	0.0f,	0.0f);
					glVertex3f(1.0f,	0.1f,	0.0f);
					glVertex3f(0.0f,	0.1f,	0.0f);

					// bottom
					glVertex3f(0.0f,	1.0f - 0.1f,	0.0f);
					glVertex3f(1.0f,	1.0f - 0.1f,	0.0f);
					glVertex3f(1.0f,	1.0f,			0.0f);
					glVertex3f(0.0f,	1.0f,			0.0f);

					// left
					glVertex3f(0.0f,	0.1f,			0.0f);
					glVertex3f(0.1f,	0.1f,			0.0f);
					glVertex3f(0.1f,	1.0f - 0.1f,	0.0f);
					glVertex3f(0.0f,	1.0f - 0.1f,	0.0f);

					// right
					glVertex3f(1.0f - 0.1f,	0.1f,			0.0f);
					glVertex3f(1.0f,		0.1f,			0.0f);
					glVertex3f(1.0f,		1.0f - 0.1f,	0.0f);
					glVertex3f(1.0f- 0.1f,	1.0f - 0.1f,	0.0f);
				glEnd();

				glPopAttrib(); // GL_ENABLE_BIT | GL_CURRENT_BIT
				glEndList();
			}
			glCallList(checkedDl);
			glPopMatrix();
		}
	}

	void ColourPickerItem::setChecked(bool checked)
	{
		this->checked = checked;
	}

	void ColourPickerItem::setCheckedCallback(CheckedCallback checkedCallback)
	{
		this->checkedCallback = checkedCallback;
	}
}
