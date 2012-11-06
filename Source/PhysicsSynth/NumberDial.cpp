//
//  NumberDial.cpp
//  PhysicsSynth
//
//  Created by Jonathan Hook on 05/11/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//
#include <math.h>
#include <JDHUtility/GLFontManager.h>
#include <JDHUtility/GLPrimitives.h>
#include "NumberDial.h"

namespace PhysicsSynth
{
    /* Constants */
    const unsigned int NumberDial::HEIGHT = 25;
    
    /* Public Constructors */
    NumberDial::NumberDial(const Point2i &position, unsigned int width, unsigned int min, unsigned int max, unsigned int initial) :
        UIElement(position, Point2i(width, HEIGHT))
    {
        this->min = min;
        this->max = max;
        this->current = initial;
        
        downVal = current;
        hasMoved = false;
        offset = 0;
        numberChanged = NULL;
    }
    
    NumberDial::~NumberDial(void)
    {
    }
    
    /* Public Functions */
    bool NumberDial::contains(const FingerEventArgs &e) const
    {
        float px		= e.getPosition().getX();
		float py		= e.getPosition().getY();
		float x			= UIElement::getSizef(position.getX() + parentPosition.getX());
		float y			= UIElement::getSizef(position.getY() + parentPosition.getY());
		float width		= UIElement::getSizef(dimensions.getX());
		float height	= UIElement::getSizef(dimensions.getY());
        
		return	(px >= x) &&
        (px <= (x + width)) &&
        (py >= y) &&
        (py <= (y + height));
    }
    
    void NumberDial::fingerAdded(const FingerEventArgs &e)
    {
        UIElement::fingerAdded(e);
        downY = e.getY();
        downVal = current;
        hasMoved = false;
    }
    
    void NumberDial::fingerUpdated(const FingerEventArgs &e)
    {
        float dy = e.getY() - downY;
        offset = dy / UIElement::getSizef(dimensions.getY() / 2);
        
        int currentVal = downVal + (int)offset;
        if(currentVal < (int)min)
        {
            currentVal = (max + 1) + (currentVal - min);
        }
        else if(currentVal > max)
        {
            currentVal = currentVal - max;
        }
        current = currentVal;
        
        if(offset > 0.1f || offset < -0.1f)
        {
            hasMoved = true;
        }
    }
    
    void NumberDial::fingerRemoved(const FingerEventArgs &e)
    {
        UIElement::fingerRemoved(e);
        
        if(!hasMoved)
        {
            current++;
        }
        
        if(current != downVal && numberChanged != NULL)
        {
            numberChanged(current);
        }
        
        offset = 0.0f;
    }
    
    unsigned int NumberDial::getValue(void) const
    {
        return current;
    }
    
    void NumberDial::render(void)
    {
        float px		= UIElement::getSizef(position.getX());
		float py		= UIElement::getSizef(position.getY());
		float height	= UIElement::getSizef(dimensions.getY());
		float border	= UIElement::getSizef(BORDER);
		float width		= UIElement::getSizef(dimensions.getX());
        
        float fy = offset;
        float dy = fmodf(fy, 1.0f);
        if(dy < 0.0f)
        {
            dy = 1.0f + dy;
        }
    
        glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        if(selected)
		{
			LIGHT_COLOUR.use();
		}
		else
		{
			MID_COLOUR.use();
		}
        
        glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
        glScalef(width - border, height - border, 1.0f);
                
        GLPrimitives::getInstance()->renderSquare();
        
        glPopMatrix();
        
        char buf[1024];
        sprintf(buf, "%i", current);
        
        Vector2f box = GLFontManager::getInstance()->queryBox(GLFontManager::MEDIUM, buf);
        float tx = px + (width - box.getX()) - (border * 4.0f);
        float ty = py + ((height / 2.0f) - (box.getY() / 2.0f)) - border;
        
        FONT_COLOUR.use();
        GLFontManager::getInstance()->renderString(GLFontManager::MEDIUM, buf, Point2f(tx, ty));
    }
    
    void NumberDial::setNumberChangedCallback(NumberChangedCallback numberChanged)
    {
        this->numberChanged = numberChanged;
    }
    
    void NumberDial::setParentPosition(const Point2i &parentPosition)
    {
        this->parentPosition = parentPosition;
    }
    
    void NumberDial::setValue(unsigned int value)
    {
        this->current = value;
    }

}