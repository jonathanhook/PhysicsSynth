/**
 * Class:	PressAndHold
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/OpenGL.h>
#include <math.h>
#include <stdlib.h>
#include "PressAndHold.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int	PressAndHold::CIRCLE_SEGS	= 32;
	const float			PressAndHold::INNER_RAD		= 0.025f;
	const float			PressAndHold::MAX_OPACITY	= 0.75f;
	const float			PressAndHold::OUTER_RAD		= 0.04f;
	const float			PressAndHold::THRESHOLD		= 0.01f;
	const unsigned int	PressAndHold::TIMEOUT		= 750;

	/* Constructors */
	PressAndHold::PressAndHold(const Point2f &position, const Point2f &createPosition, unsigned int fingerId)
	{
		this->position			= position;
		this->createPosition	= createPosition;
		this->fingerId			= fingerId;

		completed		= NULL;
		dirty			= true;
		dl				= glGenLists(1);
		halfWay			= NULL;
		halfWayFired	= false;
		markedForDelete	= false;
		timeCreated		= CrossPlatformTime::getTimeMillis();
	}

	PressAndHold::~PressAndHold(void)
	{
	}

	/* Public Member Functions */
	bool PressAndHold::getMarkedForDelete(void) const
	{
		return markedForDelete;
	}

	void PressAndHold::render(void)
	{
		if(dirty)
		{
			float x = position.getX();
			float y = position.getY();
			float o = pow(progress, 4.0f);

			glNewList(dl, GL_COMPILE);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glTranslatef(x, y, 0.0f);
				
			glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0f, 1.0f, 1.0f, o * MAX_OPACITY);

			float radius	= OUTER_RAD;
			float iRadius	= INNER_RAD;
			float increment = 1.0f / (float)CIRCLE_SEGS;

			glBegin(GL_TRIANGLE_STRIP);
				for(float f = 0; f < progress; f += increment)
				{
					float theta = (2.0f * (float)M_PI) * f;
					float x = cos(theta) * radius;
					float y = sin(theta) * radius;

					float ix = cos(theta) * iRadius;
					float iy = sin(theta) * iRadius;

					glVertex3f(x, y, 0.0f);
					glVertex3f(ix, iy, 0.0f);
				}
			glEnd();

			glBegin(GL_LINE_STRIP);
				for(float f = 0; f < progress; f += increment)
				{
					float theta = (2.0f * (float)M_PI) * f;
					float x = cos(theta) * radius;
					float y = sin(theta) * radius;

					glVertex3f(x, y, 0.0f);
				}
			glEnd();

			glBegin(GL_LINE_STRIP);
				for(float f = 0; f < progress; f += increment)
				{
					float theta = (2.0f * (float)M_PI) * f;
					float ix = cos(theta) * iRadius;
					float iy = sin(theta) * iRadius;

					glVertex3f(ix, iy, 0.0f);
				}
			glEnd();
				
			glPopAttrib();
			glPopMatrix();
			glEndList();
            
			dirty = false;
		}
		glCallList(dl);
	}

	void PressAndHold::update(void)
	{
		unsigned int now		= CrossPlatformTime::getTimeMillis();
		unsigned int elapsed	= now - timeCreated;
		progress				= (float)elapsed / (float)TIMEOUT;
		dirty					= true;

		if(progress >= 1.0f && !markedForDelete)
		{
			if(completed != NULL)
			{
				completed(*this, createPosition);
			}

			markedForDelete = true;
		}
		else if(progress >= 0.5f && !markedForDelete && !halfWayFired)
		{
			if(halfWay != NULL)
			{
				halfWay(*this);
			}

			halfWayFired = true;
		}
	}

	void PressAndHold::updateFingerPosition(const Point2f &newPosition)
	{
		float dx	= position.getX() - newPosition.getX();
		float dy	= position.getY() - newPosition.getY();
		float d		= sqrt((dx * dx) + (dy * dy));
	
		if(d >= THRESHOLD)
		{
			markedForDelete = true;
		}
	}

	void PressAndHold::setMarkedForDelete(bool markedForDelete)
	{
		this->markedForDelete = markedForDelete;
	}

	void PressAndHold::setCompletedCallback(CompletedCallback completed)
	{
		this->completed = completed;
	}
}
