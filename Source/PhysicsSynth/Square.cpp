/**
 * Class:	Square
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <assert.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLPrimitives.h>
#include <math.h>
#include "Manager.h"
#include "Square.h"

namespace PhysicsSynth
{
	/* Constructors */
	Square::Square(bool isStatic, float size, SoundConfig *sound, float friction, float restitution) :
		SimpleObject(isStatic, size, sound, friction, restitution)
	{	
	}

	Square::~Square(void)
	{
	}

	/* Public Member Functions */
	void Square::addToWorld(b2World *world, const Point2f &position)
	{
		PhysicsObject::addToWorld(world, position);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.getX(), position.getY());
		
		b2Body* body = world->CreateBody(&bodyDef);
		body->SetUserData((Square *)this);
		
		b2PolygonShape shape;
		setupShape(&shape);

		createFixture(*body, shape);
		bodies.push_back(body);

		updateLockedMass();
	}

	bool Square::contains(const FingerEventArgs &e) const
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

	PhysicsObject::PhysicsObjectType Square::getObjectType	(void) const
	{
		return PhysicsObject::SQUARE;
	}

	void Square::render(void)
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

		glRotatef(angle * (180.0f / (float)M_PI), 0.0f, 0.0f, 1.0f); // unsure how this will react with unscale etc..
		glScalef(rs, rs, 1.0f);

		renderShape();

		glPopMatrix();
	}

	void Square::setSize(float size)
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
	void Square::renderShape(void)
	{
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(-1.0f, -1.0f, 0.0f);
        glScalef(2.0f, 2.0f, 1.0f);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		assert(sound);
		const Colour3f sc = sound->getColour();
		glColor4f(sc.getR(), sc.getG(), sc.getB(), 0.5f);
        
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
			
        GLPrimitives::getInstance()->renderSquareOutline();

        glPopMatrix();
	}

	void Square::setupShape(b2Shape *shape)
	{
		float simSize = Manager::scale(getRenderSize());
		((b2PolygonShape *)shape)->SetAsBox(simSize, simSize);
	}
}
