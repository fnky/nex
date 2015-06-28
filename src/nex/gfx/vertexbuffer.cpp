#include <nex/gfx/vertexbuffer.h>

namespace nx
{

VertexBuffer::VertexBuffer() :
    m_created(false),
    m_id(0)
{ }

VertexBuffer::~VertexBuffer()
{
    destroy();
}

void VertexBuffer::create()
{
    glGenBuffers(1, &m_id);
    m_created = true;
}

void VertexBuffer::destroy()
{
    if (m_created) {
        glDeleteBuffers(1, &m_id);
        m_created = false;
    }
}

void VertexBuffer::bufferData(GLsizeiptr size, const void *data, DrawType drawType)
{
    // Make sure we have a valid buffer to which we can send data to.
    if (!m_created)
        create();

    // Make sure we are the currently bounded buffer.
    bind();

    glBufferData(GL_ARRAY_BUFFER, size, data, drawType);
}

void VertexBuffer::subData(GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
    // Make sure we are the currently bounded buffer.
    bind();

    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

} // namespace nx
