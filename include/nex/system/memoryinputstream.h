#ifndef MEMORYINPUTSTREAM_H_INCLUDE
#define MEMORYINPUTSTREAM_H_INCLUDE

// Nex includes.
#include <nex/system/instream.h>

// Standard includes.
#include <cstdlib>

namespace nx
{

class MemoryInputStream
{
public:

    /**
     * @brief Default constructor.
     */
    MemoryInputStream();

    /**
     * @brief Open the memory stream from the specified buffer.
     * @param data = The pointer to the data in memory.
     * @param size = Size of the data, in bytes.
     */
    void open(const void* data, int64 size);

    /**
     * @brief Read data from the stream.
     * @param data = Buffer where to copy the read data.
     * @param size = The number of bytes to read.
     * @return the number of bytes red, or -1 on error.
     */
    virtual int64 read(void* data, int64 size);

    /**
     * @brief Change the current reading position.
     * @param position = The position to seek to, from the beginning.
     * @return The position actually sought to, or -1 on error.
     */
    virtual int64 seek(int64 position);

    /**
     * @brief Get the current reading position in the stream.
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
     * @brief Pointer to the data in memory.
     */
    const uint8* mData;

    /**
     * @brief The number of bytes in the data.
     */
    int64 mSize;

    /**
     * @brief The streams current reading offset.
     */
    int64 mOffset;
};

} // namespace nx

#endif // MEMORYINPUTSTREAM_H_INCLUDE
