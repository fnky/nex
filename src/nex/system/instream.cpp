#include <nex/system/instream.h>

namespace nx
{

InStream::InStream() :
    mOffset(0),
    mSize(0)
{ }

InStream::InStream(int32 size) :
    mOffset(0),
    mSize(size)
{ }

void InStream::copy(uint8* buffer, uint32 offset, uint32 size)
{

}

int8 InStream::readInt8()
{
    return mBuffer[mOffset++];
}

} //namespace nx
