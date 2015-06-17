#include <nex/filesystem/file.h>


/**
 * Unix file implementation.
 */

#include <unistd.h>

namespace nx
{

bool File::exists(const std::string& path)
{
    return (access(path.c_str(), F_OK) != -1 );
}

void File::remove(const std::string &path)
{
    ::remove(path.c_str());
}

} // namespace nx
