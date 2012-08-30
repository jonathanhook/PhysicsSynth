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
#include "LabelledUIElement.h"

namespace PhysicsSynth
{
	/* Constructors */
	LabelledUIElement::LabelledUIElement(std::string label, const Point2i &position, unsigned int width) :
		UIElement(position, Point2i(width, getLabelHeight()))
	{
		this->label = label;

		dl = -1;
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

		glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		if(dl == -1)
		{
			dl = glGenLists(1);
			glNewList(dl, GL_COMPILE);

			float borderf		= getSizef(BORDER);
			float labelHeightf	= getSizef(getLabelHeight());
			float width			= getSizef(dimensions.getX());
			
			LIGHT_COLOUR.use();
			glBegin(GL_QUADS);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 1.0f, 0.0f);
				glVertex3f(0.0f, 1.0f, 0.0f);
			glEnd();

			glEndList();
		}
		glCallList(dl);

		glPopAttrib(); // GL_LINE_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT
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
