#include <nex/filesystem/fileinputstream.h>


namespace nx
{

FileInputStream::FileInputStream() :
    mFile(0)
{ }

FileInputStream::~FileInputStream()
{
    close();
}

bool FileInputStream::open(const std::string& filepath)
{
    if (mFile)
        close();

    mFile = std::fopen(filepath.c_str(), "rb");

    return mFile != 0;
}

void FileInputStream::close()
{
    if (mFile) {
        std::fclose(mFile);
        mFile = 0;
    }
}

int64 FileInputStream::read(void *data, int64 size)
{
    if (mFile)
           return std::fread(data, 1, static_cast<std::size_t>(size), mFile);
       else
           return -1;
}

int64 FileInputStream::seek(int64 position)
{
    if (mFile)
    {
       std::fseek(mFile, static_cast<std::size_t>(position), SEEK_SET);
       return tell();
    }
    else
    {
       return -1;
    }
}

int64 FileInputStream::tell()
{
    if (mFile)
        return std::ftell(mFile);
    else
        return -1;
}

int64 FileInputStream::size()
{
    if (mFile)
    {
        int64 position = tell();
        std::fseek(mFile, 0, SEEK_END);
        int64 size = tell();
        seek(position);
        return size;
    }
    else
    {
        return -1;
    }
}

} // namespace tx
