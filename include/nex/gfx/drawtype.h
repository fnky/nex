#ifndef DRAWTYPE_H_INCLUDE
#define DRAWTYPE_H_INCLUDE

#include <GL/glew.h>

namespace nx
{

enum DrawType
{
    DRAW_TYPE_STATIC = GL_STATIC_DRAW,
    DRAW_TYPE_DYNAMIC = GL_DYNAMIC_DRAW,
    DRAW_TYPE_STREAM = GL_STREAM_DRAW
};

} // namespace nx

#endif // DRAWTYPE_H_INCLUDE
