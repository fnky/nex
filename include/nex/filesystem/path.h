#ifndef PATH_H_INCLUDE
#define PATH_H_INCLUDE

#include <string>

namespace nx
{

#ifdef NEX_OS_UNIX
const char DIRECTORY_SEPARATOR =  '/';
#elif defined(NEX_OS_WIN32)
const char DIRECTORY_SEPARATOR =  '\\';
#endif

class Path
{

public:

    /**
     * @brief Combine two directories using the proper path seperator.
     * @param left = Left directory.
     * @param right = Right directory.
     * @return directory path.
     */
    static std::string combine(const std::string& left, const std::string& right);

    /**
     * @brief Returns the extension of the specified path string.
     * @param path = The path to the file.
     * @return the file extention if any.
     */
    static std::string getExtension(const std::string& path);

    /**
     * @brief Returns the directory name for the specified path string.
     * @param path = The path to the directory.
     * @return the directory name.
     */
    static std::string getDirectoryName(const std::string& path);

    /**
     * @brief Returns the file name and extension of the specified path string.
     * @param path = The path to the file.
     * @return the file name.
     */
    static std::string getFileName(const std::string& path);

    /**
     * @brief Returns the absolute path for the specified path string.
     * @param relative = The relative path.
     * @return the absolute path.
     */
    static std::string getFullPath(const std::string& relative);

};

} // namespace nx

#endif // PATH_H_INCLUDE
