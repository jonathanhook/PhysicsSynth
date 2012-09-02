/**
 * Class:	GLVbo
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#pragma once
#include <stdlib.h>
#include <OpenGL.h>

namespace JDHUtility
{
	class GLVbo
	{
    public:
        static const GLuint COORDS_IN_VERTEX;
        static const GLuint COORDS_IN_UV;
        
        GLVbo(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count, GLfloat *textureCoords = NULL);
        ~GLVbo(void);
     
        void render(void) const;
        void update(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count, GLfloat *textureCoords = NULL);
        
    private:
        
        GLuint  id;
        GLuint  textureId;
        
        GLenum  mode;
        GLsizei count;
    };
}