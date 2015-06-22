#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

// Nex includes.
#include <nex/system/typedefs.h>
#include <nex/system/instream.h>

#include <nex/math/vec2.h>
#include <nex/math/rect.h>

#include <nex/gfx/color.h>

// Standard includes.
#include <string>
#include <vector>

namespace nx
{

class Image
{
public:

    /**
     * @brief Default constructor.
     */
    Image();

    /**
      * @brief Default destructor.
      */
    ~Image();

    /**
     * @brief Create the image and fill it with a specified color.
     * @param width = Width of the image.
     * @param height = Height of the image.
     * @param color = The color to fill with.
     */
    void create(uint32 width, uint32 height, const Color& color = Color(0, 0, 0));

    /**
     * @brief Create the image from an array of pixels.
     * @param width = Width of the image.
     * @param height = Height of the image.
     * @param pixels = Array of pixels to copy to the image.
     */
    void create(uint32 width, uint32 height, const uint8* pixels);

    /**
     * @brief Create a transparency mask from a specified color-key.
     * @param color = Color to make transparent.
     * @param alpha = Alpha value to assign to transparent pixels.
     */
    void createMaskFromColor(const Color& color, uint8 alpha = 0);

    /**
     * @brief Copy pixels from another image onto this one.
     * @param source = The source image to copy from.
     * @param destX = The X coordinate of the destination position.
     * @param destY = The Y coordinate of the destination position.
     * @param sourceRect = Sub-rectangle of the source image to copy.
     * @param applyAlpha = Should the copy take into account the source transparency.
     */
    void copy(const Image& source, uint32 destX, uint32 destY,
              const recti& sourceRect = recti(0, 0, 0, 0), bool applyAlpha = false);

    /**
     * @brief Change the color of a pixel.
     * @param x = The X coordinate of pixel to change.
     * @param y = The Y coordinate of pixel to change.
     * @param color = New color of the pixel.
     */
    void setPixel(uint32 x, uint32 y, const Color& color);

    /**
     * @brief Get the color of a pixel.
     * @param x = The X coordinate of pixel to get.
     * @param y = The Y coordinate of pixel to get.
     * @return Color of the pixel at coordinates (x, y).
     */
    Color getPixel(uint32 x, uint32 y) const;

    /**
     * @brief Flip the image horizontally (left <-> right).
     */
    void flipHorizontally();

    /**
     * @brief Flip the image vertically (top <-> bottom).
     */
    void flipVertically();

    /**
     * @brief Load the image from a file on disk.
     * @param filename = Path of the image file to load.
     * @return true if loading was successful.
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Load the image from a file in memory.
     * @param data = Pointer to the file data in memory.
     * @param size = Size of the data to load, in bytes.
     * @return true if loading was successful.
     */
    bool loadFromMemory(const void* data, std::size_t size);

    /**
     * @brief Load the image from a custom stream.
     * @param stream = The source stream to read from.
     * @return true if loading was successful.
     */
    bool loadFromStream(InStream& stream);

    /**
     * @brief Save the image to a file on disk.
     * @param filename = Path of the file to save.
     * @return true if saving was successful.
     */
    bool saveToFile(const std::string& filename) const;

    /**
     * @brief Return the size (width and height) of the image.
     * @return Size of the image, in pixels.
     */
    vec2u size() const;

    /**
     * @brief Get a read-only pointer to the array of pixels.
     * @return Read-only pointer to the array of pixels.
     */
    const uint8* getPixelsPtr() const;

private:
    vec2u mSize;
    std::vector<uint8> mPixels;
};

} // namespace nx

#endif // IMAGE_H_INCLUDE
