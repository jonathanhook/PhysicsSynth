/**
 * Class:	Triangle
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
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLVbo.h>
#include <math.h>
#include <JDHUtility/Vector2f.h>
#include "Manager.h"
#include "Triangle.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float Triangle::THUMBNAIL_SCALE = 1.0f;

	/* Constructors */
	Triangle::Triangle(bool isStatic, float size, SoundConfig *sound, float friction, float restitution) :
		SimpleObject(isStatic, size, sound, friction, restitution)
	{
        fill    = NULL;
        outline = NULL;
	}

	Triangle::~Triangle(void)
	{
        NDELETE(fill);
        NDELETE(outline);
	}

	/* Public Member Functions */
	void Triangle::addToWorld(b2World *world, const Point2f &position)
	{
		PhysicsObject::addToWorld(world, position);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.getX(), position.getY());
		
		b2Body* body = world->CreateBody(&bodyDef);
		body->SetUserData((Triangle *)this);
		
		b2PolygonShape shape;
		setupShape(&shape);
		
		createFixture(*body, shape);
		bodies.push_back(body);

		updateLockedMass();
	}

	bool Triangle::contains(const FingerEventArgs &e) const
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

			/*b2Body *body = bodies[0];
			assert(body != NULL);
			assert(modelview != NULL);

			Point2f p	= e.getPosition();
			float angle	= body->GetAngle();

			modelview->unTranslatePoint(p);
			modelview->unScalePoint(p);
			p.rotate(-angle);

			return barrycentricInclusion(p, points[0], points[1], points[2]);*/
		}
		else
		{
			return false;
		}
	}

	PhysicsObject::PhysicsObjectType Triangle::getObjectType(void) const
	{
		return PhysicsObject::TRIANGLE;
	}

	void Triangle::render(void)
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

	void Triangle::setSize(float size)
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
	bool Triangle::barrycentricInclusion(const Point2f &p, const Point2f &a, const Point2f &b, const Point2f &c) const
	{
		// Compute vectors        
		Vector2f v0(c.getX() - a.getX(), c.getY() - a.getY());
		Vector2f v1(b.getX() - a.getX(), b.getY() - a.getY());
		Vector2f v2(p.getX() - a.getX(), p.getY() - a.getY());

		// Compute dot products
		float dot00 = v0.getDotProduct(v0);
		float dot01 = v0.getDotProduct(v1);
		float dot02 = v0.getDotProduct(v2);
		float dot11 = v1.getDotProduct(v1);
		float dot12 = v1.getDotProduct(v2);

		// Compute barycentric coordinates
		float invDenom	= 1.0f / (dot00 * dot11 - dot01 * dot01);
		float u			= (dot11 * dot02 - dot01 * dot12) * invDenom;
		float v			= (dot00 * dot12 - dot01 * dot02) * invDenom;

		// Check if point is in triangle
		return (u > 0) && (v > 0) && (u + v < 1);
	}

	void Triangle::initPoints(void)
	{
		float rs = getRenderSize();

		points[0].setX(cos(-((float)M_PI * 0.5f)) * rs);
		points[0].setY(sin(-((float)M_PI * 0.5f)) * rs);

		points[1].setX(cos((float)M_PI * 0.16f) * rs);
		points[1].setY(sin((float)M_PI * 0.16f) * rs);
	
		points[2].setX(cos((float)M_PI * 0.83f) * rs);
		points[2].setY(sin((float)M_PI * 0.83f) * rs);

        
        GLfloat verts[9] =
        {
            points[0].getX(), points[0].getY(), 0.0f,
            points[1].getX(), points[1].getY(), 0.0f,
            points[2].getX(), points[2].getY(), 0.0f
        };
        
        if(fill == NULL && outline == NULL)
        {
            fill    = new GLVbo(GL_TRIANGLES, GL_DYNAMIC_DRAW, verts, 3);
            outline = new GLVbo(GL_LINE_LOOP, GL_DYNAMIC_DRAW, verts, 3);
        }
        else
        {
            fill->update(GL_TRIANGLES, GL_DYNAMIC_DRAW, verts, 3);
            outline->update(GL_LINE_LOOP, GL_DYNAMIC_DRAW, verts, 3);
        }
	}

	void Triangle::renderShape(void)
	{
		glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
		
		assert(sound);
		const Colour3f &sc = sound->getColour();
		glColor4f(sc.getR(), sc.getG(), sc.getB(), 0.5f);

        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        assert(fill);
        fill->render();

        glPopAttrib(); // GL_ENABLE_BIT

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

        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
        assert(outline);
        outline->render();

        glPopAttrib(); // GL_ENABLE_BIT
		glPopAttrib(); // GL_CURRENT_BIT | GL_LINE_BIT
	}

	void Triangle::renderThumbnail(void)
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

	void Triangle::setupShape(b2Shape *shape)
	{
		initPoints();

		b2Vec2 verts[3];
		for(unsigned int i = 0; i < 3; i++)
		{
			Point2f p = Manager::scale(points[i]);
			verts[i].Set(p.getX(), p.getY());
		}
		((b2PolygonShape *)shape)->Set(verts, 3);
	}
}
