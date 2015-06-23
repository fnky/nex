#ifndef VERTEXLIST_H_INCLUDE
#define VERTEXLIST_H_INCLUDE

// Nex includes.
#include <nex/gfx/vertex3d.h>

// Standard includes.
#include <vector>

namespace nx
{

class VertexList3d
{
public:

    /**
     * @brief Default constructor.
     */
    VertexList3d();

    /**
     * @brief Default desturctor.
     */
    ~VertexList3d();

    /**
     * @brief Push a 3d vertex onto the list.
     * @param vertex = The 3d vertex to add.
     */
    inline void addVertex(const Vertex3d& vertex) {
        mVertices.push_back(vertex);
    }

    /**
     * @brief Clear this vertex list.
     */
    inline void clear() { mVertices.clear(); }

    /**
     * @brief Get the size of the vertex list.
     * @return The size of the vertex list.
     */
    inline uint32 size() const { return mVertices.size(); }

    /**
     * @brief Get a pointer to the data.
     * @return A constant pointer to the vertex data.
     */
    inline const Vertex3d* getVertexPtr() { return &mVertices[0]; }

    /**
     * @brief Get a pointer to the raw float data.
     * @return A pointer to the raw float data.
     */
    inline const float* getFloatPtr() { return reinterpret_cast<const float*>(&mVertices[0]); }

private:

    std::vector<Vertex3d> mVertices;
};

} // namespace nx

#endif // VERTEXLIST_H_INCLUDE
