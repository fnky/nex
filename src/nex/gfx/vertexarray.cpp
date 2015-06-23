#include <nex/gfx/vertexarray.h>

namespace nx
{

VertexArray::VertexArray() :
    mCreated(false),
    mId(0)
{ }

VertexArray::~VertexArray()
{
    destroy();
}

void VertexArray::create()
{
    glGenVertexArrays(1, &mId);
    mCreated = true;
}

void VertexArray::destroy()
{
    if (mCreated) {
        glDeleteVertexArrays(1, &mId);
        mCreated = false;
    }
}

} // namespace nx
