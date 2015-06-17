#include <nex/filesystem/directory.h>
#include <nex/filesystem/path.h>
/**
 *
 * Unix directory implementation.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

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
    struct stat sb;
    return (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
}

void Directory::create(const std::string& path)
{
    std::vector<std::string> tokens = split(path);

    std::string fullPath;
    for (auto& token : tokens)
    {
        fullPath += token + '/';
        mkdir(fullPath.c_str(), 0777);
    }
}

void Directory::remove(const std::string& dirname)
{

    DIR* dir;
    struct dirent* entry;
    std::string path;

    dir = opendir(dirname.c_str());
    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {

            path = dirname + "/" + std::string(entry->d_name);
            if (entry->d_type == DT_DIR) {
                remove(path);
            }

            /*
             * Here, the actual deletion must be done.  Beacuse this is
             * quite a dangerous thing to do, and this program is not very
             * well tested, we are just printing as if we are deleting.
             */
            //printf(%s\n", path);
            //std::cout << "(not really) Deleting: " << path << std::endl;
            /*
             * When you are finished testing this and feel you are ready to do the real
             * deleting, use this: remove*STUB*(path);
             * (see "man 3 remove")
             * Please note that I DONT TAKE RESPONSIBILITY for data you delete with this!
             */
            ::remove(path.c_str());
        }

    }
    closedir(dir);

    ::remove(dirname.c_str());
    /*
     * Now the directory is emtpy, finally delete the directory itself. (Just
     * printing here, see above)
     */
    //printf("(not really) Deleting: %s\n", dirname);
    //std::cout << "not really) Deleting:" << dirname << std::endl;
}

std::vector<DirectoryInfo> Directory::getDirectories(const std::string& dirname)
{
    DIR* dir;
    struct dirent* entry;
    std::string path;

    std::vector<DirectoryInfo> directories;

    dir = opendir(dirname.c_str());
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {

            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {

                path = dirname + "/" + std::string(entry->d_name);
                if (entry->d_type == DT_DIR) {

                    DirectoryInfo info;
                    info.name = Path::getDirectoryName(path);
                    info.path = path;

                    directories.push_back(info);
                }
            }

        }
    }
    closedir(dir);

    return directories;
}

std::vector<FileInfo> Directory::getFiles(const std::string& dirname)
{
    DIR* dir;
    struct dirent* entry;
    std::string path;

    std::vector<FileInfo> files;

    dir = opendir(dirname.c_str());
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {

            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {

                path = dirname + "/" + std::string(entry->d_name);
                if (entry->d_type != DT_DIR) {

                    FileInfo info;
                    info.path = path;
                    info.name = Path::getFileName(path);
                    info.extention = Path::getExtension(path);

                    files.push_back(info);
                }
            }

        }
    }
    closedir(dir);

    return files;
}

} // namespace nx
