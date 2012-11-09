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
#include "Slider.h"

namespace PhysicsSynth
{
	/* Constructors */
	Slider::Slider(std::string label, const Point2i &position, unsigned int width) :
		LabelledUIElement(label, position, width)
	{
		value		= 0.0f;

		dimensions.setY(getLabelHeight() * 2);
	}

	Slider::~Slider(void)
	{
	}

	/* Public Member Functions */
	void Slider::fingerAdded(const FingerEventArgs &e)
	{
		UIElement::fingerAdded(e);
		updateValue(e);
	}

	void Slider::fingerUpdated(const FingerEventArgs &e)
	{
		UIElement::fingerUpdated(e);
		updateValue(e);
	}

	void Slider::fingerRemoved(const FingerEventArgs &e)
	{
		UIElement::fingerRemoved(e);
		updateValue(e);
	}

	float Slider::getValue(void) const
	{
		return value;
	}

	void Slider::render(void)
	{
		LabelledUIElement::render();

		float px			= getSizef(position.getX());
		float py			= getSizef(position.getY() + getLabelHeight());
		float border		= getSizef(BORDER);
		float labelHeight	= getSizef(getLabelHeight());
		float width			= getSizef(dimensions.getX());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(width - border, labelHeight - border, 1.0f);
		glEnable(GL_BLEND);
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
         
		glPopMatrix();

		border		= getSizef(BORDER);
		labelHeight	= getSizef(getLabelHeight());
		width		= getSizef(dimensions.getX());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef((width - border) * value, labelHeight - border, 1.0f);

        VALUE_COLOUR.use();
        GLPrimitives::getInstance()->renderSquare();
        
        glDisable(GL_BLEND);
		glPopMatrix();
	}

	void Slider::setValue(float value)
	{
		this->value = value;
	}

	void Slider::setValueChangedCallback(ValueChangedCallback valueChanged)
	{
		this->valueChanged = valueChanged;
	}

	/* Private Member Functions */
	void Slider::updateValue(const FingerEventArgs &e)
	{
		float fingerX			= e.getPosition().getX();
		float targetRegionX		= getSizef(position.getX() + BORDER);
		float targetRegionWidth	= getSizef(dimensions.getX() - (BORDER * 2));
		float tx				= (fingerX - targetRegionX) / targetRegionWidth;

		// clamp
		if(tx < 0.0f)
		{
			tx = 0.0f;
		}
		else if(tx > 1.0f)
		{
			tx = 1.0f;
		}

		bool changed = (value != tx);
		value = tx;

		if(changed && valueChanged != NULL)
		{
			valueChanged(value);
		}
	}
}
