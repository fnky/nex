#ifndef IMAGELOADER_H_INCLUDE
#define IMAGELOADER_H_INCLUDE

// Nex system includes.
#include <nex/system/noncopyable.h>

// Nex math includes.
#include <nex/math/vec2.h>

// Standard includes.
#include <string>
#include <vector>

namespace nx
{

// Forward reference for the in stream.
class InStream;

namespace priv
{

class ImageLoader
{
public:

    /**
      * @brief Get the unique instance of the class.
      * @return Reference to the ImageLoader instance.
      */
     static ImageLoader& getInstance();

     /**
      * @brief Load an image from a file on disk.
      * @param filename = Path of image file to load.
      * @param pixels = Array of pixels to fill with loaded image.
      * @param size = Size of loaded image, in pixels.
      * @return true if loading was successful.
      */
     bool loadImageFromFile(const std::string& filename, std::vector<uint8>& pixels, vec2u& size);

     /**
      * @brief Load an image from a file in memory.
      * @param data = Pointer to the file data in memory.
      * @param dataSize = Size of the data to load, in bytes.
      * @param pixels = Array of pixels to fill with loaded image.
      * @param size = Size of loaded image, in pixels.
      * @return true if loading was successful.
      */
     bool loadImageFromMemory(const void* data, std::size_t dataSize, std::vector<uint8>& pixels, vec2u& size);

     /**
      * @brief Load an image from a custom stream.
      * @param stream = Source stream to read from.
      * @param pixels = Array of pixels to fill with loaded image.
      * @param size = Size of loaded image, in pixels.
      * @return true if loading was successful.
      */
     bool loadImageFromStream(InStream& stream, std::vector<uint8>& pixels, vec2u& size);

     /**
      * @brief Save an array of pixels as an image file.
      * @param filename = Path of image file to save.
      * @param pixels = Array of pixels to save to image.
      * @param size = Size of image to save, in pixels.
      * @return true if saving was successful.
      */
     bool saveImageToFile(const std::string& filename, const std::vector<uint8>& pixels, const vec2u& size);

private:

     /**
      * @brief Default constructor.
      */
     ImageLoader();

     /**
      * @brief Default destuctor.
      */
     ~ImageLoader();
};

} // namespace priv

} // namespace nx

#endif // IMAGELOADER_H_INCLUDE
