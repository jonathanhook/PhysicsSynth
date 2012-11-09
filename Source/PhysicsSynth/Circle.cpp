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
#include <math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/GLVbo.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLPrimitives.h>
#include "Circle.h"
#include "Manager.h"

namespace PhysicsSynth
{
	/* Private Member Functions */
	const unsigned int	Circle::CIRCLE_VERTICES = 32;

	/* Constructors */
	Circle::Circle(bool isStatic, float size, SoundConfig *sound, float friction, float restitution) :
		SimpleObject(isStatic, size, sound, friction, restitution)
	{
        GLfloat centreLineVerts[6]
        {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f
        };
        centreLineVbo = new GLVbo(GL_LINES, GL_STATIC_DRAW, centreLineVerts, 2);
	}

	Circle::~Circle(void)
	{
        NDELETE(centreLineVbo);
	}

	/* Public Member Functions */
	void Circle::addToWorld(b2World *world, const Point2f &position)
	{
		PhysicsObject::addToWorld(world, position);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.getX(), position.getY());
		
		b2Body* body = world->CreateBody(&bodyDef);
		body->SetUserData((Circle *)this);
		
		b2CircleShape shape;
		setupShape(&shape);
		
		createFixture(*body, shape);
		bodies.push_back(body);
		
		updateLockedMass();
	}

	bool Circle::contains(const FingerEventArgs &e) const
	{
		if(isLocked)
		{
			assert(modelview != NULL);

			Point2f p = e.getPosition();
			modelview->unTranslatePoint(p);
			modelview->unScalePoint(p);

			float x	= p.getX();
			float y	= p.getY();
			float d	= sqrt((x * x) + (y * y));

			float fSize			= Manager::FINGER_SIZE;
			float renderSize	= getRenderSize();
			float scale			= modelview->getXScale();

			return d <= renderSize + (fSize / scale);
		}
		else
		{
			return false;
		}
	}

	PhysicsObject::PhysicsObjectType Circle::getObjectType(void) const
	{
		return PhysicsObject::CIRCLE;
	}

	void Circle::render(void)
	{
		b2Body *body = bodies[0];
		assert(body != NULL);

		float angle = body->GetAngle();
		float x		= Manager::descale(body->GetPosition().x);
		float y		= Manager::descale(body->GetPosition().y);
		float rs	= getRenderSize();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		saveTransform();
		
		glRotatef(angle * (180.0f / (float)M_PI), 0.0f, 0.0f, 1.0f);
		glScalef(rs, rs, 1.0f);

		renderShape();

		glPopMatrix();
	}

	void Circle::setSize(float size)
	{
		PhysicsObject::setSize(size);

		if(isInWorld)
		{
			assert(fixture);
			b2Body *body = fixture->GetBody();

			assert(body);
			body->DestroyFixture(fixture);

			b2CircleShape shape; 
			setupShape(&shape);

			createFixture(*body, shape);
		}
	}

	/* Private Member Functions */
	void Circle::renderShape(void)
	{
		assert(sound);
		const Colour3f &sc = sound->getColour();
		glColor4f(sc.getR(), sc.getG(), sc.getB(), 0.5f);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GLPrimitives::getInstance()->renderCircle();

		if(isSelected)
		{
			VALUE_COLOUR.use();
			glLineWidth(2.0f);
		}
		else
		{
			sound->getColour().use();
			glLineWidth(1.0f);
		}
        
        GLPrimitives::getInstance()->renderCircleOutline();
        
        assert(centreLineVbo);
        centreLineVbo->render();
        
        glDisable(GL_BLEND);
        glDisable(GL_LINE_SMOOTH);
	}

	void Circle::setupShape(b2Shape *shape)
	{
		shape->m_radius = Manager::scale(getRenderSize());
	}
}