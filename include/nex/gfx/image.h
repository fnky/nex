#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

#include <nex/system/typedefs.h>

#include <nex/gfx/color.h>

namespace nx
{

class Image
{
public:
    Image();
    ~Image();

    void create(uint32 width, uint32 height, const Color& color = Color(0, 0, 0));
};

} // namespace nx

#endif // IMAGE_H_INCLUDE
