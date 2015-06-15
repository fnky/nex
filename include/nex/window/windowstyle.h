#ifndef WINDOWSTYLE_H_INCLUDE
#define WINDOWSTYLE_H_INCLUDE

namespace nx
{

enum Style
{
    None        = 0,
    Titlebar    = 1 << 0,
    Resize      = 1 << 1,
    Close       = 1 << 2,
    Fullscreen  = 1 << 3,

    Default     = Titlebar | Resize | Close
};

} // namespace nx

#endif // WINDOWSTYLE_H_INCLUDE
