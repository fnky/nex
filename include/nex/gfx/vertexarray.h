#ifndef VERTEXARRAY_H_INCLUDE
#define VERTEXARRAY_H_INCLUDE

#include <GL/glew.h>

namespace nx
{

/**
 * @brief This class represents an opengl vertex array.
 *
 * It also holds the current settings and the reference to the vertex buffer object.
 *
 */
class VertexArray
{

public:

    /**
     * @brief Default VertexArray constructor.
     */
    VertexArray();
    ~VertexArray();

    /**
     * @brief Create an instance of the vertex array.
     */
    void create();

    /**
     * @brief Destroy the instance of the vertex array.
     */
    void destroy();

    /**
     * @brief Bind the vertex array.
     */
    inline void bind() const { glBindVertexArray(mId); }

    /**
     * @brief Unbind the vertex array.
     */
    inline void unbind() const { glBindVertexArray(0); }

    /**
     * @brief Check if this vertex array has been created.
     * @return true if it has been created.
     */
    inline bool isCreated() const { return m_created; }

private:
    bool m_created;
    GLuint mId;
};
} // namespace nx

#endif // VERTEXARRAY_H_INCLUDE
