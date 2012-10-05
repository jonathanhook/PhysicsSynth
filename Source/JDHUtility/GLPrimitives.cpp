/**
 * Class:	GLPrimitives
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "Ndelete.h"
#include "GLVbo.h"
#include "GLPrimitives.h"

namespace JDHUtility
{
    /* Constants */
    const GLsizei GLPrimitives::CIRCLE_VERTICES = 64;
    
	/* Static Functions */
	GLPrimitives *GLPrimitives::instance = NULL;
	GLPrimitives *GLPrimitives::getInstance(void)
	{
		if(!instance)
		{
			instance = new GLPrimitives();
		}

		return instance;
	}

	/* Constructors */
	GLPrimitives::GLPrimitives(void)
	{
		initPrimitives();
	}

	GLPrimitives::~GLPrimitives(void)
	{
        NDELETE(circleVbo);
        NDELETE(circleOutlineVbo);
		NDELETE(squareVbo);
        NDELETE(squareOutlineVbo);
    }

	/* Public Member Functions */
    void GLPrimitives::renderCircle(void) const
    {
        assert(circleVbo);
        circleVbo->render();
    }
    
    void GLPrimitives::renderCircleOutline(void) const
    {
        assert(circleOutlineVbo);
        circleOutlineVbo->render();
    }
    
	void GLPrimitives::renderSquare(void) const
	{
		assert(squareVbo);
        squareVbo->render();
	}
    
    void GLPrimitives::renderSquareOutline(void) const
	{
		assert(squareOutlineVbo);
        squareOutlineVbo->render();
	}

	/* Private Member Functions */
	void GLPrimitives::initPrimitives(void)
	{
        // square
        GLfloat squareData[12] =
		{ 
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f
		};
        
        GLfloat squareTextureData[8] =
		{
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

        squareVbo = new GLVbo(GL_TRIANGLE_STRIP, GL_STATIC_DRAW, squareData, 4, squareTextureData);
        squareOutlineVbo = new GLVbo(GL_LINE_LOOP, GL_STATIC_DRAW, squareData, 4, squareTextureData);
    
        // circle
        GLsizei circleVertexCount = CIRCLE_VERTICES * 3;
        GLfloat circleData[circleVertexCount];
        
        GLsizei circleTextureCount = CIRCLE_VERTICES * 2;
        GLfloat circleTextureData[circleTextureCount];

        unsigned int j = 0;
        float angleIncrement = ((float)M_PI * 2.0f) / (float)CIRCLE_VERTICES;
        for(unsigned int i = 0; i < circleVertexCount; i+=3)
        {
            float theta = angleIncrement * (float)i / 3.0f;
            float px	= cos(theta) * 1.0f;
            float py	= sin(theta) * 1.0f;
            
            circleData[i]       = px;
            circleData[i + 1]   = py;
            circleData[i + 2]   = 0.0f;
            
            circleTextureData[j++] = (px + 1.0f) / 2.0f;
            circleTextureData[j++] = (py + 1.0f) / 2.0f;
        }
        
        circleVbo           = new GLVbo(GL_TRIANGLE_FAN, GL_STATIC_DRAW, circleData, CIRCLE_VERTICES, circleTextureData);
        circleOutlineVbo    = new GLVbo(GL_LINE_LOOP, GL_STATIC_DRAW, circleData, CIRCLE_VERTICES);
	}
}