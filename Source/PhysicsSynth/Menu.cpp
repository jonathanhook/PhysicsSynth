/**
 * Class:	Menu
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/Ndelete.h>
#include "Menu.h"

namespace PhysicsSynth
{
	/* Protected Constants */
	const std::string Menu::CREATE_TEXTURE	= "../../../Data/Textures/Menu/CreateIcon.tga";
	const std::string Menu::ERASE_TEXTURE	= "../../../Data/Textures/Menu/EraseIcon.tga";

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
		backgroundDl	= -1;
		maxY			= 0;
		menuDl			= -1;
	}

	Menu::~Menu(void)
	{
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
		float py = getSizef(position.getY() - BORDER);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px, py, 0.0f);

		float width		= getSizef(dimensions.getX() + (BORDER * 3));
		float height	= getSizef(dimensions.getY() + (BORDER * 3));
		glScalef(width, height, 1.0f);

		if(backgroundDl == -1)
		{
			backgroundDl = glGenLists(1);
			glNewList(backgroundDl, GL_COMPILE);

			glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			BACKGROUND_MASK_COLOUR.use();
			glBegin(GL_QUADS);
				glVertex3f(0.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	0.0f,	0.0f);
				glVertex3f(1.0f,	1.0f,	0.0f);
				glVertex3f(0.0f,	1.0f,	0.0f);
			glEnd();

			// Coloured background when selected
			//if(mode != CREATE)
			//{
			//	glColor4f(VALUE_COLOUR.getR(), VALUE_COLOUR.getG(), VALUE_COLOUR.getB(), 0.15f);				
			//
			//	glBegin(GL_QUADS);
			//		glVertex3f(0.0f,	0.0f,	0.0f);
			//		glVertex3f(1.0f,	0.0f,	0.0f);
			//		glVertex3f(1.0f,	1.0f,	0.0f);
			//		glVertex3f(0.0f,	1.0f,	0.0f);
			//	glEnd();
			//}

			glPopAttrib();
			glEndList();
		}
		glCallList(backgroundDl);

		if(menuDl == -1)
		{
			menuDl = glGenLists(1);
			glNewList(menuDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				
			if(mode == CREATE)
			{
				BORDER_COLOUR.use();
				glLineWidth(1.0f);
			}
			else
			{
				VALUE_COLOUR.use();
				glLineWidth(2.0f);
			}

			glBegin(GL_LINES);
				// top
				if(TOP & borderState)
				{
					glVertex3f(0.0f,	0.0f,	0.0f);
					glVertex3f(1.0f,	0.0f,	0.0f);
				}

				// bottom
				if(BOTTOM & borderState)
				{
					glVertex3f(1.0f,	1.0f,	0.0f);
					glVertex3f(0.0f,	1.0f,	0.0f);
				}

				// left
				if(LEFT & borderState)
				{
					glVertex3f(0.0f,	0.0f,	0.0f);
					glVertex3f(0.0f,	1.0f,	0.0f);
				}

				// right
				if(RIGHT & borderState)
				{
					glVertex3f(1.0f,	0.0f,	0.0f);
					glVertex3f(1.0f,	1.0f,	0.0f);
				}
			glEnd();

			glPopAttrib();
			glEndList();
		}
		glCallList(menuDl);

		glPopMatrix();

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
