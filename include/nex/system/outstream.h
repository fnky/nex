#ifndef OUTSTREAM_H_INCLUDE
#define OUTSTREAM_H_INCLUDE

#include <nex/system/typedefs.h>

namespace nx
{

class OutStream
{
public:

    /**
     * @brief Virtual destructor.
     */
    virtual ~OutStream();

    /**
     * @brief Write data to the stream.
     * @param data = Buffer to read from.
     * @param size = The number of bytes to read.
     * @return The number of bytes actually writtens, or -1 on error.
     */
    virtual int64 write(void* data, int64 size) = 0;

    /**
     * @brief Change the current writing position.
     * @param position = The position to seek to, from the beginning.
     * @return = The position actually sought to, or -1 on error.
     */
    virtual int64 seek(int64 position) = 0;

    /**
     * @brief Get the current writing position in the stream.
     * @return The current position, or -1 on error.
     */
    virtual int64 tell() = 0;

    /**
     * @brief Return the size of the stream.
     * @return The total number of bytes in the stream, or -1 on error.
     */
    virtual int64 size() = 0;
};

} //namespace nx

#endif // OUTSTREAM_H_INCLUDE
