#ifndef FILEINPUTSTREAM_H_INCLUDE
#define FILEINPUTSTREAM_H_INCLUDE

// Nex includes.
#include <nex/system/instream.h>

// Standard includes.
#include <cstdio>
#include <string>

namespace nx
{

class FileInputStream : public InStream
{
public:

    /**
     * @brief Default constructor.
     */
    FileInputStream();

    /**
     * @brief Default vitrual destructor.
     */
    virtual ~FileInputStream();

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
     * @brief Read the specified number of bytes into the specified array.
     * @param data = The place to read the data into.
     * @param size = The number of bytes to read.
     * @return The actual number of bytes read or -1 on error.
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
     * @brief Return the size of the stream.
     * @return The total number of bytes available in the stream, or -1 on error.
     */
    virtual int64 size();

private:

    /**
     * @brief The actual file pointer.
     */
    std::FILE* mFile;
};

} // namespace nx

#endif // FILEINPUTSTREAM_H_INCLUDE
