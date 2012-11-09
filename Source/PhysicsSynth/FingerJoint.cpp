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
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Joints/b2MouseJoint.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLVbo.h>
#include "FingerJoint.h"
#include "Manager.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float		FingerJoint::END_POINT_SIZE	= 2.0f;
	const Colour4f	FingerJoint::VALUE_COLOUR	= Colour4f(0.11f, 0.53f, 0.71f, 1.0f);

	/* Constructors */
	FingerJoint::FingerJoint(PhysicsObject *object, b2Body *body, const b2Vec2 &target, b2World *world)
	{
		this->object	= object;
		this->body		= body;
		this->world		= world;
        
        GLfloat dummyVertices[6];
        pointVbo = new GLVbo(GL_POINTS, GL_DYNAMIC_DRAW, dummyVertices, 2);
        lineVbo = new GLVbo(GL_POINTS, GL_DYNAMIC_DRAW, dummyVertices, 2);

		init(target);
	}

	FingerJoint::~FingerJoint(void)
	{
		// Box2D delete
		world->DestroyJoint(joint);
		world->DestroyBody(groundBody);
	}

	/* Public Member Functions */
	const b2Body *FingerJoint::getBody(void) const
	{
		return body;
	}

	PhysicsObject *FingerJoint::getObject(void) const
	{
		return object;
	}

	void FingerJoint::render(void)
	{
		b2Vec2 p1 = joint->GetAnchorB();
		b2Vec2 p2 = joint->GetTarget();

		float p1x = Manager::descale(p1.x);
		float p1y = Manager::descale(p1.y);
		float p2x = Manager::descale(p2.x);
		float p2y = Manager::descale(p2.y);

		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glLineWidth(1.0f);
		
		VALUE_COLOUR.use();

        GLfloat vertices[6] =
        {
            p1x, p1y, 0.0f,
            p2x, p2y, 0.0f
        };
        
        pointVbo->update(GL_POINTS, GL_DYNAMIC_DRAW, vertices, 2);
        lineVbo->update(GL_LINES, GL_DYNAMIC_DRAW, vertices, 2);
        
        pointVbo->render();
        lineVbo->render();
        
        glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
	}

	void FingerJoint::updateTarget(const b2Vec2 &target)
	{
		joint->SetTarget(target);
	}

	/* Private Member Functions */
	void FingerJoint::init(const b2Vec2 &target)
	{
		b2BodyDef bodyDef;
		groundBody = world->CreateBody(&bodyDef);

		b2MouseJointDef md;
		md.bodyA	= groundBody;
		md.bodyB	= body;
		md.target	= target;
		md.maxForce = 1000.0f * body->GetMass();
		joint		= (b2MouseJoint *)world->CreateJoint(&md);
		
		body->SetAwake(true);
	}		
}
