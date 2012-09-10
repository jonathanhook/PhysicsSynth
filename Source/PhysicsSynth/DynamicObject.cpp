/**
 * Class:	DynamicObject
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLTexture.h>
#include <JDHUtility/GLPrimitives.h>
#include <JDHUtility/WindowingUtils.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/PointInclusion.h>
#include "DynamicObject.h"
#include "Finger.h"
#include "LoopPointer.h"
#include "Manager.h"
#include "Synchronizer.h"

namespace PhysicsSynth
{
	/* Public Constants */
	const unsigned int	DynamicObject::PATTERN_LENGTH = 8;

	/* Protected Constants */
	const unsigned int	DynamicObject::DEFAULT_PATTERN	= 0x55;
	const float			DynamicObject::DEFAULT_RATE		= 0.5f;
	const float			DynamicObject::ICON_SIZE		= 0.0075f;

	/* Private Constants */
	const unsigned int	DynamicObject::CIRCLE_VERTICES	= 16;
	const float			DynamicObject::THUMBNAIL_SCALE	= 40.0f;

	/* Constructors */
	DynamicObject::DynamicObject(std::string texturePath, float rate, unsigned int pattern, float size, SoundConfig *sound, float friction, float restitution) :
		PhysicsObject(false, size, sound, friction, restitution)
	{
		this->texturePath	= texturePath; 
		this->rate			= rate;
		this->pattern		= pattern;

		finger			= NULL;
		fingerDown		= false;
		lastTick		= 0;
		loop			= new LoopPointer(0.0f);
        texture         = new GLTexture(texturePath);

		Synchronizer *sync = Synchronizer::getInstance();
		assert(sync);

		sync->syncLoop(loop);
	}

	DynamicObject::~DynamicObject(void)
	{
        NDELETE(texture);
		NDELETE(loop);
	}

	/* Public Member Functions */
	void DynamicObject::addToWorld(b2World *world, const Point2f &position)
	{
		PhysicsObject::addToWorld(world, position);
		sync();
	}

	bool DynamicObject::contains(const FingerEventArgs &e) const
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

	void DynamicObject::fingerAdded(const FingerEventArgs &e)
	{
		if(!fingerDown)
		{
			Point2f p =	e.getPosition();
			modelview->unScalePoint(p);

			fingerDown	= true;
			finger		= new Finger(e.getId(), p);

			if(selected != NULL)
			{
				selected(this);
			}
		}
	}

	void DynamicObject::fingerUpdated(const FingerEventArgs &e)
	{
		if(fingerDown)
		{
			assert(finger);
			unsigned int id = e.getId();

			if(finger->getId() == id)
			{
				Point2f p =	e.getPosition();
				modelview->unScalePoint(p);

				finger->updatePosition(p);
				
				if(!isLocked && translate != NULL)
				{	
					Vector2f delta	= finger->getDelta();
					Point2f pos		= getPosition();
					pos.translate(delta);

					translate(this, pos);
				}
			}
		}
	}

	void DynamicObject::fingerRemoved(const FingerEventArgs &e)
	{
		if(fingerDown)
		{
			assert(finger);
			unsigned int id = e.getId();

			if(finger->getId() == id)
			{
				fingerDown = false;
				NDELETE(finger);
			}
		}
	}

	float DynamicObject::getBoundingRegion(void) const
	{
		return Manager::scale(ICON_SIZE);
	}

	unsigned int DynamicObject::getPattern(void) const
	{
		return pattern;
	}

	float DynamicObject::getRate(void) const
	{
		return rate;
	}

	void DynamicObject::render(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(position.getX(), position.getY(), 0.0f);
		saveTransform();
			
		renderIcon();
		
		glPopMatrix();
	}

	void DynamicObject::renderThumbnail(void)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glScalef(THUMBNAIL_SCALE, THUMBNAIL_SCALE, 1.0f);

		renderIcon();

		glPopMatrix();
	}

	void DynamicObject::setPattern(unsigned int pattern)
	{
		this->pattern = pattern;
	}

	void DynamicObject::setRate(float rate)
	{
		this->rate = rate;
	}

	void DynamicObject::sync(void)
	{
		Synchronizer *s = Synchronizer::getInstance();
		assert(s);
		assert(loop);

		// sync the loop position
		s->syncLoop(loop);
		lastTick = 0;

		// sync values
		rate = s->getSnappedSliderVal(rate);
	}

	void DynamicObject::update(void)
	{
		assert(loop);
		loop->update(rate);

		unsigned int loopPos	= (unsigned int)(loop->getLoopPosition() * PATTERN_LENGTH);

		if(loopPos != lastTick)
		{
			if(pattern & (1 << (loopPos % PATTERN_LENGTH)))
			{
				onPatternTick();
			}

			lastTick = loopPos;
		}
	}

	/* Protected Member Functions */
	void DynamicObject::updateLockedMass(void)
	{

	}

	/* Private Member Functions */
	void DynamicObject::renderIcon(void)
	{
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(ICON_SIZE, ICON_SIZE, 1.0f);
        
		glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
		assert(sound);
		const Colour3f &sc = sound->getColour();
		glColor4f(sc.getR(), sc.getG(), sc.getB(), 0.5f);
        
        GLPrimitives::getInstance()->renderCircle();
        
        texture->bind(GL_REPLACE);
        GLPrimitives::getInstance()->renderCircle();
        
        glPopAttrib();

        glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT | GL_ENABLE_BIT);
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
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

		glPopAttrib(); // GL_CURRENT_BIT | GL_LINE_BIT
        glPopMatrix();
	}
}