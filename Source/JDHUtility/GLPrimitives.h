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
		static GLPrimitives *instance;
		static GLPrimitives *getInstance(void);

		void renderSquare           (void) const;
        void renderSquareOutline    (void) const;

	private:
		GLPrimitives(void);
		~GLPrimitives(void);

		void initPrimitives(void);
       
        GLVbo *squareVbo;
        GLVbo *squareOutlineVbo;
        
	};
}
