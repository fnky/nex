#include <nex/system/memoryinputstream.h>

#include <cstring>

namespace nx
{

MemoryInputStream::MemoryInputStream() :
    mData(0),
    mSize(0),
    mOffset(0)
{ }

void MemoryInputStream::open(const void *data, int64 size)
{
    mData = static_cast<const uint8*>(data);
    mSize = size;
    mOffset = 0;
}

int64 MemoryInputStream::read(void *data, int64 size)
{
    if (!mData)
        return -1;

    int64 endPosition = mOffset + size;
    int64 count = endPosition <= mSize ? size : mSize - mOffset;

    if (count > 0)
    {
        std::memcpy(data, mData + mOffset, static_cast<std::size_t>(count));
        mOffset += count;
    }

    return count;
}

int64 MemoryInputStream::seek(int64 position)
{
    if (!mData)
        return -1;

    mOffset = position < mSize ? position : mSize;

    return mOffset;
}

int64 MemoryInputStream::tell()
{
    if (!mData)
        return -1;

    return mOffset;
}

int64 MemoryInputStream::size()
{
    if (!mData)
        return -1;

    return mSize;
}

} // namespace nx
