/**
 * Class:	Wheel
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Joints/b2RevoluteJoint.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <math.h>
#include "LoopPointer.h"
#include "Manager.h"
#include "Wheel.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float				Wheel::BOUNDS_OPACITY		= 0.5f;
	const unsigned int		Wheel::CIRCLE_VERTICES		= 32;
	const float				Wheel::HUB_RADIUS			= 0.1f;
	const unsigned short	Wheel::LINE_PATTERN			= 0xAAAA;
	const int				Wheel::LINE_STIPPLE_FACTOR	= 5;
	const float				Wheel::MAX_SPOKE_RAD		= 0.049f;
	const float				Wheel::MIN_SPOKE_RAD		= 0.015f;
	const float				Wheel::SPOKE_END			= 0.1f;
	const float				Wheel::SPOKE_OPACITY		= 0.66f;
	const std::string		Wheel::TEXTURE_PATH			= "../../../Data/Textures/Wheel/wheel.tga";

	/* Constructors */
	Wheel::Wheel(float rate, unsigned int pattern, float size, SoundConfig *sound) :
		DynamicObject(TEXTURE_PATH, rate, pattern, size, sound)
	{
		body		= NULL;
		boundsDl	= -1;
		spokeAngle	= 0.0f;
		spokeDl		= -1;
	}

	Wheel::~Wheel(void)
	{
	}

	/* Public Member Functions */
	void Wheel::addToWorld(b2World *world, const Point2f &position)
	{
		DynamicObject::addToWorld(world, position);
		
		float px = position.getX();
		float py = position.getY();

		b2BodyDef bd;
		bd.position.Set(px, py);

		body = world->CreateBody(&bd);
		body->SetUserData((PhysicsObject *)this);
		bodies.push_back(body);

		initSpokes();

		if(translate != NULL)
		{
			translate(this, getPosition());
		}
	}

	float Wheel::getBoundingRegion(void) const
	{
		return Manager::scale(getSpokeRad());
	}

	PhysicsObject::PhysicsObjectType Wheel::getObjectType(void) const
	{
		return WHEEL;
	}

	void Wheel::render(void)
	{
		DynamicObject::render();
		
		float x = position.getX();
		float y = position.getY();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x, y, 0.0f);

		renderBounds();
		renderSpokes();

		glPopMatrix();
	}

	void Wheel::setPattern(unsigned int pattern)
	{
		DynamicObject::setPattern(pattern);

		if(isInWorld)
		{
			initSpokes();
		}
	}

	void Wheel::setPosition(const Point2f &position)
	{
		PhysicsObject::setPosition(position);

		if(isInWorld)
		{
			updateSpokePos(position);
		}
	}

	void Wheel::setSize(float size)
	{
		float oldSize	= this->size;
		
		PhysicsObject::setSize(size);

		if(oldSize < size && translate != NULL)
		{
			translate(this, getPosition());
		}

		if(isInWorld)
		{
			initSpokes();
		}
	}

	void Wheel::update(void)
	{
		DynamicObject::update();

		updateSpokeAngle(loop->getLoopPosition() * (2.0f * (float)M_PI));
	}

	/* Private Member Functions */
	float Wheel::getSpokeRad(void) const
	{
		return (size * (MAX_SPOKE_RAD - MIN_SPOKE_RAD)) + MIN_SPOKE_RAD;
	}

	void Wheel::initSpokes(void)
	{
		assert(body);

		// if update, destroy the old fixture
		for(unsigned int i = 0; i < fixtures.size(); i++)
		{
			b2Fixture *f = fixtures[i];
			assert(f);

			body->DestroyFixture(f);
		}
		fixtures.clear();
	
		float angleIncrement	= (2.0f * (float)M_PI) / (float)PATTERN_LENGTH;
		float spokeRad			= Manager::scale(getSpokeRad());

		b2PolygonShape spokeShape;
		for(unsigned int i = 0; i < PATTERN_LENGTH; i++)
		{
			if(pattern & 1 << i)
			{
				float theta = (float)i * angleIncrement;
				float x		= cos(theta) * spokeRad;
				float y		= sin(theta) * spokeRad;

				spokeShape.SetAsEdge(b2Vec2(0.0f, 0.0f), b2Vec2(x, y));

				b2FixtureDef fixtureDef;
				fixtureDef.shape	= &spokeShape;	
				fixtureDef.density	= 0.0f;

				fixtures.push_back(body->CreateFixture(&fixtureDef));
			}
		}
	}

	void Wheel::renderSpokes(void)
	{
		float angleIncrement	= 360.0f / (float)PATTERN_LENGTH;
		float spokeRad			= getSpokeRad();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotatef(spokeAngle * (180.0f / (float)M_PI), 0.0f, 0.0f, 1.0f);

		const Colour3f &c = sound->getColour();
		glColor4f(c.getR(), c.getG(), c.getB(), SPOKE_OPACITY);

		for(unsigned int i = 0; i < PATTERN_LENGTH; i++)
		{
			if(pattern & 1 << i)
			{
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glRotatef(angleIncrement * (float)i, 0.0f, 0.0f, 1.0f);
				glTranslatef(ICON_SIZE, 0.0f, 0.0f);
				glScalef(spokeRad - ICON_SIZE, spokeRad - ICON_SIZE, 1.0f);

				if(spokeDl == -1)
				{
					spokeDl = glGenLists(1);
					glNewList(spokeDl, GL_COMPILE);

					glPushAttrib(GL_ENABLE_BIT);
					glEnable(GL_BLEND);
					glEnable(GL_LINE_SMOOTH);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glLineWidth(2.0f);
					glBegin(GL_LINE_STRIP);
						glVertex3f(SPOKE_END, 0.0f, 0.0f);
						glVertex3f(1.0f - SPOKE_END, 0.0f, 0.0f);
					glEnd();

					glPopAttrib();
					glEndList();
				}
				glCallList(spokeDl);

				glPopMatrix();
			}
		}

		glPopMatrix();
	}

	void Wheel::renderBounds(void)
	{
		float spokeRad = getSpokeRad();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glScalef(spokeRad, spokeRad, 1.0f);

		if(boundsDl == -1)
		{
			boundsDl = glGenLists(1);
			glNewList(boundsDl, GL_COMPILE);
			
			glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_LINE_STIPPLE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glLineStipple(LINE_STIPPLE_FACTOR, LINE_PATTERN);
			glLineWidth(1.0f);
			glColor4f(1.0f, 1.0f, 1.0f, BOUNDS_OPACITY);
			glBegin(GL_LINE_STRIP);
				float angleIncrement = ((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES;
				for(unsigned int i = 0; i <= CIRCLE_VERTICES; i++)
				{
					float theta = angleIncrement * (float)i; 
					float px	= cos(theta) * 1.0f;
					float py	= sin(theta) * 1.0f;

					glVertex3f(px, py, 0.0f);
				}
			glEnd();

			glPopAttrib(); // GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT
			glEndList();
		}
		glCallList(boundsDl);

		glPopMatrix();
	}

	void Wheel::onPatternTick(void)
	{

	}

	void Wheel::updateSpokeAngle(float angle)
	{
		spokeAngle = angle;

		assert(body);
		body->SetTransform(body->GetPosition(), spokeAngle);
	}

	void Wheel::updateSpokePos(const Point2f &position)
	{
		assert(body);
		body->SetTransform(b2Vec2(Manager::scale(position.getX()), Manager::scale(position.getY())), spokeAngle);
	}

	void Wheel::updateFixtures(void)
	{

	}
}
