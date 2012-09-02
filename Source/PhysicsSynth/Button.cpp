/**
 * Class:	Button
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Vector2f.h>
#include <JDHUtility/GLFontManager.h>
#include <JDHUtility/GLPrimitives.h>
#include "Button.h"

namespace PhysicsSynth
{
	/* Constructors */
	Button::Button(std::string label, const Point2i &position, unsigned int width) :
		UIElement(position, Point2i(width, 0))
	{
		this->label = label;
        
		dimensions.setY(getLabelHeight() * 2);
	}

	Button::~Button(void)
	{
	}

	/* Public Member Functions */
	void Button::render(void)
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

        GLPrimitives::getInstance()->renderSquare();

		glPopAttrib(); // GL_CURRENT_BIT | GL_ENABLE_BIT
		glPopMatrix();

		GLFontManager *f = GLFontManager::getInstance();
		assert(f);

		const Vector2f &dims = f->queryBox(GLFontManager::LARGE, label);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border + (width / 2.0f) - (dims.getX() / 2.0f), py + border + (buttonHeight / 2.0f) - (dims.getY() / 2.0f), 0.0f);

		f->renderString(GLFontManager::LARGE, label, Point2f(0, 0));

		glPopMatrix();
	}
}
