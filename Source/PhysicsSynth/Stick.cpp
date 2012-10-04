/**
 * Class:	Stick
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLPrimitives.h>
#include <math.h>
#include "Manager.h"
#include "Stick.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float Stick::STICK_THICKNESS = 0.002f;

	/* Constructors */
	Stick::Stick(bool isStatic, float size, SoundConfig *sound, float friction, float restitution) :
		SimpleObject(isStatic, size, sound, friction, restitution)
    {
	}

	Stick::~Stick(void)
	{
	}

	/* Public Member Functions */
	void Stick::addToWorld(b2World *world, const Point2f &position)
	{
		PhysicsObject::addToWorld(world, position);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.getX(), position.getY());
		
		b2Body* body = world->CreateBody(&bodyDef);
		body->SetUserData((Stick *)this);
		
		b2PolygonShape shape;
		setupShape(&shape);

		createFixture(*body, shape);
		bodies.push_back(body);

		updateLockedMass();
	}

	bool Stick::contains(const FingerEventArgs &e) const
	{
		if(isLocked)
		{
			return false;
		}
		else
		{
			return false;
		}
	}
	
	PhysicsObject::PhysicsObjectType Stick::getObjectType(void) const
	{
		return PhysicsObject::STICK;
	}
	
	void Stick::render(void)
	{
		b2Body *body = bodies[0];
		assert(body != NULL);

		float angle = body->GetAngle();
		float x		= Manager::descale(body->GetPosition().x);
		float y		= Manager::descale(body->GetPosition().y);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		saveTransform();

		glRotatef(angle * (180.0f / (float)M_PI), 0.0f, 0.0f, 1.0f); // unsure how this will react with unscale etc..

		renderShape();

		glPopMatrix();
	}

	void Stick::renderThumbnail(void)
	{

	}

	void Stick::setSize(float size)
	{
		PhysicsObject::setSize(size);

		if(isInWorld)
		{
			assert(fixture);
			b2Body *body = fixture->GetBody();

			assert(body);
			body->DestroyFixture(fixture);

			b2PolygonShape shape; 
			setupShape(&shape);

			createFixture(*body, shape);
		}
	}

	/* Private Member Functions */
	void Stick::renderShape(void)
	{
		float w	= getRenderSize();
		float h	= STICK_THICKNESS;
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(w, h, 1.0f);

		assert(sound);
		const Colour3f sc = sound->getColour();
		glColor4f(sc.getR(), sc.getG(), sc.getB(), 0.5f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GLPrimitives::getInstance()->renderSquare();
        
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

        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
        GLPrimitives::getInstance()->renderSquareOutline();

        glPopMatrix();
	}
	
	void Stick::setupShape(b2Shape *shape)
	{
		float w = Manager::scale(getRenderSize());
		float h = Manager::scale(STICK_THICKNESS);
		((b2PolygonShape *)shape)->SetAsBox(w, h);
	}
}
