#ifndef WINDOWSTYLE_H_INCLUDE
#define WINDOWSTYLE_H_INCLUDE

namespace nx
{
enum Style
{
    None       = 0,      // No border / title bar (this flag and all others are mutually exclusive)
    Titlebar   = 1 << 0, // Title bar + fixed border
    Resize     = 1 << 1, // Title bar + resizeable border + maximize button
    Close      = 1 << 2, // Title bar + close button
    Fullscreen = 1 << 3, // Full-screen mode (this flag and all others are mutually exclusive)

    Default = Titlebar | Resize | Close // Default window style
};
} // namespace nx


#endif // WINDOWSTYLE_H_INCLUDE
