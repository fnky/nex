#ifndef GFXPROVIDER_H_INCLUDE
#define GFXPROVIDER_H_INCLUDE

#include <nex/system/typedefs.h>

#include <nex/core/windowhandle.h>
#include <nex/core/windowstyle.h>

namespace nx
{

class WindowProvider
{
public:
    WindowProvider();
    virtual ~WindowProvider();

    /**
     * @brief Create a new instance based on the current operating system.
     * @return the new instance of the window provider.
     */
    static WindowProvider* newInstance();

    /**
     * @brief Create a window provider with the specified video mode and video settings.
     * @param width = video width.
     * @param height = video height.
     * @return true if the window was created sucesfully.
     */
    virtual bool create(uint32 width, uint32 height, Style style) = 0;

    /**
     * @brief Show the window provider.
     */
    virtual void show() = 0;

    /**
     * @brief Hide the window provider.
     */
    virtual void hide() = 0;
};

} // namespace nx

#endif // GFXPROVIDER_H_INCLUDE
