#include <nex/filesystem/path.h>

#include <string.h>
#include <libgen.h>
#include <stdlib.h>

namespace nx
{

std::string Path::getDirectoryName(const std::string& path)
{
    char* dirc;
    char* basec;
    char* bname;
    char* dname;

    dirc = strdup(path.c_str());
    basec = strdup(path.c_str());
    dname = dirname(dirc);
    bname = basename(basec);

    return std::string(bname);
}

std::string Path::getFileName(const std::string& path)
{
    char* dirc;
    char* basec;
    char* bname;
    char* dname;

    dirc = strdup(path.c_str());
    basec = strdup(path.c_str());
    dname = dirname(dirc);
    bname = basename(basec);

    return std::string(bname);
}

std::string Path::getFullPath(const std::string& relative)
{
    // If you have a path longer than this, go fuck your self.
    char buffer[4096];

    char* ptr = realpath(relative.c_str(), buffer);

    if (ptr == 0) {
        return std::string("");
    }

    return std::string(ptr);
}

} // namespace nx
