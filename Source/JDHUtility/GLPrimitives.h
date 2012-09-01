/**
 * Class:	GLPrimitives
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <JDHUtility/OpenGL.h>

namespace JDHUtility
{
	class GLPrimitives
	{
	public:
		static GLPrimitives *instance;

		static GLPrimitives *getInstance(void);

		void renderSquare(void) const;

	private:
		GLPrimitives(void);
		~GLPrimitives(void);

		void initSquare(void);
		
		GLuint squareVbo;
	};
}
