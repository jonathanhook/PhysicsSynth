/**
 * Class:	Handle
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <assert.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLTexture.h>
#include <math.h>
#include <JDHUtility/Ndelete.h>
#include "Finger.h"
#include "Handle.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float			Handle::BACKGROUND_ALPHA			= 0.75f;
	const float			Handle::BACKGROUND_MASK_ALPHA		= 0.75f;
	const float			Handle::CIRCLE_VERTICES				= 32;
	const float			Handle::NON_SELECTED_ALPHA_MODIFIER	= 0.75f;
	const float			Handle::SELECTED_ALPHA_MODIFIER		= 1.0f;
	const std::string	Handle::TEXTURE_PATH				= "../../../Data/Textures/Handle/move.tga";
	const Colour4f		Handle::VALUE_COLOUR				= Colour4f(0.11f, 0.53f, 0.71f, 0.5f);

	/* Constructors */
	Handle::Handle(const Point2f &position, float size)
	{
		this->position	= position;
		this->size		= size;

		finger		= NULL;
		fingerDown	= false;
		modelview	= new GLMatrixf();
	}

	Handle::~Handle(void)
	{
		NDELETE(finger);
		NDELETE(modelview);
	}

	/* Public Member Functions */
	bool Handle::contains(const FingerEventArgs &e) const
	{
		assert(modelview != NULL);
		
		Point2f p =	e.getPosition();
		modelview->unTranslatePoint(p);
		modelview->unScalePoint(p);

		float a	= p.getX();
		float b	= p.getY();
		float c	= sqrt((a * a) + (b * b));

		return c <= size;
	}

	void Handle::fingerAdded(const FingerEventArgs &e)
	{
		if(!fingerDown)
		{
			Point2f p =	e.getPosition();
			modelview->unScalePoint(p);

			fingerDown	= true;
			finger		= new Finger(e.getId(), p);

			if(pressed != NULL)
			{
				pressed(this);
			}
		}
	}

	void Handle::fingerUpdated(const FingerEventArgs &e)
	{
		if(fingerDown)
		{
			assert(finger);
			unsigned int id = e.getId();

			if(finger->getId() == id && dragged != NULL)
			{
				Point2f p =	e.getPosition();
				modelview->unScalePoint(p);

				finger->updatePosition(p);
				
				Vector2f delta = finger->getDelta();
				dragged(this, delta);
			}
		}
	}
	
	void Handle::fingerRemoved(const FingerEventArgs &e)
	{
		if(fingerDown)
		{
			assert(finger);
			unsigned int id = e.getId();

			if(finger->getId() == id)
			{
				fingerDown = false;
				NDELETE(finger);
			}
		}
	}

	void Handle::render(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(position.getX(), position.getY(), 0.0f);
		saveTransform();

		// background mask
		static unsigned int backgroundMaskDl = -1;
		if(backgroundMaskDl == -1)
		{
			backgroundMaskDl = glGenLists(1);
			glNewList(backgroundMaskDl, GL_COMPILE);
			
			glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.0f, 0.0f, 0.0f, BACKGROUND_MASK_ALPHA);

			glBegin(GL_POLYGON);
				for(unsigned int i = 0; i < CIRCLE_VERTICES; i++)
				{
					float theta = (((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES) * (float)i; 
					float x		= cos(theta) * size;
					float y		= sin(theta) * size;

					glVertex3f(x, y, 0.0f);
				}
			glEnd();

			glPopAttrib(); // GL_CURRENT_BIT | GL_ENABLE_BIT
			glEndList();
		}
		glCallList(backgroundMaskDl);

		// border
		float alphaModifier = fingerDown ? SELECTED_ALPHA_MODIFIER : NON_SELECTED_ALPHA_MODIFIER;

		glPushAttrib(GL_CURRENT_BIT);
		glColor4f(VALUE_COLOUR.getR(), VALUE_COLOUR.getG(), VALUE_COLOUR.getB(), alphaModifier);

		static unsigned int borderDl = -1;
		if(borderDl == -1)
		{
			borderDl = glGenLists(1);
			glNewList(borderDl, GL_COMPILE);

			glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glLineWidth(1.0f);

			glBegin(GL_LINE_LOOP);
				for(unsigned int i = 0; i < CIRCLE_VERTICES; i++)
				{
					float theta = (((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES) * (float)i; 
					float x		= cos(theta) * size;
					float y		= sin(theta) * size;

					glVertex3f(x, y, 0.0f);
				}
			glEnd();

			glPopAttrib(); // GL_LINE_BIT | GL_ENABLE_BIT
			glEndList();
		}
		glCallList(borderDl);
		
		// texture
		glColor4f(1.0f, 1.0f, 1.0f, BACKGROUND_ALPHA * alphaModifier);

		static unsigned int textureDl = -1;
		if(textureDl == -1)
		{
			// texture on stack so only ever loaded once
			GLTexture texture(TEXTURE_PATH);
	
			textureDl = glGenLists(1);
			glNewList(textureDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			texture.bind(GL_MODULATE);
			glBegin(GL_POLYGON);
				for(unsigned int i = 0; i < CIRCLE_VERTICES; i++)
				{
					float theta = (((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES) * (float)i; 
					float x		= cos(theta) * size;
					float y		= sin(theta) * size;
					float u		= (x + size) / (size * 2.0f);
					float v		= (y + size) / (size * 2.0f);

					glTexCoord2f(u, v);
					glVertex3f(x, y, 0.0f);
				}
			glEnd();

			glPopAttrib();
			glEndList();
		}
		glCallList(textureDl);

		glPopAttrib(); // GL_CURRENT_BIT
		glPopMatrix();
	}

	void Handle::setDraggedCallback(DraggedCallback dragged)
	{
		this->dragged = dragged;
	}

	void Handle::setPosition(const Point2f &position)
	{
		this->position = position;
	}

	void Handle::setPressedCallback	(PressedCallback pressed)
	{
		this->pressed = pressed;
	}

	/* Private Member Functions */
	void Handle::saveTransform(void)
	{
		assert(modelview != NULL);
		glGetFloatv(GL_MODELVIEW_MATRIX, modelview->getMatrix());
	}
}
