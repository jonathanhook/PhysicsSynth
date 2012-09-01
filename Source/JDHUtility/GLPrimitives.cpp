/**
 * Class:	GLPrimitives
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include <stdlib.h>
#include "Ndelete.h"
#include "GLPrimitives.h"

#include  <stdio.h>

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
		initSquare();
	}

	GLPrimitives::~GLPrimitives(void)
	{
		glDeleteBuffers(1, &squareVbo);
	}

	/* Public Member Functions */
	void GLPrimitives::renderSquare(void)
	{
		glBindBuffer(GL_ARRAY_BUFFER, squareVbo);
        glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/* Private Member Functions */
	void GLPrimitives::initSquare(void)
	{
        const GLfloat data[12] =
		{ 
			0.0f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glGenBuffers(1, &squareVbo);
        glBindBuffer(GL_ARRAY_BUFFER, squareVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, &data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}