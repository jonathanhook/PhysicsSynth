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
    const GLuint GLVbo::COORDS_IN_UV = 2;
    
    /* Constructors */
    GLVbo::GLVbo(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count, GLfloat *textureCoords)
    {
        glGenBuffers(1, &id);
        glGenBuffers(1, &textureId);
        
        update(mode, usage, vertices, count, textureCoords);
    }
    
    GLVbo::~GLVbo(void)
    {
        glDeleteBuffers(1, &id);
        glDeleteBuffers(1, &textureId);
    }
    
    /* Public member functions */
    void GLVbo::render(void) const
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, id);
		glVertexPointer(COORDS_IN_VERTEX, GL_FLOAT, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, textureId);
        glTexCoordPointer(COORDS_IN_UV, GL_FLOAT, 0, 0);
        
        glDrawArrays(mode, 0, count);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    
    void GLVbo::update(GLenum mode, GLenum usage, GLfloat *vertices, GLsizei count, GLfloat *textureCoords)
    {
        this->mode  = mode;
        this->count = count;
        
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * COORDS_IN_VERTEX * count, vertices, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        if(textureCoords != NULL)
        {
            glBindBuffer(GL_ARRAY_BUFFER, textureId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * COORDS_IN_UV * count, textureCoords, usage);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}