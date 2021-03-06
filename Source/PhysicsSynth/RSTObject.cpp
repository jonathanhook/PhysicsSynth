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
#define _USE_MATH_DEFINES
#include <assert.h>
#include <JDHUtility/OpenGL.h>
#include <math.h>
#include <JDHUtility/Ndelete.h>
#include "RSTObject.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float RSTObject::MAX_SCALE	= 3.0f;
	const float RSTObject::MIN_SCALE	= 1.0f;

	/* Constructors */
	RSTObject::RSTObject(bool rotateEnabled, bool scaleEnabled, bool translateEnabled)
	{
		this->rotateEnabled		= rotateEnabled;
		this->scaleEnabled		= scaleEnabled;
		this->translateEnabled	= translateEnabled;

		scale = 1.0f;
		
		setTransformToIdentity();
	}

	RSTObject::~RSTObject(void)
	{
		std::map<int, Finger *>::iterator it;
		for(it = fingers.begin(); it != fingers.end(); it++)
		{
			NDELETE((*it).second);
		}
		fingers.clear();
	}

	/* Public Member Functions */
	void RSTObject::debugScale(float z, const Point2f &p)
	{
		float px = p.getX();
		float py = p.getY();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(px, py, 0.0f);
		glScalef(z, z, z);
		glTranslatef(-px, -py, 0.0f);
		glMultMatrixf(transform);
		glGetFloatv(GL_MODELVIEW_MATRIX, transform);
		glPopMatrix();
	}

	void RSTObject::fingerAdded(const FingerEventArgs &e)
	{
		Finger *f = new Finger(e.getId(), e.getPosition());
		fingers[e.getId()] = f;
	}

	void RSTObject::fingerUpdated(const FingerEventArgs &e)
	{
		unsigned int pId	= e.getId();

		if(fingers.count(pId) > 0)
		{
			Point2f p = e.getPosition();

			Finger *f = fingers[pId];
			assert(f != NULL);

			f->updatePosition(p);

			if(fingers.size() == 1)
			{
				translate(*f);
			}
			else if(fingers.size() == 2)
			{
				Finger *f1 = findOtherFinger(pId);
				rst(*f, *f1);
			}
		}
	}
	
	void RSTObject::fingerRemoved(const FingerEventArgs &e)
	{
		unsigned int pId = e.getId();

		if(fingers.size() > 0 && fingers.count(pId) > 0)
		{
			NDELETE(fingers[pId]);
			fingers.erase(pId);
		}
	}

	bool RSTObject::isRotateEnabled(void) const
	{
		return rotateEnabled;
	}

	bool RSTObject::isScaleEnabled(void) const
	{
		return scaleEnabled;
	}
	
	bool RSTObject::isTranslateEnabled(void) const
	{
		return translateEnabled;
	}

	void RSTObject::setRotateEnabled(bool rotateEnabled)
	{
		this->rotateEnabled = rotateEnabled;
	}

	void RSTObject::setScaleEnabled(bool scaleEnabled)
	{
		this->scaleEnabled = scaleEnabled;
	}

	void RSTObject::setTranslateEnabled(bool translateEnabled)
	{
		this->translateEnabled = translateEnabled;
	}

	/* Protected Member Functions */
	void RSTObject::scaleChanged(void)
	{

	}

	/* Private Member Functions */
	Finger *RSTObject::findOtherFinger(unsigned int fId) const
	{
		Finger *other = NULL;

		std::map<int, Finger *>::const_iterator it;
		for(it = fingers.begin(); it != fingers.end(); it++)
		{
			int key = (*it).first;
			Finger *value = (*it).second;
			assert(value != NULL);

			if(key != fId) 
			{
				other = value;
			}
		}

		assert(other != NULL);
		return other;
	}

	void RSTObject::rst(const Finger &actuator, const Finger &anchor)
	{
		float centreX	= anchor.getPosition().getX();
		float centreY	= anchor.getPosition().getY();

		const Point2f	&actuatorPos	= actuator.getPosition();
		float			actuatorX		= actuatorPos.getX();
		float			actuatorY		= actuatorPos.getY();

		const Point2f	&actuatorLast	= actuator.getLastPosition();
		float			actuatorLastX	= actuatorLast.getX();
		float			actuatorLastY	= actuatorLast.getY();

		Vector2f v0(actuatorLastX - centreX, actuatorLastY - centreY);
		Vector2f v1(actuatorX - centreX, actuatorY - centreY);

		float scaleFactor	= v1.getScaleFactor(v0);
		// TODO: implement rotation
		//float theta			= v0.getAngle(v1);

		if((scale * scaleFactor >= MIN_SCALE) && (scale * scaleFactor <= MAX_SCALE))
		{
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(centreX, centreY, 0.0f);

			if(scaleEnabled)
			{
				glScalef(scaleFactor, scaleFactor, 1.0f);
			}

			if(rotateEnabled)
			{
				// TODO: implement rotation
				//glRotatef(theta * (180.0f / M_PI), 0.0f, 0.0f, 1.0f);
			}

			glTranslatef(-centreX, -centreY, 0.0f);

			glMultMatrixf(transform);
			glGetFloatv(GL_MODELVIEW_MATRIX, transform);
			glPopMatrix();

			scale *= scaleFactor;
			scaleChanged();
		}
	}

	void RSTObject::setTransformToIdentity(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX, transform);
		glPopMatrix();
	}

	void RSTObject::translate(const Finger &actuator)
	{
		translate(actuator.getDelta());
	}

	void RSTObject::translate(const Vector2f &delta)
	{
		float dx = delta.getX();
		float dy = delta.getY();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(dx, dy, 0.0f);
		glMultMatrixf(transform);
		glGetFloatv(GL_MODELVIEW_MATRIX, transform);
		glPopMatrix();
	}
}
