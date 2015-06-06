#include <nex/core/win32/oswindowprovider.h>

#include <windows.h>

/////////////////////////////////////////////////
/// Windows Implementation of the GfxProvider  //
/////////////////////////////////////////////////

namespace nx
{
namespace priv
{

OSWindowProvider::OSWindowProvider() :
    mWindowHandle(0)
{

}

OSWindowProvider::~OSWindowProvider()
{

}

bool OSWindowProvider::create(uint32 width, uint32 height, Style style)
{
    /*//Only register our class on the first class.
    if (!mHasRegistedClass) {
        registerClass();
        mHasRegistedClass = true;
    }

    // Choose the window style according to the Style parameter
    DWORD win32Style = WS_VISIBLE;
    if (style == Style::None)
    {
        win32Style |= WS_POPUP;
    }
    else
    {
        if (style & Style::Titlebar) win32Style |= WS_CAPTION | WS_MINIMIZEBOX;
        if (style & Style::Resize)   win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
        if (style & Style::Close)    win32Style |= WS_SYSMENU;
    }

    // In windowed mode, adjust width and height so that window will have the requested client area
    bool fullscreen = (style & Style::Fullscreen) != 0;
    if (!fullscreen)
    {
        RECT rectangle = {0, 0, width, height};
        AdjustWindowRect(&rectangle, win32Style, false);
        width  = rectangle.right - rectangle.left;
        height = rectangle.bottom - rectangle.top;
    }

    // Create the window
    m_handle = CreateWindowW(className, title.toWideString().c_str(), win32Style, left, top, width, height, NULL, NULL, GetModuleHandle(NULL), this);

    // By default, the OS limits the size of the window the the desktop size,
    // we have to resize it after creation to apply the real size
    setSize(Vector2u(mode.width, mode.height));

    // Switch to fullscreen if requested
    if (fullscreen)
        switchToFullscreen(mode);*/

    return true;
}

void OSWindowProvider::registerClass()
{
    WNDCLASSEX wcex;
    /*wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "Nex Engine";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);*/
}

void OSWindowProvider::show()
{
    if (mWindowHandle) {
        ShowWindow(mWindowHandle, SW_HIDE);
    }
}

void OSWindowProvider::hide()
{
    if (mWindowHandle) {
        ShowWindow(mWindowHandle, SW_SHOW);
    }
}


} // namespace priv
} // namespace nx
