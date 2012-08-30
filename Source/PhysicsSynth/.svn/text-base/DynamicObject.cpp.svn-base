/**
 * Class:	DynamicObject
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <assert.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/Colour4f.h>
#include <JDHUtility/OpenGL.h>
#include <JDHUtility/GLMatrixf.h>
#include <JDHUtility/GLTexture.h>
#include <JDHUtility/WindowingUtils.h>
#include <math.h>
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

		backgroundDl	= -1;
		borderDl		= -1;
		finger			= NULL;
		fingerDown		= false;
		lastTick		= 0;
		loop			= new LoopPointer(0.0f);
		textureDl		= -1;

		Synchronizer *sync = Synchronizer::getInstance();
		assert(sync);

		sync->syncLoop(loop);
	}

	DynamicObject::~DynamicObject(void)
	{
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

		float tickIncrement		= 1.0f / (PATTERN_LENGTH);
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
		glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
		
		assert(sound);
		const Colour3f &sc = sound->getColour();
		glColor4f(sc.getR(), sc.getG(), sc.getB(), 0.5f);

		if(backgroundDl == -1)
		{
			backgroundDl = glGenLists(1);
			glNewList(backgroundDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_POLYGON);
				float angleIncrement = ((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES;
				for(unsigned int i = 0; i < CIRCLE_VERTICES; i++)
				{
					float theta = angleIncrement * (float)i; 
					float px	= cos(theta) * ICON_SIZE;
					float py	= sin(theta) * ICON_SIZE;

					glVertex3f(px, py, 0.0f);
				}
			glEnd();

			glPopAttrib();
			glEndList();
		}
		glCallList(backgroundDl);

		if(textureDl == -1)
		{
			GLTexture texture(texturePath);
			
			textureDl = glGenLists(1);
			glNewList(textureDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			texture.bind(GL_REPLACE);
			glBegin(GL_POLYGON);
				float angleIncrement = ((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES;
				for(unsigned int i = 0; i < CIRCLE_VERTICES; i++)
				{
					float theta = angleIncrement * (float)i; 
					float px	= cos(theta) * ICON_SIZE;
					float py	= sin(theta) * ICON_SIZE;
					float u		= (px + ICON_SIZE) / (ICON_SIZE * 2.0f);
					float v		= (py + ICON_SIZE) / (ICON_SIZE * 2.0f);

					glTexCoord2f(u, v);
					glVertex3f(px, py, 0.0f);
				}
			glEnd();

			glPopAttrib();
			glEndList();
		}
		glCallList(textureDl);

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

		if(borderDl == -1)
		{
			borderDl = glGenLists(1);
			glNewList(borderDl, GL_COMPILE);

			glPushAttrib(GL_ENABLE_BIT);
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_LINE_LOOP);
				float angleIncrement = ((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES;
				for(unsigned int i = 0; i < CIRCLE_VERTICES; i++)
				{
					float theta = angleIncrement * (float)i; 
					float px	= cos(theta) * ICON_SIZE;
					float py	= sin(theta) * ICON_SIZE;

					glVertex3f(px, py, 0.0f);
				}
			glEnd();

			glPopAttrib(); // GL_ENABLE_BIT
			glEndList();
		}
		glCallList(borderDl);

		glPopAttrib(); // GL_CURRENT_BIT | GL_LINE_BIT
	}
}