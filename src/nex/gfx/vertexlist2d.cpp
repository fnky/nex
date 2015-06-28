#include <nex/gfx/vertexlist2d.h>

namespace nx
{

VertexList2d::VertexList2d()
{ }

VertexList2d::~VertexList2d()
{
    m_vertices.clear();
}

Vertex2d& VertexList2d::operator [](std::size_t index)
{
    return m_vertices[index];
}

const Vertex2d& VertexList2d::operator [](std::size_t index) const
{
    return m_vertices[index];
}

} // namespace nx
