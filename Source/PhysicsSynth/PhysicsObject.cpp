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
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <math.h>
#include <JDHUtility/Ndelete.h>
#include "FingerJoint.h"
#include "Manager.h"
#include "PhysicsObject.h"
#include "SoundEvent.h"

namespace PhysicsSynth
{
	/* Protected Constants */
	const float		PhysicsObject::DENSITY				= 1.0f;
	const float		PhysicsObject::DEFAULT_FRICTION		= 0.5f;
	const bool		PhysicsObject::DEFAULT_IS_LOCKED	= false;
	const float		PhysicsObject::DEFAULT_RESTITUTION	= 0.5f;
	const float		PhysicsObject::DEFAULT_SIZE			= 0.5f;
	const float		PhysicsObject::MAX_RESTITUTION		= 0.9f;
	const float		PhysicsObject::MAX_SIZE				= 0.025f;
	const float		PhysicsObject::MIN_SIZE				= 0.0025f;
	const Colour4f	PhysicsObject::VALUE_COLOUR			= Colour4f(0.11f, 0.53f, 0.71f, 1.0f);

	/* Constructors */
	PhysicsObject::PhysicsObject(bool isLocked, float size, SoundConfig *sound, float friction, float restitution)
	{
		this->isLocked		= isLocked;
		this->size			= size;
		this->sound			= sound;
		this->friction		= friction;
		this->restitution	= restitution;

		collided			= false;
		cx					= 0.0f;
		cy					= 0.0f;
		isInWorld			= false;
		isMarkedForDelete	= false;
		isSelected			= false;
		lastSoundImpulse	= 0.0f;
		modelview			= new GLMatrixf();
		selected			= NULL;
		soundEvent			= NULL;
		translate			= NULL;
		world				= NULL;
	}

	PhysicsObject::~PhysicsObject(void)
	{
		// if the object has been initiaised in a world then Box2D delete
		if(isInWorld)
		{
			assert(world != NULL);

			for(unsigned int i = 0; i < bodies.size(); i++)
			{
				b2Body *body = bodies[i];
				assert(body != NULL);

				world->DestroyBody(body);
			}
			bodies.clear();
		}
	}

	/* Public Member Functions */
	void PhysicsObject::addToWorld(b2World *world, const Point2f &position)
	{
		assert(!isInWorld);

		this->world		= world;
		this->position	= Manager::descale(position); // in the case of dynamic objects position is stored as the initial position in the world and never updated

		isInWorld	= true;
	}

	void PhysicsObject::collide(b2Body *cb, float cx, float cy)
	{
		collided = true;
		this->cx = cx;
		this->cy = cy;
	}

	float PhysicsObject::getBoundingRegion(void) const
	{
		return getRenderSize();
	}

	float PhysicsObject::getFriction(void) const
	{
		return friction;
	}

	bool PhysicsObject::getIsLocked(void) const
	{
		return isLocked;
	}
	
	bool PhysicsObject::getIsSelected(void) const
	{
		return isSelected;
	}

	bool PhysicsObject::getIsMarkedForDelete(void) const
	{
		return isMarkedForDelete;
	}

	float PhysicsObject::getLastSoundImpulse(void) const
	{
		return lastSoundImpulse;
	}

	const Point2f &PhysicsObject::getPosition(void)
	{
		return position;
	}

	float PhysicsObject::getRenderSize(void) const
	{
		return MIN_SIZE + (size * MAX_SIZE);
	}

	float PhysicsObject::getRestitution(void) const
	{
		return restitution;
	}

	float PhysicsObject::getSize(void) const
	{
		return size;
	}

	SoundConfig *PhysicsObject::getSound(void) const
	{
		return sound;
	}

	void PhysicsObject::selectFromMenu(void)
	{
		if(selected != NULL)
		{
			selected(this);
		}
	}
	
	void PhysicsObject::setFriction(float friction)
	{
		this->friction = friction;

		if(isInWorld)
		{
			updateFixtures();
		}
	}
	
	void PhysicsObject::setIsLocked(bool isLocked)
	{
		this->isLocked = isLocked;
		updateLockedMass();
	}
	
	void PhysicsObject::setIsSelected(bool isSelected)
	{
		this->isSelected = isSelected;
	}

	void PhysicsObject::setLastSoundImpulse(float lastSoundImpulse)
	{
		this->lastSoundImpulse = lastSoundImpulse;
	}

	void PhysicsObject::setPosition(const Point2f &position)
	{
		this->position = position;
	}

	void PhysicsObject::setRestitution(float restitution)
	{
		this->restitution = restitution;

		if(isInWorld)
		{
			updateFixtures();
		}
	}


	void PhysicsObject::setIsMarkedForDelete(bool isMarkedForDelete)
	{
		// HACK: no delete when captured
		bool capped = !this->isCaptured();
		this->isMarkedForDelete = (isMarkedForDelete && capped);
	}

	void PhysicsObject::setSelectedCallback(SelectedCallback selected)
	{
		this->selected = selected;
	}

	void PhysicsObject::setSize(float size)
	{
		this->size = size;
	}

	void PhysicsObject::setSound(SoundConfig *sound)
	{
		this->sound = sound;
	}

	void PhysicsObject::setSoundEventCallback(SoundEventCallback soundEvent)
	{
		this->soundEvent = soundEvent;
	}

	void PhysicsObject::setTranslateCallback(TranslateCallback translate)
	{
		this->translate = translate;
	}

	/* Protected Member Functions */
	void PhysicsObject::saveTransform(void)
	{
		assert(modelview != NULL);
		glGetFloatv(GL_MODELVIEW_MATRIX, modelview->getMatrix());
	}
}
