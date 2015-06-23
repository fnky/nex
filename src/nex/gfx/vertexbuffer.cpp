#include <nex/gfx/vertexbuffer.h>

namespace nx
{

VertexBuffer::VertexBuffer() :
    mCreated(false),
    mId(0)
{ }

VertexBuffer::~VertexBuffer()
{
    destroy();
}

void VertexBuffer::create()
{
    glGenBuffers(1, &mId);
    mCreated = true;
}

void VertexBuffer::destroy()
{
    if (mCreated) {
        glDeleteBuffers(1, &mId);
        mCreated = false;
    }
}

void VertexBuffer::bufferData(GLsizeiptr size, const void *data, DrawType drawType)
{
    // Make sure we have a valid buffer to which we can send data to.
    if (!mCreated)
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
