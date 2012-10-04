/**
 * Class:	Bomb
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <assert.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLTexture.h>
#include <JDHUtility/GLPrimitives.h>
#include <math.h>
#include "Bomb.h"
#include "Manager.h"
#include "RegionQueryCallback.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const float				Bomb::BLAST_IMPULSE			= 1000.0f;
	const float				Bomb::BLAST_RADIUS_OPACITY	= 0.5f;
	const unsigned int		Bomb::DECAY_TIME			= 100;
	const float				Bomb::DEFAULT_INTENSITY		= 0.5f;
	const unsigned int		Bomb::CIRCLE_VERTICES		= 32;
	const unsigned short	Bomb::LINE_PATTERN			= 0xAAAA;
	const int				Bomb::LINE_STIPPLE_FACTOR	= 5;
	const float				Bomb::MAX_BLAST_RAD_SIZE	= 0.05f;
	const float				Bomb::MIN_BLAST_RAD_SIZE	= 0.0075f;
	const float				Bomb::MAX_INTENSITY			= 1.0f;
	const float				Bomb::MIN_INTENSITY			= 0.1f;
	const std::string		Bomb::TEXTURE_PATH			= "../../../Data/Textures/Bomb/bomb.tga";

	/* Constructors */
	Bomb::Bomb(float intensity, float rate, unsigned int pattern, float size, SoundConfig *sound) :
		DynamicObject(TEXTURE_PATH, rate, pattern, size, sound)
	{
		this->intensity = intensity;

		lastBlastTime	= 0;
	}

	Bomb::~Bomb(void)
	{
	}

	/* Public Member Functions */
	void Bomb::addToWorld(b2World *world, const Point2f &position)
	{
		DynamicObject::addToWorld(world, position);
	}

	float Bomb::getIntensity(void) const
	{
		return intensity;
	}

	PhysicsObject::PhysicsObjectType Bomb::getObjectType(void) const
	{
		return BOMB;
	}

	void Bomb::render(void)
	{
		DynamicObject::render();

		float x = position.getX();
		float y = position.getY();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x, y, 0.0f);

		renderBlastRadius();

		glPopMatrix();

	}

	/* Private Member Functions */
	float Bomb::getBlastAlpha(void) const
	{
		float i					= getBlastIntensity();
		unsigned int now		= CrossPlatformTime::getTimeMillis();
		unsigned int elapsed	= now - lastBlastTime;

		if(elapsed < DECAY_TIME)
		{
			float d = (float)elapsed / (float)DECAY_TIME;
			return d * i;
		}
		else
		{
			return 0.0f;
		}
	}

	float Bomb::getBlastIntensity(void) const
	{
		return (intensity * (MAX_INTENSITY - MIN_INTENSITY)) + MIN_INTENSITY;
	}

	float Bomb::getBlastRadiusSize(void) const
	{
		return (size * (MAX_BLAST_RAD_SIZE - MIN_BLAST_RAD_SIZE)) + MIN_BLAST_RAD_SIZE;
	}

	void Bomb::renderBlastRadius(void)
	{
		float blSize		= getBlastRadiusSize();
		float blastAlpha	= getBlastAlpha();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glScalef(blSize, blSize, 1.0f);

        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        //glEnable(GL_LINE_STIPPLE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glLineStipple(LINE_STIPPLE_FACTOR, LINE_PATTERN);
        glLineWidth(1.0f);
        glColor4f(1.0f, 1.0f, 1.0f, BLAST_RADIUS_OPACITY);
		
        GLPrimitives::getInstance()->renderCircleOutline();

		glColor4f(1.0f, 1.0f, 1.0f, blastAlpha);
        glScalef(0.95f, 0.95f, 1.0f);
        
        GLPrimitives::getInstance()->renderCircle();
        
		glPopMatrix();
	}

	void Bomb::onPatternTick(void)
	{
		if(isInWorld)
		{
			assert(world);

			float bs = getBlastRadiusSize();
			float sx = Manager::scale(position.getX());
			float sy = Manager::scale(position.getY());
			float ss = Manager::scale(bs);

			b2Vec2 p(sx, sy);
			b2AABB aabb;
			b2Vec2 d;
			d.Set(ss, ss);
			aabb.lowerBound = p - d;
			aabb.upperBound = p + d;

			// Query the world for overlapping shapes
			RegionQueryCallback callback;
			world->QueryAABB(&callback, aabb);

			if(callback.hasFixtures())
			{
				const std::vector<b2Fixture *> &fixtures	= callback.getFixtures();
				bool collided								= false;
				float x										= position.getX();
				float y										= position.getY();

				for(unsigned int i = 0; i < fixtures.size(); i++)
				{
					b2Fixture *fixture = fixtures[i];
					assert(fixture);

					b2Body* body = fixture->GetBody();
					assert(body);

					PhysicsObject *pObj = dynamic_cast<PhysicsObject *>((PhysicsObject *)body->GetUserData());
					if(pObj != NULL)
					{
						assert(pObj);

						const Point2f &objPos	= pObj->getPosition();
						float objBounds			= pObj->getBoundingRegion();
						float ox				= objPos.getX();
						float oy				= objPos.getY();

						// from centre
						float cx = ox - x;
						float cy = oy - y;

						// from boundary
						float bx = fabs(cx) - objBounds;
						float by = fabs(cy) - objBounds;
						bx = bx < 0.0f ? 0.0f : bx;
						by = by < 0.0f ? 0.0f : by;

						// distance from edge of bounding region to centre (used to scale impulse)
						float d = 1.0f - (sqrt((bx * bx) + (by * by)) / bs);
					
						if(d > 0.0f)
						{
							// apply forces
							float in = getBlastIntensity();
						
							// unit vector between centres
							float ma = sqrt((cx * cx) + (cy * cy));
							float vx = ((cx / ma) * in) * BLAST_IMPULSE;
							float vy = ((cy / ma) * in) * BLAST_IMPULSE;

							body->ApplyForce(b2Vec2(vx, vy), b2Vec2(0.0f, 0.0f));

							// make sounds
							// TODO: DONT MAKE OWN SOUND YET?
							collided = true;
						}
					}
				}

				// if collided make own sound
				if(collided && soundEvent != NULL)
				{
					assert(sound);
					soundEvent(sound, sx, sy, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
				}
			}

			lastBlastTime = CrossPlatformTime::getTimeMillis();
		}
	}

	void Bomb::setIntensity(float intensity)
	{
		this->intensity = intensity;
	}

	void Bomb::updateFixtures(void)
	{

	}
}
