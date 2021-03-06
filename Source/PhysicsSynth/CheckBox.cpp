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
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Vector2f.h>
#include "CheckBox.h"

namespace PhysicsSynth
{
	/* Constructors */
	CheckBox::CheckBox(std::string label, const Point2i &position, unsigned int width) :
		Button(label, position, width)
	{
		checkedChanged	= NULL;
		isChecked		= false;
	}

	CheckBox::~CheckBox(void)
	{
	}

	/* Public Member Functions */
	void CheckBox::fingerAdded(const FingerEventArgs &e)
	{
		UIElement::fingerAdded(e);

		isChecked = !isChecked;

		if(checkedChanged != NULL)
		{
			checkedChanged(isChecked);
		}
	}
	
	void CheckBox::render(void)
	{
		if(isChecked)
		{
            float px    = getSizef(position.getX());
            float py    = getSizef(position.getY());
            float w     = getSizef(dimensions.getX());
            float h     = getSizef(dimensions.getY());
            float b     = getSizef(BORDER);
            
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(px + b, py + b, 0.0f);
            glScalef(w, h, 1.0f);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            VALUE_COLOUR.use();
            GLPrimitives::getInstance()->renderSquare();

            glDisable(GL_BLEND);
            glPopMatrix();
		}

		Button::render();
	}

	void CheckBox::setCheckedChangedCallback(CheckedChangedCallback checkedChanged)
	{
		this->checkedChanged = checkedChanged;
	}

	void CheckBox::setIsChecked(bool isChecked)
	{
		this->isChecked = isChecked;
	}
}
