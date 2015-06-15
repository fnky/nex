#ifndef DIRECTORY_H_INCLUDE
#define DIRECTORY_H_INCLUDE

#include <nex/filesystem/directoryinfo.h>
#include <nex/filesystem/fileinfo.h>

#include <string>
#include <vector>

namespace nx
{

class Directory
{
public:

    /**
     * @brief Check if the specified directory exists.
     * @param path = The path to the directory.
     * @return true if the directory exists.
     */
    static bool exists(const std::string& path);

    /**
     * @brief Create the directory specified if it doesn't exists.
     * @param path = The path to create.
     */
    static void create(const std::string& path);

    /**
     * @brief Remove the directory specified if it exists.
     * @param path = The path to create.
     */
    static void remove(const std::string& path);

    /**
     * @brief Get a list of all the sub directories in a folder (not recursive).
     * @param dir = The path to the directory.
     * @return the list of directories found.
     */
    static std::vector<DirectoryInfo> getDirectories(const std::string& dir);

    /**
     * @brief Get a list of all files in the directory.
     * @param dir = The path to the directory.
     * @return the list of files found in the directory.
     */
    static std::vector<FileInfo> getFiles(const std::string& dir);
};

} // namespace nx

#endif // DIRECTORY_H_INCLUDE
