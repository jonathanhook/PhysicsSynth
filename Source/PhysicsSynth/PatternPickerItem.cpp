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
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLPrimitives.h>
#include "PatternPickerItem.h"

namespace PhysicsSynth
{
	/* Constructors */
	PatternPickerItem::PatternPickerItem(unsigned int mask, const Point2i &position, unsigned int width) :
		UIElement(position, Point2i(width, getLabelHeight()))
	{
		this->mask = mask;

		checked = false;

		dimensions.setY(getLabelHeight());
	}

	PatternPickerItem::~PatternPickerItem(void)
	{
	}

	/* Public Member Functions */
	bool PatternPickerItem::getChecked(void) const
	{
		return checked;
	}

	unsigned int PatternPickerItem::getMask(void) const
	{
		return mask;
	}

	void PatternPickerItem::render(void)
	{
		float px		= getSizef(position.getX());
		float py		= getSizef(position.getY());
		float border	= getSizef(BORDER);
		float width		= getSizef(dimensions.getX());
		float height	= getSizef(dimensions.getY());


		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(width - border, height - border, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        if(checked)
		{
			VALUE_COLOUR.use();
		}
		else
		{
			DARK_COLOUR.use();
		}

        GLPrimitives::getInstance()->renderSquare();

        glDisable(GL_BLEND);
		glPopMatrix();
	}

	void PatternPickerItem::setChecked(bool checked)
	{
		this->checked = checked;
	}
}