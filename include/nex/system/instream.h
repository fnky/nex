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
    virtual ~InStream();

    /**
     * @brief Read a 8-bit signed integer from the stream.
     * @return int8
     */
    virtual int8 readInt8() = 0;

    /**
     * @brief Read a 16-bit signed integer from the stream.
     * @return int16
     */
    virtual int16 readInt16() = 0;

    /**
     * @brief Read a 32-bit signed integer from the stream.
     * @return int32
     */
    virtual int32 readInt32() = 0;

    /**
     * @brief Read a 64-bit signed integer from the stream.
     * @return int64
     */
    virtual int64 readInt64() = 0;

    /**
     * @brief Read a 8-bit unsigned integer from the stream.
     * @return uint8
     */
    virtual uint8 readUint8() = 0;

    /**
     * @brief Read a 16-bit unsigned integer from the stream.
     * @return uint16
     */
    virtual uint16 readUint16() = 0;

    /**
     * @brief Read a 32-bit unsigned integer from the stream.
     * @return uint32
     */
    virtual uint32 readUint32() = 0;

    /**
     * @brief Read a 64-bit unsigned integer from the stream.
     * @return uint64
     */
    virtual uint64 readUint64() = 0;

    /**
     * @brief Read a 32-bit floating point number from the stream.
     * @return 32-bit floating pointer number.
     */
    virtual real32 readReal32() = 0;

    /**
     * @brief Read a 64-bit floatinb point number from the stream.
     * @return 64-bit floating point number.
     */
    virtual real64 readReal64() = 0;

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

#endif // INSTREAM_H_INCLUDE
