#ifndef WINDOWHANDLE_H_INCLUDE
#define WINDOWHANDLE_H_INCLUDE

// Windows' HWND is a typedef on struct HWND__*
#if defined(NEX_OS_WIN32)
    struct HWND__;
#endif

namespace nx
{

#if defined(NEX_OS_WIN32)

    // Window handle is HWND (HWND__*) on Windows
    typedef HWND__* WindowHandle;

#elif defined(NEX_OS_UNIX)

    // Window handle is Window (unsigned long) on Unix - X11
    typedef unsigned long WindowHandle;

#endif

} // namespace nx

#endif // WINDOWHANDLE_H_INCLUDE
