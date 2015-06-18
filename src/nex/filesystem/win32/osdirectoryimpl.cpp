#include <nex/filesystem/directory.h>
#include <nex/filesystem/path.h>

/**
 * Win32 directory implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <iostream>
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
    DWORD dwAttrib = GetFileAttributesA(path.c_str());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
            (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void Directory::create(const std::string& path)
{
    std::vector<std::string> tokens = split(path);

    std::string fullPath;
    for (auto& token : tokens)
    {
        fullPath += token + '/';

        ::CreateDirectoryA(fullPath.c_str(), 0);
    }
}

void Directory::remove(const std::string& dirname)
{
    WIN32_FIND_DATA FindFileData;

    std::string searchPath = dirname;
    searchPath += "\\*.*";

    std::string currentFile = "";

    HANDLE hFind = FindFirstFile(searchPath.c_str(), &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }
    else
    {
        do
        {
            // Check if its a directory...
            if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                std::string filePath = FindFileData.cFileName;

                // Ignore '.' and '..'
                if (strcmp(".", filePath.c_str()) && strcmp("..", filePath.c_str())) {

                    searchPath = dirname + "\\" + filePath;
                    remove(searchPath);
                }
            }
            else
            {
                searchPath = dirname + "\\";
                currentFile = searchPath + FindFileData.cFileName;
                ::DeleteFileA(currentFile.c_str());
            }
        }
        while (FindNextFile(hFind, &FindFileData) != 0);

        FindClose(hFind);
    }
    ::RemoveDirectoryA(dirname.c_str());
}

std::vector<DirectoryInfo> Directory::getDirectories(const std::string& dirname)
{
    WIN32_FIND_DATA filePtr;

    std::string tempPath = dirname;
    tempPath += "\\*.*";

    std::string currFile = "";

    std::vector<DirectoryInfo> found;

    HANDLE hFind = FindFirstFile(tempPath.c_str(), &filePtr );
    if (hFind == INVALID_HANDLE_VALUE) {
       return found;
    }
    else
    {
        do
        {
            //check if its a directory...
            if ((filePtr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
            {
                std::string filePath = filePtr.cFileName;
                //ignore '.' and '..'
                if (strcmp(".", filePath.c_str()) && strcmp("..", filePath.c_str()))
                {
                    tempPath = dirname + "\\" + filePath;

                    DirectoryInfo info;
                    info.path = tempPath;
                    info.name = filePath;

                    found.push_back(info);
                }
            }
            else
            {
                tempPath = dirname + "\\";
                currFile = tempPath + filePtr.cFileName;
            }
        }
        while (FindNextFile(hFind, &filePtr) != 0);

        FindClose(hFind);

    }

    return found;
}

std::vector<FileInfo> Directory::getFiles(const std::string& dirname)
{
    WIN32_FIND_DATA filePtr;

    std::string tempPath = dirname;
    tempPath += "\\*.*";

    std::string currFile = "";

    std::vector<FileInfo> found;

    HANDLE hFind = FindFirstFile(tempPath.c_str(), &filePtr );
    if (hFind == INVALID_HANDLE_VALUE) {
       return found;
    }
    else
    {
        do
        {
            //check if its a file.
            if (!(filePtr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
            {
                tempPath = dirname + "\\";
                currFile = tempPath + filePtr.cFileName;

                FileInfo info;

                info.path = currFile;
                info.name = filePtr.cFileName;
                info.extention = Path::getExtension(currFile);

                found.push_back(info);
            }
        }
        while (FindNextFile(hFind, &filePtr) != 0);

        FindClose(hFind);

    }

    return found;
}

} // namespace nx
