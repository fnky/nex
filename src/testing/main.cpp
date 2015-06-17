#include <iostream>

#include <nex/filesystem/path.h>
#include <nex/filesystem/file.h>
#include <nex/filesystem/directory.h>

using namespace nx;


int main(int argc, char** args)
{
    std::string folderPath = Path::combine(Path::combine("..", ".."), "test");

    std::vector<DirectoryInfo> folders = Directory::getDirectories(folderPath);
    std::vector<FileInfo> files = Directory::getFiles(folderPath);

    std::string filePath = Path::combine(folderPath, "afile.lua");

    std::string folderName = Path::getDirectoryName(folderPath);
    std::string fileName = Path::getFileName(filePath);

    std::string fullPath = Path::getFullPath(filePath);

    std::string fileExt = Path::getExtension(filePath);
    return 0;
}
