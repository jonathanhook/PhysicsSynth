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
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Joints/b2MouseJoint.h>
#include <Box2D/Dynamics/b2World.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <math.h>
#include "FingerJoint.h"
#include "Manager.h"
#include "SimpleObject.h"
#include "SoundEvent.h"

namespace PhysicsSynth
{
	/* Protected Constants */
	const float	SimpleObject::THUMBNAIL_SCALE = 0.3f;

	/* Constructors */
	SimpleObject::SimpleObject(bool isLocked, float size, SoundConfig *sound, float friction, float restitution) :
		PhysicsObject(isLocked, size, sound, friction, restitution)
	{
	}

	SimpleObject::~SimpleObject(void)
	{
	}

	/* Public Member Functions */
	void SimpleObject::fingerAdded(const FingerEventArgs &e)
	{
		if(selected != NULL)
		{
			selected(this);
		}
	}

	void SimpleObject::fingerUpdated(const FingerEventArgs &e)
	{
	}

	void SimpleObject::fingerRemoved(const FingerEventArgs &e)
	{
	}

	const Point2f &SimpleObject::getPosition(void)
	{
		b2Body *b = bodies[0];
		assert(b);

		const b2Vec2 wPos = b->GetPosition();
		position.setX(Manager::descale(wPos.x));
		position.setY(Manager::descale(wPos.y));

		return PhysicsObject::getPosition();
	}

	void SimpleObject::renderThumbnail(void)
	{
		b2Body *body = bodies[0];
		assert(body != NULL);

		float angle = body->GetAngle();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glScalef(THUMBNAIL_SCALE, THUMBNAIL_SCALE, 1.0f);
		glRotatef(angle * (180.0f / (float)M_PI), 0.0f, 0.0f, 1.0f);

		renderShape();

		glPopMatrix();
	}

	void SimpleObject::setPosition(const Point2f &position)
	{
		PhysicsObject::setPosition(position);

		b2Body *b = bodies[0];
		assert(b);

		b->SetTransform(b2Vec2(position.getX(), position.getY()), b->GetAngle());
	}

	void SimpleObject::update(void)
	{
	}

	/* Protected Member Functions */
	void SimpleObject::createFixture(b2Body &body, const b2Shape &shape)
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape		= &shape;	
		fixtureDef.density		= DENSITY;
		fixtureDef.friction		= friction;
		fixtureDef.restitution	= restitution * MAX_RESTITUTION;
		//fixtureDef.userData		= this;

		fixture = body.CreateFixture(&fixtureDef);
	}

	void SimpleObject::updateLockedMass(void)
	{
		if(isInWorld)
		{
			b2Body *body = bodies[0];
			assert(body);

			if(isLocked)
			{
				body->SetType(b2_staticBody);
			}
			else
			{
				body->SetType(b2_dynamicBody);
				body->ResetMassData();
			}
		}
	}

	void SimpleObject::updateFixtures(void)
	{
		assert(fixture);

		fixture->SetFriction(friction);
		fixture->SetRestitution(restitution * MAX_RESTITUTION);
	}
}
