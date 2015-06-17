#include <nex/filesystem/directory.h>
#include <nex/filesystem/path.h>

/**
 * Win32 directory implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

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
   /* HANDLE hFind;
    WIN32_FIND_DATA FindFileData;

    std::string dirPath;
    std::string fileName;

    _tcscpy(dirPath, sPath);
    _tcscat(dirPath, "\\*");
    _tcscpy(fileName, sPath);
    _tcscat(fileName, "\\");

    hFind = FindFirstFile(dirPath, &FindFileData);

    if(hFind == INVALID_HANDLE_VALUE)
        return FALSE;

    _tcscpy(dirPath,fileName);

    bool bSearch = true;
    while(bSearch) {

        if (FindNextFile(hFind, &FindFileData)) {

            if (IsDots(FindFileData.cFileName))
                continue;

            _tcscat(fileName, FindFileData.cFileName);

            if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                // we have found a directory, recurse
                if (!remove(fileName)) {
                    FindClose(hFind);
                }
                // remove the empty directory
                RemoveDirectoryA(fileName);
                _tcscpy(fileName,dirPath);
            }
            else {

                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    _chmod(fileName, _S_IWRITE);

                if (!DeleteFile(fileName)) {
                    FindClose(hFind);
                    return FALSE;
                }
                _tcscpy(fileName,dirPath);
            }
        }
        else {

            if(GetLastError() == ERROR_NO_MORE_FILES)
                bSearch = false;

            else {
                // some error occured, close the handle and return FALSE
                FindClose(hFind);
                return FALSE;
            }
        }
    }

    FindClose(hFind);

    return RemoveDirectory(sPath);*/
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
