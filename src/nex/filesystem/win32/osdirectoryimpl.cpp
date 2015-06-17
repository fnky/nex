#include <nex/filesystem/directory.h>
#include <nex/filesystem/path.h>

/**
 * Win32 directory implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace nx
{

std::vector<std::string> split(const std::string& string)
{
    std::vector<std::string> tokens;

    char* ptr = strtok((char*)string.c_str(), "\\/");
    tokens.push_back(std::string(ptr));
    while(ptr != 0) {
        ptr = strtok(0, "\\/");
        if (ptr != 0)
            tokens.push_back(std::string(ptr));
    }
    return tokens;
}

bool Directory::exists(const std::string& path)
{
    
}

void Directory::create(const std::string& path)
{
    /*std::vector<std::string> tokens = split(path);

    std::string fullPath;
    for (auto& token : tokens)
    {
        fullPath += token + '/';
        mkdir(fullPath.c_str(), 0777);
    }*/
}

void Directory::remove(const std::string& dirname)
{

    
}

std::vector<DirectoryInfo> Directory::getDirectories(const std::string& dirname)
{
   
}

std::vector<FileInfo> Directory::getFiles(const std::string& dirname)
{
    
}

} // namespace nx
