/**
 * Class:	OptionGridItem
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/GLFontManager.h>
#include "OptionGridItem.h"

namespace PhysicsSynth
{
	/* Constructors */
	OptionGridItem::OptionGridItem(const OptionGrid::Option &option, const Point2i &position, const Point2i &dimensions) :
		UIElement(position, dimensions)
	{
		this->option = option;

		checked		= false;
		checkBoxDl	= -1;
		labelDl		= -1;
	}

	OptionGridItem::~OptionGridItem(void)
	{
	}

	/* Public Member Functions */
	void OptionGridItem::fingerAdded(const FingerEventArgs &e)
	{
		UIElement::fingerAdded(e);
		checked = true;

		if(checkedCallback != NULL)
		{
			checkedCallback(this);
		}
	}

	const OptionGrid::Option &OptionGridItem::getOption(void) const
	{
		return option;
	}

	bool OptionGridItem::isChecked(void) const
	{
		return checked;
	}

	void OptionGridItem::render(void)
	{
		float px	= getSizef(position.getX());
		float py	= getSizef(position.getY());\
		float pos	= getSizef(BORDER);
		float dim	= getSizef(dimensions.getY() - (BORDER * 2));

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + pos, py + pos, 0.0f);
		glScalef(pos + dim, pos + dim, 1.0f);

		// check box
		glPushAttrib(GL_CURRENT_BIT);
		if(checked)
		{
			VALUE_COLOUR.use();
		}
		else
		{
			LIGHT_COLOUR.use();
		}
		
		if(checkBoxDl == -1)
		{
			checkBoxDl = glGenLists(1);
			glNewList(checkBoxDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_QUADS);
				glVertex3f(0.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	1.0f,	0.0f);
				glVertex3f(0.0f,	1.0f,	0.0f);
			glEnd();

			glPopAttrib(); // GL_ENABLE_BIT
			glEndList();
		}
		glCallList(checkBoxDl);
		glPopMatrix();
		glPopAttrib(); // GL_CURRENT_BIT

		// label region
		float posX	= getSizef(BORDER + dimensions.getY());
		float posY	= getSizef(BORDER);
		float dimX	= getSizef(dimensions.getX()/* - BORDER*/) - posX;
		float dimY	= getSizef(dimensions.getY() - (BORDER * 2));

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + posX, py + posY, 0.0f);
		glScalef(dimX, posY + dimY, 1.0f);

		glPushAttrib(GL_CURRENT_BIT);
		if(selected)
		{
			LIGHT_COLOUR.use();
		}
		else
		{
			DARK_COLOUR.use();
		}

		if(labelDl == -1)
		{
			labelDl = glGenLists(1);
			glNewList(labelDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_QUADS);
				glVertex3f(0.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	1.0f,	0.0f);
				glVertex3f(0.0f,	1.0f,	0.0f);
			glEnd();

			glPopAttrib(); // GL_ENABLE_BIT
			glEndList();
		}
		glCallList(labelDl);
		glPopAttrib();
		glPopMatrix();

		// label
		/*
		float fontHeight = getSizef(dimensions.getY());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(fontHeight, 0.0f, 0.0f);

		glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
		glLineWidth(TEXT_LINE_WIDTH);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		FONT2_COLOUR.use();

		GLFontManager *f = GLFontManager::getInstance();
		assert(f);
		
		std::string *label = &option.label;
		assert(label);

		float textWidth = getSizef(getTextWidth()) * (float)(*label).size();
		f->renderString(FONT2, *label, Vector2f(textWidth, fontHeight), FONT2_BORDER);

		glPopAttrib(); // GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT
		glPopMatrix();
		*/

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + dim, py, 0.0f);

		GLFontManager *f = GLFontManager::getInstance();
		assert(f);

		f->renderString(GLFontManager::MEDIUM, option.label, Point2f(dim / 2.0f, dim / 7.0f));

		glPopMatrix();
	}

	void OptionGridItem::setChecked(bool checked)
	{
		this->checked = checked;
	}

	void OptionGridItem::setCheckedCallback(CheckedCallback checkedCallback)
	{
		this->checkedCallback = checkedCallback;
	}
}
