#ifndef FILE_H_INCLUDE
#define FILE_H_INCLUDE

#include <nex/system/typedefs.h>

#include <string>

namespace nx
{

enum FileMode
{
    FILE_MODE_READ = 0,
    FILE_MODE_WRITE = 1,
    FILE_MODE_READWRITE = 2
};

class File
{
public:

    /**
     * @brief Check if the specified file exists.
     * @param path = Path to the file to check.
     * @return true if the file was found.
     */
    static bool exists(const std::string& path);

    /**
     * @brief Remove the specified file.
     * @param path = Path to the file to remove.
     */
    static void remove(const std::string& path);
};

} // namespace nx

#endif // FILE_H_INCLUDE
