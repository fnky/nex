#include <nex/filesystem/fileoutputstream.h>

namespace nx
{

FileOutputStream::FileOutputStream() :
    mFile(0)
{ }

FileOutputStream::~FileOutputStream()
{ }

bool FileOutputStream::open(const std::string& filepath)
{
    if (mFile)
        close();

    mFile = std::fopen(filepath.c_str(), "wb");

    return mFile != 0;
}

void FileOutputStream::close()
{
    if (mFile) {
        std::fclose(mFile);
        mFile = 0;
    }
}

int64 FileOutputStream::write(void* data, int64 size)
{
    if (mFile)
           return std::fwrite(data, 1, static_cast<std::size_t>(size), mFile);
       else
           return -1;
}

int64 FileOutputStream::seek(int64 position)
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

int64 FileOutputStream::tell()
{
    if (mFile)
        return std::ftell(mFile);
    else
        return -1;
}

int64 FileOutputStream::size()
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

} // namespace nx
