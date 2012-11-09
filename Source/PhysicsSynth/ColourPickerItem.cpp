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
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/GLVbo.h>
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

		checked = false;
		
        GLfloat vertices[72] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.1f, 0.0f, 0.0f,
            
            0.1f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.1f, 1.0f, 0.0f,
            
            0.1f, 1.0f, 0.0f,
            0.9f, 1.0f, 0.0f,
            0.1f, 0.9f, 0.0f,
            
            0.9f, 1.0f, 0.0f,
            0.9f, 0.9f, 0.0f,
            0.1f, 0.9f, 0.0f,
            
            0.9f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            
            0.9f, 0.0f, 0.0f,
            0.9f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            
            0.1f, 0.0f, 0.0f,
            0.1f, 0.1f, 0.0f,
            0.9f, 0.1f, 0.0f,
            
            0.9f, 0.1f, 0.0f,
            0.9f, 0.0f, 0.0f,
            0.1f, 0.0f, 0.0f

        };
        checkedVbo = new GLVbo(GL_TRIANGLES, GL_STATIC_DRAW, vertices, 24);
	}

	ColourPickerItem::~ColourPickerItem(void)
	{
        NDELETE(checkedVbo);
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        const Colour3f &sc = colour->getColour();
        glColor4f(sc.getR(), sc.getG(), sc.getB(), COLOUR_ITEM_OPACITY);
        GLPrimitives::getInstance()->renderSquare();

        if(selected)
        {
            LIGHT_COLOUR.use();
            GLPrimitives::getInstance()->renderSquare();
        }
        
		glPopMatrix();

		if(checked)
		{
			float border	= getSizef(BORDER);
			float w			= getSizef(dimensions.getX());
			float h			= getSizef(dimensions.getY());

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glTranslatef(px + border, py + border, 0.0f);
			glScalef(w - border, h - border, 0.0f);
            glBlendFunc(GL_ONE, GL_ZERO);

            VALUE_COLOUR.use();
            checkedVbo->render();

			glPopMatrix();
		}
        
        glDisable(GL_BLEND);
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
