#include <nex/gfx/vertexlist2d.h>

namespace nx
{

VertexList2d::VertexList2d()
{ }

VertexList2d::~VertexList2d()
{
    mVertices.clear();
}

Vertex2d& VertexList2d::operator [](std::size_t index)
{
    return mVertices[index];
}

const Vertex2d& VertexList2d::operator [](std::size_t index) const
{
    return mVertices[index];
}

} // namespace nx
