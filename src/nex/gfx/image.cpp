#include <nex/gfx/image.h>
#include <nex/gfx/imageloader.h>

// Standard includes.
#include <cstring>

namespace nx
{

Image::Image() :
    m_size(vec2u(0, 0))
{ }

Image::~Image()
{ }

void Image::create(uint32 width, uint32 height, const Color &color)
{
    if (width && height)
    {
        // Assign the new size
        m_size.x = width;
        m_size.y = height;

        // Resize the pixel buffer
        m_pixels.resize(width * height * 4);

        // Fill it with the specified color
        uint8* ptr = &m_pixels[0];
        uint8* end = ptr + m_pixels.size();
        while (ptr < end)
        {
            *ptr++ = color.r;
            *ptr++ = color.g;
            *ptr++ = color.b;
            *ptr++ = color.a;
        }
    }
    else
    {
        // Create an empty image
        m_size.x = 0;
        m_size.y = 0;
        m_pixels.clear();
    }
}

void Image::create(uint32 width, uint32 height, const uint8* pixels)
{
    if (pixels && width && height)
    {
        // Assign the new size
        m_size.x = width;
        m_size.y = height;

        // Copy the pixels
        std::size_t size = width * height * 4;
        m_pixels.resize(size);
        std::memcpy(&m_pixels[0], pixels, size); // faster than vector::assign
    }
    else
    {
        // Create an empty image
        m_size.x = 0;
        m_size.y = 0;
        m_pixels.clear();
    }
}

bool Image::loadFromFile(const std::string& filename)
{
    return nx::priv::ImageLoader::getInstance().loadImageFromFile(filename, m_pixels, m_size);
}

bool Image::loadFromMemory(const void* data, std::size_t size)
{
    return nx::priv::ImageLoader::getInstance().loadImageFromMemory(data, size, m_pixels, m_size);
}

bool Image::loadFromStream(InStream& stream)
{
    return nx::priv::ImageLoader::getInstance().loadImageFromStream(stream, m_pixels, m_size);
}

bool Image::saveToFile(const std::string& filename) const
{
    return nx::priv::ImageLoader::getInstance().saveImageToFile(filename, m_pixels, m_size);
}

void Image::createMaskFromColor(const Color& color, uint8 alpha)
{
    // Make sure that the image is not empty
    if (!m_pixels.empty())
    {
        // Replace the alpha of the pixels that match the transparent color
        uint8* ptr = &m_pixels[0];
        uint8* end = ptr + m_pixels.size();
        while (ptr < end)
        {
            if ((ptr[0] == color.r) && (ptr[1] == color.g) && (ptr[2] == color.b) && (ptr[3] == color.a))
                ptr[3] = alpha;
            ptr += 4;
        }
    }
}

void Image::copy(const Image& source, uint32 destX, uint32 destY, const recti& sourceRect, bool applyAlpha)
{
    // Make sure that both images are valid
    if ((source.m_size.x == 0) || (source.m_size.y == 0) || (m_size.x == 0) || (m_size.y == 0))
        return;

    // Adjust the source rectangle
    recti srcRect = sourceRect;
    if (srcRect.width == 0 || (srcRect.height == 0))
    {
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.width = source.m_size.x;
        srcRect.height = source.m_size.y;
    }
    else
    {
        if (srcRect.x < 0)
            srcRect.x = 0;

        if (srcRect.y < 0)
            srcRect.y  = 0;

        if (srcRect.width > static_cast<int>(source.m_size.x))
            srcRect.width  = source.m_size.x;

        if (srcRect.height > static_cast<int>(source.m_size.y))
            srcRect.height = source.m_size.y;
    }

    // Then find the valid bounds of the destination rectangle
    int width  = srcRect.width;
    int height = srcRect.height;

    if (destX + width  > m_size.x)
        width  = m_size.x - destX;

    if (destY + height > m_size.y)
        height = m_size.y - destY;

    // Make sure the destination area is valid
    if ((width <= 0) || (height <= 0))
        return;

    // Precompute as much as possible
    int pitch = width * 4;
    int rows = height;
    int srcStride = source.m_size.x * 4;
    int dstStride = m_size.x * 4;
    const uint8* srcPixels = &source.m_pixels[0] + (srcRect.x + srcRect.y * source.m_size.x) * 4;
    uint8* dstPixels = &m_pixels[0] + (destX + destY * m_size.x) * 4;

    // Copy the pixels
    if (applyAlpha)
    {
        // Interpolation using alpha values, pixel by pixel (slower)
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                // Get a direct pointer to the components of the current pixel
                const uint8* src = srcPixels + j * 4;
                uint8* dst = dstPixels + j * 4;

                // Interpolate RGBA components using the alpha value of the source pixel
                uint8 alpha = src[3];
                dst[0] = (src[0] * alpha + dst[0] * (255 - alpha)) / 255;
                dst[1] = (src[1] * alpha + dst[1] * (255 - alpha)) / 255;
                dst[2] = (src[2] * alpha + dst[2] * (255 - alpha)) / 255;
                dst[3] = alpha + dst[3] * (255 - alpha) / 255;
            }

            srcPixels += srcStride;
            dstPixels += dstStride;
        }
    }
    else
    {
        // Optimized copy ignoring alpha values, row by row (faster)
        for (int i = 0; i < rows; ++i)
        {
            std::memcpy(dstPixels, srcPixels, pitch);
            srcPixels += srcStride;
            dstPixels += dstStride;
        }
    }
}

void Image::setPixel(unsigned int x, unsigned int y, const Color& color)
{
    uint8* pixel = &m_pixels[(x + y * m_size.x) * 4];
    *pixel++ = color.r;
    *pixel++ = color.g;
    *pixel++ = color.b;
    *pixel++ = color.a;
}

Color Image::getPixel(unsigned int x, unsigned int y) const
{
    const uint8* pixel = &m_pixels[(x + y * m_size.x) * 4];
    return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
}

const uint8* Image::getPixelsPtr() const
{
    if (!m_pixels.empty())
    {
        return &m_pixels[0];
    }
    else
    {
        return 0;
    }
}

void Image::flipHorizontally()
{
    if (!m_pixels.empty())
    {
        std::size_t rowSize = m_size.x * 4;

        for (std::size_t y = 0; y < m_size.y; ++y)
        {
            std::vector<uint8>::iterator left = m_pixels.begin() + y * rowSize;
            std::vector<uint8>::iterator right = m_pixels.begin() + (y + 1) * rowSize - 4;

            for (std::size_t x = 0; x < m_size.x / 2; ++x)
            {
                std::swap_ranges(left, left + 4, right);

                left += 4;
                right -= 4;
            }
        }
    }
}

void Image::flipVertically()
{
    if (!m_pixels.empty())
    {
        std::size_t rowSize = m_size.x * 4;

        std::vector<uint8>::iterator top = m_pixels.begin();
        std::vector<uint8>::iterator bottom = m_pixels.end() - rowSize;

        for (std::size_t y = 0; y < m_size.y / 2; ++y)
        {
            std::swap_ranges(top, top + rowSize, bottom);

            top += rowSize;
            bottom -= rowSize;
        }
    }
}

} // namespace nx
