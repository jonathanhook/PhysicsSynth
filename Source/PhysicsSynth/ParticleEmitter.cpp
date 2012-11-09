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
#include <assert.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/GLVbo.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLTexture.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/PointInclusion.h>
#include <JDHUtility/GLPrimitives.h>
#include <stdlib.h>
#include "Finger.h"
#include "Manager.h"
#include "ParticleEmitter.h"
#include "SoundEvent.h"
#include "Synchronizer.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int	ParticleEmitter::CIRCLE_VERTICES	= 16;
	const Vector2f		ParticleEmitter::DEFAULT_IMPULSE	= Vector2f(0.5f, 0.0f);
	const float			ParticleEmitter::DEFAULT_LIFESPAN	= 0.5f;
	const unsigned int	ParticleEmitter::LIFESPAN_BARS		= 4;
	const float			ParticleEmitter::MAX_IMPULSE		= 1.0f;
	const float			ParticleEmitter::MAX_PARTICLE_SIZE	= 0.0075f;
	const float			ParticleEmitter::MIN_PARTICLE_SIZE	= 0.0001f;
	const std::string	ParticleEmitter::TEXTURE_PATH		= "emitter.tga";

	/* Private Static Member Variables */
	unsigned int ParticleEmitter::globalParticleCounter = 0;

	/* Constructors */
	ParticleEmitter::ParticleEmitter(const Vector2f &impulse, float lifespan, float rate, unsigned int pattern, float size, SoundConfig *sound, float friction, float restitution) :
		DynamicObject(TEXTURE_PATH, rate, pattern, size, sound, friction, restitution)
	{
		this->impulse	= impulse;
		this->lifespan	= lifespan;

		particlePtr	= 0;
        
        GLfloat centreLineVerts[6]
        {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f
        };
        centreLineVbo = new GLVbo(GL_LINES, GL_STATIC_DRAW, centreLineVerts, 2);
	}

	ParticleEmitter::~ParticleEmitter(void)
	{
		for(unsigned int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			Particle *p = &particles[i];
			assert(p);

			if(p->body != NULL)
			{
				world->DestroyBody(p->body);
			}
		}
        
        NDELETE(centreLineVbo);
	}

	/* Public Member Functions */
	void ParticleEmitter::addToWorld(b2World *world, const Point2f &position)
	{
		DynamicObject::addToWorld(world, position);
		initParticles();
	}

	void ParticleEmitter::collide(b2Body *cb, float cx, float cy)
	{
		for(unsigned int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			Particle *p = &particles[i];
			
			if(p->active && p->body == cb)
			{
				p->collided = true;
				p->cx = cx;
				p->cy = cy;
			}
		}
	}

	const Vector2f &ParticleEmitter::getImpulse(void) const
	{
		return impulse;
	}

	float ParticleEmitter::getLifespan(void) const
	{
		return lifespan;
	}

	PhysicsObject::PhysicsObjectType ParticleEmitter::getObjectType(void) const
	{
		return PhysicsObject::PARTICLES;
	}

	void ParticleEmitter::render(void)
	{
		renderParticles();
		DynamicObject::render();	
	}

	void ParticleEmitter::setImpulse(const Vector2f &impulse)
	{
		this->impulse = impulse;
	}

	void ParticleEmitter::setLifespan(float lifespan)
	{
		this->lifespan = lifespan;
	}

	void ParticleEmitter::update(void)
	{
		DynamicObject::update();
		updateParticles();
	}

	/* Private Member Functions */
	void ParticleEmitter::addParticle(void)
	{
		if(globalParticleCounter < MAX_PARTICLE_COUNT)
		{
			Particle *p = &particles[particlePtr++ % MAX_PARTICLE_COUNT];
			assert(p);

			p->active	= true;
			p->collided = false;
			p->created	= CrossPlatformTime::getTimeMillis();
			p->cx		= 0.0f;
			p->cy		= 0.0f;
			p->lifespan	= getLifespanMs();
			p->size		= getNewParticleSize();

			b2Body *body = p->body;
			assert(body);

			// update fixture
			b2Fixture *fixture = p->fixture;
			assert(fixture);

			fixture->SetDensity(DENSITY);
			fixture->SetFriction(friction);
			fixture->SetRestitution(restitution * MAX_RESTITUTION);

			float newSize			= Manager::scale(p->size);
			const b2Shape *shape	= fixture->GetShape();
			assert(shape);

			if(shape->m_radius != newSize)
			{
				body->DestroyFixture(fixture);

				b2CircleShape shape;
				shape.m_radius = newSize;

				b2FixtureDef fixtureDef;
				fixtureDef.shape		= &shape;	
				fixtureDef.density		= DENSITY;
				fixtureDef.friction		= friction;
				fixtureDef.restitution	= restitution * MAX_RESTITUTION;
				fixtureDef.userData		= this;
                
                fixture = body->CreateFixture(&fixtureDef);
			}

			// bring into world and force
			Point2f wp = Manager::scale(position);
			body->SetTransform(b2Vec2(wp.getX(), wp.getY()), 0.0f);
			body->SetActive(true);
			body->ApplyForce(getInitialImpulse(body->GetMass()), b2Vec2(0.0f, 0.0f));
			
			globalParticleCounter++;
		}
	}

	b2Vec2 ParticleEmitter::getInitialImpulse(float mass) const
	{
		float ix = impulse.getX();
		float iy = impulse.getY();

		ix *= MAX_IMPULSE;
		iy *= MAX_IMPULSE;

		ix *= (mass * 10.0f);
		iy *= (mass * 10.0f);

		ix = Manager::scale(ix);
		iy = Manager::scale(iy);

		return b2Vec2(ix, iy);
	}

	unsigned int ParticleEmitter::getLifespanMs(void) const
	{
		Synchronizer *s = Synchronizer::getInstance();
		assert(s);

		float maxLifespan = s->getOneBarMs() * (float)LIFESPAN_BARS;
		return (unsigned int)(lifespan * maxLifespan);
	}

	float ParticleEmitter::getNewParticleSize(void) const
	{
		return (size * (MAX_PARTICLE_SIZE - MIN_PARTICLE_SIZE)) + MIN_PARTICLE_SIZE; 
	}

	SoundEvent *ParticleEmitter::getSoundEvents(bool &isArray, unsigned int &count)
	{
/*		count				= particleCount;
		SoundEvent *sEvents = new SoundEvent[count];

		unsigned int pf = 0;
		for(unsigned int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			Particle *p		= &particles[i];
			
			if(p->active)
			{
				b2Body *body	= p->body;
				assert(body);

				SoundEvent::SoundEventType type;
				if(p->collided)
				{
					type = SoundEvent::COLLISION;
				}
				else if(body->IsAwake())
				{
					type = SoundEvent::MOVEMENT;
				}
				else
				{
					type = SoundEvent::POSITION;
				}

				populateSoundEvent(type, p->cx, p->cy, &sEvents[pf], p->body);

				p->collided = false;	
				pf++;
			}
		}
		assert(pf == count);

		isArray = true;
		return sEvents;
*/
		count = 0;
		isArray = false;
		return NULL;
	}

	void ParticleEmitter::initParticles(void)
	{
		for(unsigned int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			Particle *p = &particles[i];
			assert(p);
			assert(world);

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;

			Point2f wp = Manager::scale(position);
			bodyDef.position.Set(wp.getX(), wp.getY());

			b2Body* body = world->CreateBody(&bodyDef);
			body->SetUserData((ParticleEmitter *)this);

			b2CircleShape shape;
			shape.m_radius = Manager::scale(getNewParticleSize());

			b2FixtureDef fixtureDef;
			fixtureDef.shape		= &shape;	
			fixtureDef.density		= DENSITY;
			fixtureDef.friction		= friction;
			fixtureDef.restitution	= restitution * MAX_RESTITUTION;
			fixtureDef.userData		= this;

			b2Fixture *fixture = body->CreateFixture(&fixtureDef);
			bodies.push_back(body);
			
			body->SetActive(false);

			p->fixture	= fixture;
			p->body		= body;
		}
	}

	void ParticleEmitter::onPatternTick(void)
	{
		addParticle();
	}

	void ParticleEmitter::renderParticles(void)
	{
		unsigned int now = CrossPlatformTime::getTimeMillis();
		for(unsigned int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			Particle *p = &particles[i];
			assert(p);

			if(p->active)
			{
				b2Body *body = p->body;
				assert(body);

				float angle	= body->GetAngle();
				float x		= Manager::descale(body->GetPosition().x);
				float y		= Manager::descale(body->GetPosition().y);

				// x^2 decay
				unsigned int elapsed = now - p->created;
				float decay		= (float)elapsed / (float)p->lifespan;
				float opacity	= 1.0f - (decay * decay * decay * decay);
				
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glTranslatef(x, y, 0.0f);
				glRotatef(angle * (180.0f / (float)M_PI), 0.0f, 0.0f, 1.0f);
				glScalef(p->size, p->size, 1.0f);

				// background
				const Colour3f &c = sound->getColour();
				glColor4f(c.getR(), c.getG(), c.getB(), opacity * 0.5f);
                glEnable(GL_BLEND);
                glEnable(GL_LINE_SMOOTH);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                GLPrimitives::getInstance()->renderCircle();
        
				// border
				if(isSelected)
				{
					glColor4f(VALUE_COLOUR.getR(), VALUE_COLOUR.getG(), VALUE_COLOUR.getB(), opacity);
				}
				else
				{
					const Colour3f &c = sound->getColour();
					glColor4f(c.getR(), c.getG(), c.getB(), opacity);
				}

                glLineWidth(1.0f);
                GLPrimitives::getInstance()->renderCircleOutline();
                
                assert(centreLineVbo);
                centreLineVbo->render();
                
                glDisable(GL_BLEND);
                glDisable(GL_LINE_SMOOTH);
				glPopMatrix();
			}
		}
	}

	void ParticleEmitter::updateFixtures(void)
	{
	}

	void ParticleEmitter::updateParticles(void)
	{
		unsigned int now = CrossPlatformTime::getTimeMillis();
		for(unsigned int i = 0; i < MAX_PARTICLE_COUNT; i++)
		{
			Particle *p = &particles[i];
			assert(p);

			if(p->active)
			{
				unsigned int elapsed = now - p->created;
				if(elapsed > p->lifespan)
				{
					p->active = false;

					b2Body *body = p->body;
					assert(body);

					body->SetActive(false);
					body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
					body->SetAngularVelocity(0.0f);

					globalParticleCounter--;
				}
			}
		}
	}
}
