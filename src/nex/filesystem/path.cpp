#include <nex/filesystem/path.h>

#include <string.h>

namespace nx
{

std::string Path::combine(const std::string& left, const std::string& right)
{
    return left + DIRECTORY_SEPARATOR + right;
}

//TODO: Handle this case "../../test"
std::string Path::getExtension(const std::string &path)
{
    const char *dot = strrchr(path.c_str(), '.');

    if(!dot || dot == path)
        return "";

    return std::string(dot + 1);
}

} // namespace nx
