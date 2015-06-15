#ifndef INSTREAM_H_INCLUDE
#define INSTREAM_H_INCLUDE

#include <nex/system/typedefs.h>

namespace nx
{

class InStream
{
public:

    /**
     * @brief Construct an empty in stream.
     */
    InStream();

    /**
     * @brief Construct a stream with the specified size.
     */
    InStream(int32 size);

    /**
     * @brief Virtual destructor so we call any destructors from overriding classes.
     */
    ~InStream();

    /**
     * @brief Copy the specifed number of bytes into the in stream.
     * @param buffer = The buffer to copy data from.
     * @param offset = The starting point to read data from.
     * @param size = The number of bytes to read.
     */
    void copy(uint8* buffer, uint32 offset, uint32 size);

    /**
     * @brief Read a 8-bit signed integer from the stream.
     * @return int8
     */
    int8 readInt8();

    /**
     * @brief Read a 16-bit signed integer from the stream.
     * @return int16
     */
    int16 readInt16();

    /**
     * @brief Read a 32-bit signed integer from the stream.
     * @return int32
     */
    int32 readInt32();

    /**
     * @brief Read a 64-bit signed integer from the stream.
     * @return int64
     */
    int64 readInt64();

    /**
     * @brief Read a 8-bit unsigned integer from the stream.
     * @return uint8
     */
    uint8 readUint8();

    /**
     * @brief Read a 16-bit unsigned integer from the stream.
     * @return uint16
     */
     uint16 readUint16();

    /**
     * @brief Read a 32-bit unsigned integer from the stream.
     * @return uint32
     */
    uint32 readUint32();

    /**
     * @brief Read a 64-bit unsigned integer from the stream.
     * @return uint64
     */
    uint64 readUint64();

    /**
     * @brief Read a 32-bit floating point number from the stream.
     * @return 32-bit floating pointer number.
     */
    real32 readReal32();

    /**
     * @brief Read a 64-bit floatinb point number from the stream.
     * @return 64-bit floating point number.
     */
    real64 readReal64();

    /**
     * @brief The current location where we will be reading data from.
     * @return the streams current offset.
     */
    uint32 getOffset() const { return mOffset; }

    /**
     * @brief Set the current offset where we will be reading dadta from.
     * @param offset
     */
    void setOffset(uint32 offset) { mOffset = offset; }

    /**
     * @brief Get the size of the current buffer.
     * @return size in bytes.
     */
    uint32 getSize() const { return mSize; }

protected:

    /**
     * @brief The current reading offset.
     */
    uint32 mOffset;

    /**
     * @brief The size of the buffer.
     */
    uint32 mSize;

    /**
     * @brief The actual byte buffer.
     */
    uint8* mBuffer;
};

} //namespace nx

#endif // INSTREAM_H_INCLUDE
