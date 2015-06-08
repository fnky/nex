#ifndef OSWINDOWPROVIDER_H_INCLUDE
#define OSWINDOWPROVIDER_H_INCLUDE

#include <nex/core/windowprovider.h>

#include <X11/Xlib.h>

/////////////////////////////////////////////////
/// Unix Implementation of the GfxProvider     //
/////////////////////////////////////////////////

namespace nx
{
namespace priv
{

class OSWindowProvider : public WindowProvider
{
public:
    OSWindowProvider();
    ~OSWindowProvider();

    /**
     * @brief Create a gfx provider with the specified video mode and video settings.
     * @param width = video width.
     * @param height = video height.
     * @return true if the window was created sucesfully.
     */
    bool create(uint32 width, uint32 height, Style style);

    /**
     * @brief Destroys the window provider.
     */
    void destroy();

    /**
     * @brief Show the gfx provider.
     */
    void show();

    /**
     * @brief Hide the gfx provider.
     */
    void hide();

private:

    /**
     * @brief The handle to the current window.
     */
    WindowHandle mWindowHandle;

    Display* mDisplay;
    Window mWindow;

    int mScreen;
};

} // namespace priv
} // namespace nx

#endif // OSWINDOWPROVIDER_H_INCLUDE
