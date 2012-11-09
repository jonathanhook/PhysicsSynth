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
#include <math.h>
#include <Ndelete.h>
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/GLVbo.h>
#include "TargetButton.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float	TargetButton::SNAP_THRESHOLD = 0.05f;
    const float	TargetButton::TARGET_SIZE = 0.05f;
    
	/* Constructors */
	TargetButton::TargetButton(std::string text, const Point2i &position, unsigned int width) :
		LabelledUIElement(text, position, width)
	{
        GLfloat hVerts[6] =
        {
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };
        hVbo = new GLVbo(GL_LINES, GL_STATIC_DRAW, hVerts, 2);
        
        GLfloat vVerts[6] =
        {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f
        };
        vVbo = new GLVbo(GL_LINES, GL_STATIC_DRAW, vVerts, 2);
        
		targetPosition.setX(0.0f);
		targetPosition.setY(0.0f);

		dimensions.setY(getLabelHeight() * 6);
	}

	TargetButton::~TargetButton(void)
	{
        NDELETE(vVbo);
        NDELETE(hVbo);
	}

	/* Public Member Functions */
	void TargetButton::fingerAdded(const FingerEventArgs &e)
	{
		LabelledUIElement::fingerAdded(e);
		updateTargetPosition(e);
	}
	
	void TargetButton::fingerUpdated(const FingerEventArgs &e)
	{
		LabelledUIElement::fingerUpdated(e);
		updateTargetPosition(e);
	}
	
	void TargetButton::fingerRemoved(const FingerEventArgs &e)
	{
		LabelledUIElement::fingerRemoved(e);
		updateTargetPosition(e);
	}

	const Vector2f &TargetButton::getTargetPosition(void) const
	{
		return targetPosition;
	}

	void TargetButton::render(void)
	{
		LabelledUIElement::render();

		float width		= getSizef(dimensions.getX() - (BORDER));
		float height	= getSizef(dimensions.getY() - (BORDER) - getLabelHeight());
		float px		= getSizef(position.getX() + BORDER);
		float py		= getSizef(position.getY() + BORDER + getLabelHeight());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px, py, 0.0f);
		glScalef(width, height, 1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        DARK_COLOUR.use();
        GLPrimitives::getInstance()->renderSquare();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.0f, (targetPosition.getY() / 2.0f) + 0.5f, 0.0f);
        glLineWidth(1.0f);
        VALUE_COLOUR.use();

        vVbo->render();

		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef((targetPosition.getX() / 2.0f) + 0.5f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        VALUE_COLOUR.use();

        hVbo->render();

		glPopMatrix();
        
        glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef((targetPosition.getX() / 2.0f) + 0.5f, (targetPosition.getY() / 2.0f) + 0.5f, 0.0f);
        glScalef(TARGET_SIZE, TARGET_SIZE * 2.0f, 1.0f);
        glTranslatef(-0.5f, -0.5f, 0.0f);
        
        GLPrimitives::getInstance()->renderSquareOutline();
        
        glPopMatrix();
        
        glDisable(GL_BLEND);
		glPopMatrix();
	}

	void TargetButton::setTargetChangedCallback(TargetChangedCallback targetChanged)
	{
		this->targetChanged = targetChanged;
	}

	void TargetButton::setTargetPosition(const Vector2f &targetPosition)
	{
		this->targetPosition = targetPosition;
	}

	/* Private Member Functions */
	void TargetButton::updateTargetPosition(const FingerEventArgs &e)
	{
		float fingerX				= e.getPosition().getX();
		float fingerY				= e.getPosition().getY();
		float targetRegionX			= getSizef(position.getX());
		float targetRegionY			= getSizef(position.getY() + getLabelHeight());
		float targetRegionWidth		= getSizef(dimensions.getX() / 2);
		float targetRegionHeight	= getSizef((dimensions.getY() - getLabelHeight()) / 2);
		float tx					= ((fingerX - targetRegionX) / targetRegionWidth) - 1.0f;
		float ty					= ((fingerY - targetRegionY) / targetRegionHeight) - 1.0f;

		// clamp
		if(tx > 1.0f)
		{
			tx = 1.0f;
		}
		else if(tx < -1.0f)
		{
			tx = -1.0f;
		}

		if(ty > 1.0f)
		{
			ty = 1.0f;
		}
		else if(ty < -1.0f)
		{
			ty = -1.0f;
		}

		// snap to centre
		if(fabs(tx) < SNAP_THRESHOLD)
		{
			tx = 0.0f; 
		}

		if(fabs(ty) < SNAP_THRESHOLD)
		{
			ty = 0.0f;
		}

		bool changed = (targetPosition.getX() != tx) || (targetPosition.getY() != ty);

		targetPosition.setX(tx);
		targetPosition.setY(ty);

		if(changed && targetChanged != NULL)
		{
			targetChanged(targetPosition);
		}
	}
}
