#ifndef VERTEX_H_INCLUDE
#define VERTEX_H_INCLUDE

#include <nex/math/vec2.h>
#include <nex/math/vec3.h>

using nx::vec2f;
using nx::vec3f;

namespace nx
{

struct Vertex3d
{

    /**
     * @brief Default Vertex3d Constructor (All zeros).
     */
    Vertex3d() :
        position(vec3f()),
        color(vec3f()),
        uv(vec2f()),
        normal(vec3f())
    { }

    /**
     * @brief Constructor to define the vertex position (The rest are zeros).
     * @param position = The vertex position.
     */
    Vertex3d(vec3f position) :
        position(position),
        color(vec3f()),
        uv(vec2f()),
        normal(vec3f())
    { }

    /**
     * @brief Constructor to define the vertex position and color (The rest are zeros).
     * @param position = The vertex position.
     * @param color = The vertex color.
     */
    Vertex3d(vec3f position, vec3f color) :
        position(position),
        color(color),
        uv(vec2f()),
        normal(vec3f())
    { }

    /**
     * @brief Constructor to define the vertex position, color and uv (The rest are zeros).
     * @param position = The vertex position.
     * @param color = The vertex color.
     * @param uv = The uv color.
     */
    Vertex3d(vec3f position, vec3f color, vec2f uv) :
        position(position),
        color(color),
        uv(uv),
        normal(vec3f())
    { }

    /**
     * @brief Constructor to define the vertex position, color, uv and normal.
     * @param position = The vertex position.
     * @param color = The vertex color.
     * @param uv = The vertex texture uv.
     * @param normal = The vertex normal.
     */
    Vertex3d(vec3f position, vec3f color, vec2f uv, vec3f normal) :
        position(position),
        color(color),
        uv(uv),
        normal(normal)
    { }

    vec3f position;
    vec3f color;
    vec2f uv;
    vec3f normal;
};

} // namespace nx

#endif // VERTEX_H_INCLUDE
