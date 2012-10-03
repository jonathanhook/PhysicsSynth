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
#include <JDHUtility/GLPrimitives.h>
#include "OptionGridItem.h"

namespace PhysicsSynth
{
	/* Constructors */
	OptionGridItem::OptionGridItem(const OptionGrid::Option &option, const Point2i &position, const Point2i &dimensions) :
		UIElement(position, dimensions)
	{
		this->option = option;

		checked		= false;
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
		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
		if(checked)
		{
			VALUE_COLOUR.use();
		}
		else
		{
			LIGHT_COLOUR.use();
		}
		
        GLPrimitives::getInstance()->renderSquare();
        
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

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
		if(selected)
		{
			LIGHT_COLOUR.use();
		}
		else
		{
			DARK_COLOUR.use();
		}

        GLPrimitives::getInstance()->renderSquare();

		glPopAttrib();
		glPopMatrix();

		// label
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
