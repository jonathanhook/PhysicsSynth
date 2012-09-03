/**
 * Class:	GLPrimitives
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <OpenGL.h>

namespace JDHUtility
{
    class GLVbo;
    
	class GLPrimitives
	{
	public:
        static const GLsizei CIRCLE_VERTICES;
        
		static GLPrimitives *instance;
		static GLPrimitives *getInstance(void);

        void renderCircle           (void) const;
        void renderCircleOutline    (void) const;
		void renderSquare           (void) const;
        void renderSquareOutline    (void) const;

	private:
		GLPrimitives(void);
		~GLPrimitives(void);

		void initPrimitives(void);
       
        GLVbo *circleVbo;
        GLVbo *circleOutlineVbo;
        GLVbo *squareVbo;
        GLVbo *squareOutlineVbo;
        
	};
}
