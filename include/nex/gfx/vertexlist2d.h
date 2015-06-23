#ifndef VERTEXLIST_H_INCLUDE
#define VERTEXLIST_H_INCLUDE

// Nex includes.
#include <nex/gfx/vertex2d.h>

#include <vector>

namespace nx
{

class VertexList2d
{
public:

    /**
     * @brief Default constructor.
     */
    VertexList2d();

    /**
     * @brief Default destructor.
     */
    ~VertexList2d();

    /**
     * @brief Add a 2d vertex into the list.
     * @param vertex
     */
    inline void addVertex(const Vertex2d& vertex) {
        mVertices.push_back(vertex);
    }

    inline void resize(std::size_t vertexCount) {
        mVertices.resize(vertexCount);
    }

    /**
     * @brief Get a read-write access to a vertex by its index.
     * @param index = Index Index of the vertex to get.
     * @return Reference to the index-th vertex.
     */
    Vertex2d& operator [](std::size_t index);

    /**
     * @brief Get a read-only access to a vertex by its index.
     * @param index = Const reference to the index-th vertex.
     * @return Const reference to the index-th vertex.
     */
    const Vertex2d& operator [](std::size_t index) const;

    /**
     * @brief Clear the vertex list.
     */
    inline void clear() { mVertices.clear(); }

    /**
     * @brief Get the size of the current vertex list.
     * @return the size of the list.
     */
    inline uint32 size() const { return mVertices.size(); }

    /**
     * @brief Get a pointer to the data.
     * @return A constant pointer to the vertex data.
     */
    inline const Vertex2d* getVertexPtr() { return &mVertices[0]; }

    /**
     * @brief Get a pointer to the raw float data.
     * @return A pointer to the raw float data.
     */
    inline const float* getFloatPtr() { return reinterpret_cast<const float*>(&mVertices[0]); }

private:
    std::vector<Vertex2d> mVertices;
};

} // namespace nx

#endif // VERTEXLIST_H_INCLUDE
