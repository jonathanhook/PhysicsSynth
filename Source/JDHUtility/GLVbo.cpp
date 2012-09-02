/**
 * Class:	GLVbo
 * Author:	Jonathan David Hook
 * Email:	j.d.hook@ncl.ac.uk
 * Web:		http://homepages.cs.ncl.ac.uk/j.d.hook
 */
#include "GLVbo.h"

namespace JDHUtility
{
    /* Constants */
    const GLuint GLVbo::COORDS_IN_VERTEX = 3;
    
    /* Constructors */
    GLVbo::GLVbo(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count)
    {
        glGenBuffers(1, &id);
        update(mode, usage, vertices, count);
    }
    
    GLVbo::~GLVbo(void)
    {
        glDeleteBuffers(1, &id);
    }
    
    /* Public member functions */
    void GLVbo::render(void) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(mode, 0, count);
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void GLVbo::update(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count)
    {
        this->mode  = mode;
        this->count = count;
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * COORDS_IN_VERTEX * count, vertices, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}