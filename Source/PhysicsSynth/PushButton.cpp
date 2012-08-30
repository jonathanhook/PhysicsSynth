/**
 * Class:	PushButton
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLTexture.h>
#include "PushButton.h"

namespace PhysicsSynth
{
	/* Constructors */
	PushButton::PushButton(std::string texturePath, const Point2i &position, const Point2i &dimensions) :
		UIElement(position, dimensions)
	{
		dl		= -1;
		texture = new GLTexture(texturePath);
	}

	PushButton::~PushButton(void)
	{
	}

	/* Public Member Functions */
	void PushButton::render(void)
	{
		float px = getSizef(position.getX());
		float py = getSizef(position.getY());			
		float border	= getSizef(BORDER);
		float dimX		= getSizef(dimensions.getX());
		float dimY		= getSizef(dimensions.getY());

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(px + border, py + border, 0.0f);
		glScalef(dimX - border, dimY - border, 1.0f);

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if(selected)
		{
			LIGHT_COLOUR.use();
		}
		else
		{
			DARK_COLOUR.use();
		}

		if(dl == -1) 
		{
			dl = glGenLists(1);
			glNewList(dl, GL_COMPILE);

			glBegin(GL_QUADS);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 1.0f, 0.0f);
				glVertex3f(0.0f, 1.0f, 0.0f);
			glEnd();

			assert(texture);
			if(texture->isTexture())
			{
				texture->bind(GL_REPLACE);
	
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 1.0f);	glVertex3f(0.0f, 0.0f,	0.0f);
					glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 0.0f,	0.0f);
					glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f,	0.0f);
					glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 1.0f,	0.0f);
				glEnd();
			}

			glEndList();
		}
		glCallList(dl);

		glPopAttrib();
		glPopMatrix();
	}
}
