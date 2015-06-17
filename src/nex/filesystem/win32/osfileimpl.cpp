#include <nex/filesystem/file.h>

/**
 * Win32 file implementation.
 */

#include <windows.h>
#include "Shlwapi.h"
namespace nx
{

bool File::exists(const std::string& path)
{
    return ::PathFileExistsA(path.c_str());
}

void File::remove(const std::string &path)
{
    ::DeleteFileA(path.c_str());
}

} // namespace nx
