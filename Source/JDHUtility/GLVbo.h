/**
 * Class:	GLVbo
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <OpenGL.h>

namespace JDHUtility
{
	class GLVbo
	{
    public:
        static const GLuint COORDS_IN_VERTEX;
        
        GLVbo(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count);
        ~GLVbo(void);
     
        void render(void) const;
        void update(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count);
        
    private:
        
        GLuint id;
        GLenum mode;
        GLsizei count;
    };
}