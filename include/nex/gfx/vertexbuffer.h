#ifndef VERTEXBUFFER_H_INCLUDE
#define VERTEXBUFFER_H_INCLUDE

#include <GL/glew.h>

#include "drawtype.h"

namespace nx
{

/**
 * @brief This class represents an OpenGL Vertex buffer.
 *
 * The vertex buffer object holds the data required for the vertex array to render properly.
 */
class VertexBuffer
{
public:

    /**
     * @brief Default VertexBuffer constructor.
     */
    VertexBuffer();
    ~VertexBuffer();

    /**
     * @brief Create an instance of the vertex buffer.
     */
    void create();

    /**
     * @brief Destroy the instance of the vertex buffer.
     */
    void destroy();

    /**
     * @brief Buffer data to the vertex buffer.
     * @param size = The size of the data.
     * @param data = Pointer to the data.
     * @param drawType = Type of drawing the data will be used for.
     */
    void bufferData(GLsizeiptr size, const void* data, DrawType drawType);

    /**
     * @brief Buffer sub data to the vertex buffer.
     * @param offset = The offset to begin writing at.
     * @param size = The size of the data to write.
     * @param data = Pointer to the data.
     */
    void subData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

    /**
     * @brief Bind the vertex buffer object.
     */
    inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

    /**
     * @brief Unbind the vertex buffer object.
     */
    inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:
    bool m_created;
    bool m_hasData;
    GLuint m_id;
};

} // namespace nx

#endif // VERTEXBUFFER_H_INCLUDE
