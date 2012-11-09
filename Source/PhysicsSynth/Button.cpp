/**
 * This file is part of PhysicsSynth.
 *
 * Created by Jonathan Hook (jonathan.hook@ncl.ac.uk)
 * Copyright (c) 2010-2012 Jonathan Hook. All rights reserved.
 *
 * PhysicsSynth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PhysicsSynth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PhysicsSynth.  If not, see <http://www.gnu.org/licenses/>.
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
			MID_COLOUR.use();
		}

        GLPrimitives::getInstance()->renderSquare();

		glPopMatrix();

		GLFontManager *f = GLFontManager::getInstance();
		assert(f);

		const Vector2f &dims = f->queryBox(GLFontManager::LARGE, label);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border + (width / 2.0f) - (dims.getX() / 2.0f), py + border + (buttonHeight / 2.0f) - (dims.getY() / 2.0f), 0.0f);

        FONT_COLOUR.use();
		f->renderString(GLFontManager::LARGE, label, Point2f(0, 0));

        glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
        
		glPopMatrix();
	}
}
