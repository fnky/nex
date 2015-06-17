#include <nex/filesystem/path.h>

/**
 * Win32 path implementation.
 */

#include <windows.h>
#include "Shlwapi.h"

namespace nx
{

std::string Path::getDirectoryName(const std::string& path)
{
    char buffer[path.size()];

    memcpy(buffer, path.c_str(), path.size());

    PathRemoveFileSpecA(buffer);

    return std::string(buffer);
}

std::string Path::getFileName(const std::string& path)
{
    return ::PathFindFileNameA(path.c_str());
}

std::string Path::getFullPath(const std::string& relative)
{
    char buffer[4096];

    ::GetFullPathNameA(relative.c_str(), 4096, buffer, 0);

    return std::string(buffer);
}

} // namespace nx
