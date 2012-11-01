/**
 * Class:	Handle
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLTexture.h>
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/GLTexture.h>
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
	const std::string	Handle::TEXTURE_PATH				= "move.tga";
	const Colour4f		Handle::VALUE_COLOUR				= Colour4f(0.11f, 0.53f, 0.71f, 0.5f);

	/* Constructors */
	Handle::Handle(const Point2f &position, float size)
	{
		this->position	= position;
		this->size		= size;

		finger		= NULL;
		fingerDown	= false;
		modelview	= new GLMatrixf();
        texture     = new GLTexture(TEXTURE_PATH);
	}

	Handle::~Handle(void)
	{
		NDELETE(finger);
		NDELETE(modelview);
        NDELETE(texture);
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
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.0f, 0.0f, BACKGROUND_MASK_ALPHA);

        glScalef(size, size, 1.0f);
        GLPrimitives::getInstance()->renderCircle();

		// border
		float alphaModifier = fingerDown ? SELECTED_ALPHA_MODIFIER : NON_SELECTED_ALPHA_MODIFIER;

		glColor4f(VALUE_COLOUR.getR(), VALUE_COLOUR.getG(), VALUE_COLOUR.getB(), alphaModifier);
        glLineWidth(1.0f);

        GLPrimitives::getInstance()->renderCircleOutline();

		// texture
		glColor4f(1.0f, 1.0f, 1.0f, BACKGROUND_ALPHA * alphaModifier);

        texture->bind(GL_MODULATE);
        GLPrimitives::getInstance()->renderCircle();
        texture->unbind();

        glDisable(GL_BLEND);
        glDisable(GL_LINE_SMOOTH);
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
