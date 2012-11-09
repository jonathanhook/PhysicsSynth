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
#include "ObjectPickerItem.h"
#include "PhysicsObject.h"

namespace PhysicsSynth
{
	/* Constructors */
	ObjectPickerItem::ObjectPickerItem(PhysicsObject *object, const Point2i &position, unsigned int width) :
		Button("", position, width)
	{
		this->object = object;
	}

	ObjectPickerItem::~ObjectPickerItem(void)
	{
	}
	
	/* Public Member Functions */
	PhysicsObject *ObjectPickerItem::getObject(void) const
	{
		return object;
	}

	void ObjectPickerItem::render(void)
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
			DARK_COLOUR.use();
		}
        
        GLPrimitives::getInstance()->renderSquare();

		glTranslatef(0.5f, 0.5f, 0.0f);	
		glScalef(1.0f / (width - border), 1.0f, 1.0f);
		glScalef(buttonHeight - border, 1.0f, 1.0f);

		assert(object);
		object->renderThumbnail();

        glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
		glPopMatrix();
	}
}
