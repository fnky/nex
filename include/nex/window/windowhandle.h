#ifndef WINDOWHANDLE_H_INCLUDE
#define WINDOWHANDLE_H_INCLUDE

// Windows' HWND is a typedef on struct HWND__*
#if defined(NEX_OS_WIN32)
    struct HWND__;
#endif

namespace nx
{

#ifdef NEX_OS_UNIX
typedef unsigned long WindowHandle;
#elif defined(NEX_OS_WIN32)
typedef HWND__ WindowHandle;
#elif defined (NEX_OS_APPLE)
typedef void* WindowHandle
#endif

} // namespace nx

#endif // WINDOWHANDLE_H_INCLUDE
