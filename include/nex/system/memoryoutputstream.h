#ifndef MEMORYOUTPUTSTREAM_H_INCLUDE
#define MEMORYOUTPUTSTREAM_H_INCLUDE

// Nex includes.
#include <nex/system/outstream.h>

namespace nx
{

class MemoryOutputStream
{

public:

    /**
     * @brief Default constructor.
     */
    MemoryOutputStream();

    /**
     * @brief Open the memory stream from the specified buffer.
     * @param data = The pointer to the data in memory.
     * @param size = Size of the buffer, in bytes.
     */
    void open(void* data, int64 size);

    /**
     * @brief Write data to the stream.
     * @param data = Buffer where to read the data from.
     * @param size = The number of bytes to read.
     * @return the number of bytes written, or -1 on error.
     */
    virtual int64 write(void* data, int64 size);

    /**
     * @brief Change the current writing position.
     * @param position = The position to seek to, from the beginning.
     * @return The position actually sought to, or -1 on error.
     */
    virtual int64 seek(int64 position);

    /**
     * @brief Get the current writing position in the stream.
     * @return The current position, or -1 on error.
     */
    virtual int64 tell();

    /**
     * @brief  Return the size of the stream.
     * @return The total number of bytes available in the stream, or -1 on error.
     */
    virtual int64 size();

private:

    /**
     * @brief Pointer to the buffer into which we will write.
     */
    uint8* mData;

    /**
     * @brief The size of the destination buffer.
     */
    int64 mSize;

    /**
     * @brief Our current writing offset.
     */
    int64 mOffset;
};

} // namespace nx

#endif // MEMORYOUTPUTSTREAM_H_INCLUDE
