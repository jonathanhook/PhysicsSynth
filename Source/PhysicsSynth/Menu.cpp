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
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/GLVbo.h>
#include <JDHUtility/Ndelete.h>
#include "Menu.h"

namespace PhysicsSynth
{
	/* Protected Constants */
	const std::string Menu::CREATE_TEXTURE	= "CreateIcon.tga";
	const std::string Menu::ERASE_TEXTURE	= "EraseIcon.tga";

	/* Private Constants */
	const Colour4f Menu::BACKGROUND_MASK_COLOUR	= Colour4f(0.0f, 0.0f, 0.0f, 0.9f);
	const Colour4f Menu::BORDER_COLOUR			= Colour4f(1.0f, 1.0f, 1.0f, 0.5f);

	/* Constructors */
	Menu::Menu(const Point2i &position, unsigned int width, unsigned char borderState, MenuMode mode) :
		UIElement(position, Point2i(width, 0))
	{
		this->borderState	= borderState;
		this->mode			= mode;

		addCursor		= Point2i(0, 0);
		maxY			= 0;

        GLfloat topv[6] =
        {
            0.0f,	0.0f,	0.0f,
            1.0f,	0.0f,	0.0f
        };
        topVbo = new GLVbo(GL_LINES, GL_STATIC_DRAW, topv, 2);
        
        GLfloat bottomv[12] =
        {
            0.0f,	0.0f,	0.0f,
            0.0f,	1.0f,	0.0f,
            1.0f,	1.0f,	0.0f,
            1.0f,   0.0f,   0.0f
        };
        bottomVbo = new GLVbo(GL_LINE_STRIP, GL_STATIC_DRAW, bottomv, 4);
        
        GLfloat leftv[6] =
        {
            0.0f,	0.0f,	0.0f,
            0.0f,	1.0f,	0.0f
        };
        leftVbo = new GLVbo(GL_LINES, GL_STATIC_DRAW, leftv, 2);
        
        GLfloat rightv[6] =
        {
            1.0f,	0.0f,	0.0f,
            1.0f,	1.0f,	0.0f
        };
        rightVbo = new GLVbo(GL_LINES, GL_STATIC_DRAW, rightv, 2);
	}

	Menu::~Menu(void)
	{
        NDELETE(topVbo);
        NDELETE(bottomVbo);
        NDELETE(leftVbo);
        NDELETE(rightVbo);
        
		for(unsigned int i = 0; i < menuItems.size(); i++)
		{
			NDELETE(menuItems[i]);
		}
		menuItems.clear();
	}

	/* Public Member Functions */
	void Menu::fingerAdded(const FingerEventArgs &e)
	{
	}

	void Menu::fingerUpdated(const FingerEventArgs &e)
	{
	}
	
	void Menu::fingerRemoved(const FingerEventArgs &e)
	{
	}

	void Menu::render(void)
	{        
		float px = getSizef(position.getX() - BORDER);
		float py = getSizef(position.getY());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px, py, 0.0f);

		float width		= getSizef(dimensions.getX() + (BORDER * 2));
		float height	= getSizef(dimensions.getY());
		glScalef(width, height, 1.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLineWidth(1.0f);
        
        BACKGROUND_MASK_COLOUR.use();
        GLPrimitives::getInstance()->renderSquare();
        
        if(mode == CREATE)
        {
            BORDER_COLOUR.use();
        }
        else
        {
            VALUE_COLOUR.use();
        }

		// top
		if(TOP & borderState)
		{
            topVbo->render();
        }
        
        // left
        if(LEFT & borderState)
        {
            leftVbo->render();
        }
        
        // right
        if(RIGHT & borderState)
        {
            rightVbo->render();
        }
        
        glPopMatrix();

        // bottom
        if(BOTTOM & borderState)
        {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(px, py + height, 0.0f);
            
            float bh = getSizef(BORDER * 2);
            glScalef(width, bh, 1.0f);
            
            BACKGROUND_MASK_COLOUR.use();
            GLPrimitives::getInstance()->renderSquare();
            
            if(mode == CREATE)
            {
                BORDER_COLOUR.use();
            }
            else
            {
                VALUE_COLOUR.use();
            }
            
            bottomVbo->render();
            
            glPopMatrix();
        }
        
        glDisable(GL_BLEND);
        
        // render children
		for(unsigned int i = 0; i < menuItems.size(); i++)
		{
			UIElement *m = menuItems[i];
			assert(m != NULL);
            
			m->render();
		}
	}
	
	void Menu::setBorderState(unsigned char borderState)
	{
		this->borderState = borderState;
	}

	void Menu::setPosition(const Point2i &position)
	{
		unsigned int tx = position.getX() - this->position.getX();
		unsigned int ty = position.getY() - this->position.getY();

		this->position = position;

		// update children
		for(unsigned int i = 0; i < menuItems.size(); i++)
		{
			UIElement *item = menuItems[i];
			assert(item);

			Point2i itemPos = item->getPosition();
			itemPos.translateX(tx);
			itemPos.translateY(ty);

			item->setPosition(itemPos);
		}
	}

	/* Protected Member Functions */
	void Menu::addMenuItem(UIElement &item)
	{
		int itemWidth	= item.getDimensions().getX();
		int itemHeight	= item.getDimensions().getY();
		int ax			= addCursor.getX();
		int ay			= addCursor.getY();
		int width		= dimensions.getX();
		int height		= dimensions.getY();
		
		if((ax + itemWidth) > width)
		{
			ax = 0; 
			ay = (ay + maxY);

			maxY = 0;
		}

		item.setPosition(Point2i(position.getX() + ax, position.getY() + ay));
		ax += itemWidth;

		if(itemHeight > (int)maxY)
		{
			int difference = itemHeight - maxY;
			dimensions.setY(height + difference);

			maxY = itemHeight;
		}

		addCursor.setX(ax);
		addCursor.setY(ay);

		// register
		registerEventHandler(&item);
		menuItems.push_back(&item);
	}
}
