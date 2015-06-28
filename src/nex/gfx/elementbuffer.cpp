#include <nex/gfx/elementbuffer.h>

namespace nx
{

ElementBuffer::ElementBuffer() :
    m_created(false),
    m_id(0)
{ }

ElementBuffer::~ElementBuffer()
{
    destroy();
}

void ElementBuffer::create()
{
    m_created = true;
    glGenBuffers(1, &m_id);
}

void ElementBuffer::destroy()
{
    if (m_created) {
        glDeleteBuffers(1, &m_id);
        m_created = false;
    }
}

void ElementBuffer::bufferData(GLsizeiptr size, const void *data, DrawType drawType)
{
    // Make sure we have a valid buffer to which we can send data to.
    if (!m_created)
        create();

    // Make sure we are the currently bounded buffer.
    bind();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, drawType);
}

void ElementBuffer::subData(GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
    // Make sure we are the currently bounded buffer.
    bind();

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

} // namespace nx
