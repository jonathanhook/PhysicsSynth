/**
 * Class:	PressAndHold
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <assert.h>
#include <JDHUtility/CrossPlatformTime.h>
#include <JDHUtility/GLVbo.h>
#include <JDHUtility/Ndelete.h>
#include <JDHUtility/OpenGL.h>
#include <math.h>
#include <stdlib.h>
#include "PressAndHold.h"

namespace PhysicsSynth
{
	/* Private Constants */
	const unsigned int	PressAndHold::CIRCLE_SEGS	= 32;
	const float			PressAndHold::INNER_RAD		= 0.025f;
	const float			PressAndHold::MAX_FILL_OPACITY	= 0.25f;
    const float			PressAndHold::MAX_LINE_OPACITY	= 0.5f;
	const float			PressAndHold::OUTER_RAD		= 0.033f;
	const float			PressAndHold::THRESHOLD		= 0.01f;
	const unsigned int	PressAndHold::TIMEOUT		= 750;

	/* Constructors */
	PressAndHold::PressAndHold(const Point2f &position, const Point2f &createPosition, unsigned int fingerId)
	{
		this->position			= position;
		this->createPosition	= createPosition;
		this->fingerId			= fingerId;

		completed		= NULL;
		dirty			= true;
		halfWay			= NULL;
		halfWayFired	= false;
		markedForDelete	= false;
		timeCreated		= CrossPlatformTime::getTimeMillis();
        
        // VBOs
        float radius	= OUTER_RAD;
        float iRadius	= INNER_RAD;

        unsigned int fillVertexCount = CIRCLE_SEGS * 2;
        unsigned int fillArrayLength = fillVertexCount * 3;
        GLfloat fillVertices[fillArrayLength];
        
        unsigned int lineVertexCount = CIRCLE_SEGS;
        unsigned int lineArrayLength = lineVertexCount * 3;
        GLfloat innerVertices[lineArrayLength];
        GLfloat outerVertices[lineArrayLength];
        
        for(unsigned int i = 0; i < CIRCLE_SEGS; i++)
        {
            float theta = (2.0f * (float)M_PI) * ((float)i / (float)(CIRCLE_SEGS - 2));

            float x = cos(theta) * radius;
            float y = sin(theta) * radius;
            
            float ix = cos(theta) * iRadius;
            float iy = sin(theta) * iRadius;
            
            // fill
            unsigned int index = i * 6;
            
            fillVertices[index] = x;
            fillVertices[index + 1] = y;
            fillVertices[index + 2] = 0.0f;
            
            fillVertices[index + 3] = ix;
            fillVertices[index + 4] = iy;
            fillVertices[index + 5] = 0.0f;
            
            // lines
            unsigned int lIndex = i * 3;
            
            innerVertices[lIndex] = x;
            innerVertices[lIndex + 1] = y;
            innerVertices[lIndex + 2] = 0.0f;
            
            outerVertices[lIndex] = ix;
            outerVertices[lIndex + 1] = iy;
            outerVertices[lIndex + 2] = 0.0f;
        }

        fillVbo = new GLVbo(GL_TRIANGLE_STRIP, GL_STATIC_DRAW, fillVertices, fillVertexCount);
        innerLineVbo = new GLVbo(GL_LINE_STRIP, GL_STATIC_DRAW, innerVertices, lineVertexCount);
        outerLineVbo = new GLVbo(GL_LINE_STRIP, GL_STATIC_DRAW, outerVertices, lineVertexCount);
	}

	PressAndHold::~PressAndHold(void)
	{
        NDELETE(fillVbo);
        NDELETE(innerLineVbo);
        NDELETE(outerLineVbo);
	}

	/* Public Member Functions */
	bool PressAndHold::getMarkedForDelete(void) const
	{
		return markedForDelete;
	}

	void PressAndHold::render(void)
	{
        float x = position.getX();
        float y = position.getY();
        float o = pow(progress, 4.0f);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(x, y, 0.0f);
				
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 1.0f, o * MAX_FILL_OPACITY);
        
        assert(fillVbo);
        fillVbo->update(GL_TRIANGLE_STRIP, GL_STATIC_DRAW, NULL, ((float)CIRCLE_SEGS * 2.0f) * o);
        fillVbo->render();
        
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(1.0f);
        glColor4f(1.0f, 1.0f, 1.0f, o * MAX_LINE_OPACITY);
        
        assert(innerLineVbo);
        innerLineVbo->update(GL_LINE_STRIP, GL_STATIC_DRAW, NULL, (float)CIRCLE_SEGS * o);
        innerLineVbo->render();
        
        assert(outerLineVbo);
        outerLineVbo->update(GL_LINE_STRIP, GL_STATIC_DRAW, NULL, (float)CIRCLE_SEGS * o);
        outerLineVbo->render();
        
        glDisable(GL_BLEND);
        glDisable(GL_LINE_SMOOTH);
        glPopMatrix();
	}

	void PressAndHold::update(void)
	{
		unsigned int now		= CrossPlatformTime::getTimeMillis();
		unsigned int elapsed	= now - timeCreated;
		progress				= (float)elapsed / (float)TIMEOUT;
		dirty					= true;

		if(progress >= 1.0f && !markedForDelete)
		{
			if(completed != NULL)
			{
				completed(*this, createPosition);
			}

			markedForDelete = true;
		}
		else if(progress >= 0.5f && !markedForDelete && !halfWayFired)
		{
			if(halfWay != NULL)
			{
				halfWay(*this);
			}

			halfWayFired = true;
		}
	}

	void PressAndHold::updateFingerPosition(const Point2f &newPosition)
	{
		float dx	= position.getX() - newPosition.getX();
		float dy	= position.getY() - newPosition.getY();
		float d		= sqrt((dx * dx) + (dy * dy));
	
		if(d >= THRESHOLD)
		{
			markedForDelete = true;
		}
	}

	void PressAndHold::setMarkedForDelete(bool markedForDelete)
	{
		this->markedForDelete = markedForDelete;
	}

	void PressAndHold::setCompletedCallback(CompletedCallback completed)
	{
		this->completed = completed;
	}
}
