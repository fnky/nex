#ifndef OUTSTREAM_H_INCLUDE
#define OUTSTREAM_H_INCLUDE

#include <nex/system/typedefs.h>

namespace nx
{

class OutStream
{
public:

    /**
     * @brief Construct an empty out stream.
     */
    OutStream();

    /**
     * @brief Construct a stream with the specified size.
     */
    OutStream(int32 size);

    /**
     * @brief Virtual destructor so we call any destructors from overriding classes.
     */
    virtual ~OutStream();

    /**
     * @brief Write a signed 8-bit number to the stream.
     * @param value = 8-bit signed number.
     */
    virtual void writeInt8(const int8 value) = 0;

    /**
     * @brief Write a signed 16-bit number to the stream.
     * @param value = 16-bit signed number.
     */
    virtual void writeInt16(const int16 value) = 0;

    /**
     * @brief Write a signed 32-bit number to the stream.
     * @param value = 32-bit signed number.
     */
    virtual void writeInt32(const int32 value) = 0;

    /**
     * @brief Write a signed 64-bit number to the stream.
     * @param value = 64-bit signed number.
     */
    virtual void writeInt64(const int64 value) = 0;

    /**
     * @brief Write a unsigned 8-bit number to the stream.
     * @param value = 8-bit unsigned number.
     */
    virtual void writeUint8(const uint8 value) = 0;

    /**
     * @brief Write a unsigned 16-bit number to the stream.
     * @param value = 16-bit unsigned number.
     */
    virtual void writeUint16(const uint16 value) = 0;

    /**
     * @brief Write a unsigned 32-bit number to the stream.
     * @param value = 32-bit unsigned number.
     */
    virtual void writeUint32(const uint32 value) = 0;

    /**
     * @brief Write a unsigned 64-bit number to the stream.
     * @param value = 64-bit unsigned number.
     */
    virtual void writeUint64(const uint64 value) = 0;

    /**
     * @brief Write a 32-bit floating pointer number to the stream.
     * @param value = 32-bit floating pointer number.
     */
    virtual void writeReal32(const real32 value) = 0;

    /**
     * @brief Write a 64-bit floating pointer number to the stream.
     * @param value = 64-bit floating pointer number.
     */
    virtual void writeReal64(const real64 value) = 0;

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
};

} //namespace nx

#endif // OUTSTREAM_H_INCLUDE
