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
#include <JDHUtility/GLTexture.h>
#include <JDHUtility/GLPrimitives.h>
#include "PushButton.h"

namespace PhysicsSynth
{
	/* Constructors */
	PushButton::PushButton(std::string texturePath, const Point2i &position, const Point2i &dimensions) :
		UIElement(position, dimensions)
    {
		texture = new GLTexture(texturePath);
	}

	PushButton::~PushButton(void)
	{
	}

	/* Public Member Functions */
	void PushButton::render(void)
	{
		float px = getSizef(position.getX());
		float py = getSizef(position.getY());			
		float border	= getSizef(BORDER);
		float dimX		= getSizef(dimensions.getX());
		float dimY		= getSizef(dimensions.getY());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(dimX - border, dimY - border, 1.0f);
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

        assert(texture);
        if(texture->isTexture())
        {
            glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
            glTranslatef(0.125f, 0.125f, 0.0f);
            glScalef(0.75f, 0.75f, 1.0f);
            
            texture->bind(GL_MODULATE, GL_LINEAR, GL_LINEAR);
            GLPrimitives::getInstance()->renderSquare();
            texture->unbind();
        }
        
        glDisable(GL_BLEND);
		glPopMatrix();
	}
}
