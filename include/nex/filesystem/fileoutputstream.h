#ifndef FILEOUTPUTSTREAM_H_INCLUDE
#define FILEOUTPUTSTREAM_H_INCLUDE

// Nex includes.
#include <nex/system/outstream.h>

// Standard includes.
#include <string>
#include <cstdio>

namespace nx
{

class FileOutputStream
{
public:

    /**
     * @brief Default constructor.
     */
    FileOutputStream();

    /**
     * @brief Default virtual destructor.
     */
    virtual ~FileOutputStream();

    /**
     * @brief Open a file stream to the specified path.
     * @param filepath = The path to the file.
     * @return true if sucessful.
     */
    bool open(const std::string& filepath);

    /**
     * @brief Close the file stream.
     */
    void close();

    /**
     * @brief Write the specified number of bytes into the specified array.
     * @param data = The place to read the data from.
     * @param size = The number of bytes to write.
     * @return The actual number of bytes written or -1 on error.
     */
    virtual int64 write(void* data, int64 size);

    /**
     * @brief Change the current writing position.
     * @param position = The position to seek to, from the beginning.
     * @return The position actually sought to, or -1 on error.
     */
    virtual int64 seek(int64 position);

    /**
     * @brief Get the current reading writing in the stream.
     * @return The current position, or -1 on error.
     */
    virtual int64 tell();

    /**
     * @brief Return the size of the stream.
     * @return The total number of bytes available in the stream, or -1 on error.
     */
    virtual int64 size();

private:

    /**
     * @brief The file pointer to which we will write data.
     */
    std::FILE* mFile;
};

} // namespace nx

#endif // FILEOUTPUTSTREAM_H_INCLUDE
