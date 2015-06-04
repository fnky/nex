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

} //namespace nx
