#include <nex/core/windowprovider.h>

#ifdef NEX_OS_WIN32
#include <nex/core/win32/oswindowprovider.h>
#elif defined(NEX_OS_UNIX)
#include <nex/core/unix/oswindowprovider.h>
#endif

namespace nx
{

WindowProvider* WindowProvider::newInstance()
{
    return new priv::OSWindowProvider();
}

WindowProvider::WindowProvider()
{ }

WindowProvider::~WindowProvider()
{ }

} // namespace nx
