#include <nex/system/memoryoutputstream.h>

#include <cstring>

namespace nx
{

MemoryOutputStream::MemoryOutputStream() :
    mData(0),
    mSize(0),
    mOffset(0)
{ }

void MemoryOutputStream::open(void *data, int64 size)
{
    mData = static_cast<uint8*>(data);
    mSize = size;
    mOffset = 0;
}

int64 MemoryOutputStream::write(void *data, int64 size)
{
    if (!mData)
        return -1;

    int64 endPosition = mOffset + size;
    int64 count = endPosition <= mSize ? size : mSize - mOffset;

    if (count > 0)
    {
        std::memcpy(mData + mOffset, data, static_cast<std::size_t>(count));
        mOffset += count;
    }

    return count;
}

int64 MemoryOutputStream::seek(int64 position)
{
    if (!mData)
        return -1;

    mOffset = position < mSize ? position : mSize;

    return mOffset;
}

int64 MemoryOutputStream::tell()
{
    if (!mData)
        return -1;

    return mOffset;
}

int64 MemoryOutputStream::size()
{
    if (!mData)
        return -1;

    return mSize;
}

} // namespace nx
