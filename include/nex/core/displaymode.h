#ifndef DISPLAYMODE_H_INCLUDE
#define DISPLAYMODE_H_INCLUDE

#include <nex/system/typedefs.h>

#include <vector>

namespace nx
{

class DisplayMode
{
public:

    /**
     * @brief Create a video mode with all members set to zero.
     */
    DisplayMode();

    /**
     * @brief Create a video mode with the specified values.
     * @param width = width of the back buffer.
     * @param height = height of the back buffer.
     * @param bitsPerPixel = number of bits for each pixel.
     */
    DisplayMode(uint32 width, uint32 height, uint32 bitsPerPixel = 32);

    /**
     * @brief Get the current desktop video mode.
     * @return Current desktop video mode.
     */
    static DisplayMode getDesktopMode();

    /**
     * @brief Retrieve all the video modes supported in fullscreen mode.
     * @return Array containing all the supported fullscreen modes.
     */
    static const std::vector<DisplayMode> getFullscreenModes();

    /**
     * @brief Tell whether or not the video mode is valid (only applies to full screen modes).
     * @return True if the video mode is valid for fullscreen mode.
     */
    bool isValid() const;

    uint32 width;
    uint32 height;
    uint32 bitsPerPixel;
};

bool operator ==(const DisplayMode& left, const DisplayMode& right);
bool operator !=(const DisplayMode& left, const DisplayMode& right);
bool operator <(const DisplayMode& left, const DisplayMode& right);
bool operator >(const DisplayMode& left, const DisplayMode& right);
bool operator <=(const DisplayMode& left, const DisplayMode& right);
bool operator >=(const DisplayMode& left, const DisplayMode& right);

} // namespace nx

#endif // DISPLAYMODE_H_INCLUDE
