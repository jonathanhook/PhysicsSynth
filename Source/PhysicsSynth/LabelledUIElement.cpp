/**
 * Class:	LabelledUIElement
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/GLTextureFont.h>
#include <JDHUtility/GLFontManager.h>
#include <JDHUtility/GLPrimitives.h>
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	/* Constructors */
	LabelledUIElement::LabelledUIElement(std::string label, const Point2i &position, unsigned int width) :
		UIElement(position, Point2i(width, getLabelHeight()))
	{
		this->label = label;
	}

	LabelledUIElement::~LabelledUIElement(void)
	{
	}

	/* Public Member Functions */
	void LabelledUIElement::render(void)
	{
		float px			= getSizef(position.getX());
		float py			= getSizef(position.getY());
		float borderf		= getSizef(BORDER);
		float labelHeightf	= getSizef(getLabelHeight());
		float width			= getSizef(dimensions.getX());
			
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + borderf, py + borderf, 0.0f);
		glScalef(width - borderf, labelHeightf - borderf, 1.0f);
        
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
        LIGHT_COLOUR.use();
        GLPrimitives::getInstance()->renderSquare();
        
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px, py, 0.0f);

		GLFontManager *f = GLFontManager::getInstance();
		assert(f);

		f->renderString(GLFontManager::LARGE, label, Point2f(borderf * 4.0f, borderf));

		glPopMatrix();
	}
}
