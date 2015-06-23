#include <nex/gfx/elementbuffer.h>

namespace nx
{

ElementBuffer::ElementBuffer() :
    mCreated(false),
    mId(0)
{ }

ElementBuffer::~ElementBuffer()
{
    destroy();
}

void ElementBuffer::create()
{
    mCreated = true;
    glGenBuffers(1, &mId);
}

void ElementBuffer::destroy()
{
    if (mCreated) {
        glDeleteBuffers(1, &mId);
        mCreated = false;
    }
}

void ElementBuffer::bufferData(GLsizeiptr size, const void *data, DrawType drawType)
{
    // Make sure we have a valid buffer to which we can send data to.
    if (!mCreated)
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
