#include <nex/core/displaymode.h>

#include <algorithm>
#include <functional>

namespace nx
{

DisplayMode::DisplayMode() :
    width(0),
    height(0),
    bitsPerPixel(0)
{ }

DisplayMode::DisplayMode(uint32 width, uint32 height, uint32 bitsPerPixel) :
    width(width),
    height(height),
    bitsPerPixel(bitsPerPixel)
{ }

bool DisplayMode::isValid() const
{
    const std::vector<DisplayMode>& modes = getFullscreenModes();

    return std::find(modes.begin(), modes.end(), *this) != modes.end();
}

bool operator ==(const DisplayMode& left, const DisplayMode& right)
{
    return (left.width        == right.width)        &&
           (left.height       == right.height)       &&
           (left.bitsPerPixel == right.bitsPerPixel);
}

bool operator !=(const DisplayMode& left, const DisplayMode& right)
{
    return !(left == right);
}

bool operator <(const DisplayMode& left, const DisplayMode& right)
{
    if (left.bitsPerPixel == right.bitsPerPixel)
    {
        if (left.width == right.width)
        {
            return left.height < right.height;
        }
        else
        {
            return left.width < right.width;
        }
    }
    else
    {
        return left.bitsPerPixel < right.bitsPerPixel;
    }
}

bool operator >(const DisplayMode& left, const DisplayMode& right)
{
    return right < left;
}

bool operator <=(const DisplayMode& left, const DisplayMode& right)
{
    return !(right < left);
}

bool operator >=(const DisplayMode& left, const DisplayMode& right)
{
    return !(left < right);
}

} // namespace nx
