#ifndef VERTEX_H_INCLUDE
#define VERTEX_H_INCLUDE

#include <nex/math/vec2.h>
#include <nex/math/vec3.h>

using nx::vec2f;
using nx::vec3f;

namespace nx
{

struct Vertex2d
{
    /**
     * @brief Default Vertex2d constructor.
     */
    Vertex2d() :
        position(vec2f()),
        color(vec3f()),
        uv(vec2f())
    { }

    /**
     * @brief Constructor to specify the vertex position with zero values for the rest.
     * @param position = The vertex position.
     */
    Vertex2d(vec2f position) :
        position(position),
        color(vec3f()),
        uv(vec2f())
    { }

    /**
     * @brief Constructor to specify the vertex position with zero values for the rest.
     * @param position = The vertex position.
     * @param uv = The vertex uv position.
     */
    Vertex2d(vec2f position, vec3f color) :
        position(position),
        color(color),
        uv(vec2f())
    { }

    /**
     * @brief Constructor to specify all values.
     * @param position = The vertex position.
     * @param uv = The vertex uv position.
     * @param color = The vertex color.
     */
    Vertex2d(vec2f position, vec3f color, vec2f uv) :
        position(position),
        color(color),
        uv(uv)
    { }

    vec2f position;
    vec3f color;
    vec2f uv;
};

} // namespace nx

#endif // VERTEX_H_INCLUDE
