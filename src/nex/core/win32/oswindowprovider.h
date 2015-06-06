#ifndef OSWINDOWPROVIDER_H_INCLUDE
#define OSWINDOWPROVIDER_H_INCLUDE

#include <nex/core/windowprovider.h>

/////////////////////////////////////////////////
/// Windows Implementation of the GfxProvider  //
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

    /**
     * @brief Only register the class on the first window class.
     */
    bool mHasRegisteredClass;

    /**
     * @brief Registers the window class.
     */
    void registerClass();
};

} // namespace priv
} // namespace nx

#endif // OSWINDOWPROVIDER_H_INCLUDE
