#include <nex/core/unix/oswindowprovider.h>

// Unix specfic includes.
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
/////////////////////////////////////////////////
/// Unix Implementation of the GfxProvider     //
/////////////////////////////////////////////////

namespace nx
{
namespace priv
{

OSWindowProvider::OSWindowProvider() :
    mWindowHandle(0),
    mDisplay(0),
    mWindow(0),
    mScreen(0)
{

}

OSWindowProvider::~OSWindowProvider()
{

}

bool OSWindowProvider::create(uint32 width, uint32 height, Style style)
{
    // Open a connection to the x server.
    mDisplay = XOpenDisplay(NULL);
    mScreen = DefaultScreen(mDisplay);

    ::Window root = XRootWindow(mDisplay, mScreen);

    int count;
    XVisualInfo* visuals = XGetVisualInfo(mDisplay, 0, NULL, &count);

    //TODO: Figure out what to do here.

    //Seems like we need a color map and some sort of visual info.

    return true;
}

void OSWindowProvider::destroy()
{
    // Close our connection to the x server.
    XCloseDisplay(mDisplay);
    mDisplay = 0;
}

void OSWindowProvider::show()
{
    
}

void OSWindowProvider::hide()
{
    
}


} // namespace priv
} // namespace nx
