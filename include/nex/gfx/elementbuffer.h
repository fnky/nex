#ifndef ELEMENTBUFFER_H_INCLUDE
#define ELEMENTBUFFER_H_INCLUDE

#include <GL/glew.h>

#include "drawtype.h"

namespace nx
{

/**
 * @brief This class represents an OpenGL Element Buffer Object.
 *
 * This element buffer holds the indexes which reference data from a vertex buffer object.
 */
class ElementBuffer
{
public:
    ElementBuffer();
    ~ElementBuffer();

    /**
     * @brief Create an instance of the vertex buffer object.
     */
    void create();

    /**
     * @brief Destroy the instance of the vertex buffer object.
     */
    void destroy();

    /**
     * @brief Buffer data to the element buffer.
     * @param size = The size of the data.
     * @param data = Pointer to the data.
     * @param drawType = Type of drawing the data will be used for.
     */
    void bufferData(GLsizeiptr size, const void* data, DrawType drawType);

    /**
     * @brief Buffer sub data to the element buffer.
     * @param offset = The offset to begin writing at.
     * @param size = The size of the data to write.
     * @param data = Pointer to the data.
     */
    void subData(GLintptr offset, GLsizeiptr size, const GLvoid* data);

    /**
     * @brief Bind the element buffer.
     */
    inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }

    /**
     * @brief Unbind the element buffer.
     */
    inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    /**
     * @brief Check if this element buffer has been created.
     * @return true if it has been created.
     */
    inline bool isCreated() const { return m_created; }

private:
    bool m_created;
    GLuint m_id;
};

} // namespace nx

#endif // ELEMENTBUFFER_H_INCLUDE
