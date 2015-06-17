#include <nex/filesystem/path.h>

#include <string.h>

namespace nx
{

std::string Path::combine(const std::string& left, const std::string& right)
{
    return left + DIRECTORY_SEPARATOR + right;
}

std::string Path::getExtension(const std::string &path)
{
    //First use strrchr to find the last '.' in the pathname.
    //If it doesn't exist, there's no "extension".

    const char* last = strrchr(path.c_str(), '.');
    if (last == 0) {
        return 0;
    }

    //Next, use strchr to check whether there's any '/' after the last '.'.
    //If so, the last '.' is in a directory component, not the filename, so there's no extension.

    const char* ptr = strchr(last, DIRECTORY_SEPARATOR);
    while (ptr != 0) {
        if (ptr > last) {
            return "";
        }
        ptr = strchr(ptr+1, DIRECTORY_SEPARATOR);
    }

    //Otherwise, you found the extension. You can use the pointer to the position one past the '.' directly as a C string.
    //No need to copy it to new storage unless the original string will be freed or clobbered before you use it.

    return std::string(last);
}

} // namespace nx
