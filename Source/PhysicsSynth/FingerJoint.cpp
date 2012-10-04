/**
 * Class:	FingerJoint
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
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
