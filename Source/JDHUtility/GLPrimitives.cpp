/**
 * Class:	GLPrimitives
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <assert.h>
#include <stdlib.h>
#include "Ndelete.h"
#include "GLVbo.h"
#include "GLPrimitives.h"


namespace JDHUtility
{
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
		NDELETE(squareVbo);
        NDELETE(squareOutlineVbo);
    }

	/* Public Member Functions */
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
        GLfloat data[12] =
		{ 
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

        squareVbo = new GLVbo(GL_QUADS, GL_STATIC_DRAW, data, 4);
        squareOutlineVbo = new GLVbo(GL_LINE_LOOP, GL_STATIC_DRAW, data, 4);
        
	}
}