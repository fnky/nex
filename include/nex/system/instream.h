#ifndef INSTREAM_H_INCLUDE
#define INSTREAM_H_INCLUDE

#include <nex/system/typedefs.h>

namespace nx
{

class InStream
{
public:

    /**
     * @brief Virtual stream destructor.
     */
    virtual ~InStream();

    /**
     * @brief Read data from the stream.
     * @param data = Buffer where to copy the read data.
     * @param size = The number of bytes to read.
     * @return The number of bytes actually read, or -1 on error.
     */
    virtual int64 read(void* data, int64 size) = 0;

    /**
     * @brief Change the current reading position.
     * @param position = The position to seek to, from the beginning.
     * @return = The position actually sought to, or -1 on error.
     */
    virtual int64 seek(int64 position) = 0;

    /**
     * @brief Get the current reading position in the stream.
     * @return The current position, or -1 on error.
     */
    virtual int64 tell() = 0;

    /**
     * @brief Return the size of the stream.
     * @return The total number of bytes available in the stream, or -1 on error.
     */
    virtual int64 size() = 0;
};

} //namespace nx

#endif // INSTREAM_H_INCLUDE
