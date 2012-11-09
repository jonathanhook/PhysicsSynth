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

        FONT_COLOUR.use();
		f->renderString(GLFontManager::LARGE, label, Point2f(borderf * 4.0f, borderf));

        glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
		glPopMatrix();
	}
}
