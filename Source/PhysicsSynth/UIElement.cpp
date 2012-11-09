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
#include <JDHUtility/GLTextureFont.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/WindowingUtils.h>
#include "UIElement.h"

namespace PhysicsSynth
{
	/* Protected Constants */
	const unsigned int 	UIElement::BORDER			= 1;
	const Colour4f		UIElement::DARK_COLOUR		(1.0f, 1.0f, 1.0f, 0.1f);
	const unsigned int	UIElement::LABEL_HEIGHT_DIV	= 27;
	const Colour4f		UIElement::LIGHT_COLOUR		(1.0f, 1.0f, 1.0f, 0.25f);
    const Colour4f		UIElement::MID_COLOUR		(1.0f, 1.0f, 1.0f, 0.15f);
	const Colour4f		UIElement::VALUE_COLOUR		(0.11f, 0.53f, 0.71f, 0.5f);
    const Colour4f      UIElement::FONT_COLOUR      (1.0f, 1.0f, 1.0f, 0.75f);

	/* Static Functions */
	float UIElement::getSizef(unsigned int pixels)
	{
		const Vector2f &dims = WindowingUtils::getWindowDimensions();
		float w = dims.getX();

		return (float)pixels / w;
	}

	/* Constructors */
	UIElement::UIElement(const Point2i &position, const Point2i &dimensions)
	{
		this->position		= position;
		this->dimensions	= dimensions;

		captured	= false;
		capturedId	= 0;
		clicked		= NULL;
		pressed		= NULL;
		released	= NULL;
		selected	= false;

		winWidth	= 1024; // HACK: basically makes the menu a fixed width independent of screen size
		winHeight	= 600;	// HACK: basically makes the menu a fixed height independent of screen size
	}

	UIElement::~UIElement(void)
	{

	}

	/* Public Member Functions */
	bool UIElement::contains(const FingerEventArgs &e) const
	{
		float px		= e.getPosition().getX();
		float py		= e.getPosition().getY();
		float x			= getSizef(position.getX());
		float y			= getSizef(position.getY());
		float width		= getSizef(dimensions.getX());
		float height	= getSizef(dimensions.getY());

		return	(px >= x) && 
				(px <= (x + width)) &&
				(py >= y) &&
				(py <= (y + height));
	}

	void UIElement::fingerAdded(const FingerEventArgs &e)
	{
		if(!captured)
		{
			capturedId	= e.getId();
			captured	= true;
			selected	= true;

			if(pressed != NULL)
			{
				pressed(this);
			}
		}
	}

	void UIElement::fingerUpdated(const FingerEventArgs &e)
	{
	}

	void UIElement::fingerRemoved(const FingerEventArgs &e)
	{
		if(captured && capturedId == e.getId())
		{
			captured	= false;
			selected	= false;

			if(released != NULL)
			{
				released(this);
			}

			if(clicked != NULL && contains(e))
			{
				clicked(this);
			}
		}
	}

	const Point2i &UIElement::getDimensions(void) const
	{
		return dimensions;
	}

	const Point2i &UIElement::getPosition(void) const
	{
		return position;
	}

	void UIElement::setClickedCallback(ClickedCallback clicked)
	{
		this->clicked = clicked;
	}

	void UIElement::setDimensions(const Point2i &dimensions)
	{
		this->dimensions = dimensions;
	}

	void UIElement::setPosition(const Point2i &position)
	{
		this->position = position;
	}

	void UIElement::setPressedCallback(PressedCallback pressed)
	{
		this->pressed = pressed;
	}
	
	void UIElement::setReleasedCallback(ReleasedCallback released)
	{
		this->released = released;
	}

	/* Protected Member Functions */
	unsigned int UIElement::getLabelHeight(void) const
	{
		return winHeight / LABEL_HEIGHT_DIV;
	}

}
