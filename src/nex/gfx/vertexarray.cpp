#include <nex/gfx/vertexarray.h>

namespace nx
{

VertexArray::VertexArray() :
    m_created(false),
    mId(0)
{ }

VertexArray::~VertexArray()
{
    destroy();
}

void VertexArray::create()
{
    glGenVertexArrays(1, &mId);
    m_created = true;
}

void VertexArray::destroy()
{
    if (m_created) {
        glDeleteVertexArrays(1, &mId);
        m_created = false;
    }
}

} // namespace nx
