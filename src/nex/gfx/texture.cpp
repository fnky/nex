#include <nex/gfx/texture.h>
#include <nex/gfx/image.h>

// Standard includes.
#include <iostream>

namespace nx
{

int Texture::m_texturesAlive = 0;

uint32 Texture::getMaximumSize()
{
    GLint size;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);

    return static_cast<unsigned int>(size);
}

Texture::Texture() :
    m_id(0),
    m_pixelsFlipped(false),
    m_smooth(false)
{
    std::cout << "texture ctor" << std::endl;
}

Texture::~Texture()
{
    std::cout << "texture dtor" << std::endl;

    if (m_id) {
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}

uint32 getValidSize(unsigned int size)
{
    // If hardware doesn't support NPOT textures, we calculate the nearest power of two
    unsigned int powerOfTwo = 1;
    while (powerOfTwo < size)
        powerOfTwo *= 2;

    return powerOfTwo;

}

bool Texture::create(uint32 width, uint32 height)
{
    // Check if texture parameters are valid before creating it
    if ((width == 0) || (height == 0))
    {
        return false;
    }

    // Compute the internal texture dimensions depending on NPOT textures support
    vec2u actualSize(getValidSize(width), getValidSize(height));

    // Check the maximum texture size
    uint32 maxSize = getMaximumSize();
    if ((actualSize.x > maxSize) || (actualSize.y > maxSize))
    {
        std::cout << "Failed to create texture, its internal size is too high "
              << "(" << actualSize.x << "x" << actualSize.y << ", "
              << "maximum is " << maxSize << "x" << maxSize << ")"
              << std::endl;
        return false;
    }

    // All the validity checks passed, we can store the new texture settings
    m_size.x = width;
    m_size.y = height;
    m_actualSize = actualSize;
    m_pixelsFlipped = false;

    // Create the OpenGL texture if it doesn't exist yet
    if (!m_id)
    {
        GLuint texture;
        glGenTextures(1, &m_id);
        m_id = static_cast<unsigned int>(texture);
    }

    // Initialize the texture
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_actualSize.x, m_actualSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_repeat ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_repeat ? GL_CLAMP_TO_EDGE : GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);
}

bool Texture::loadFromFile(const std::string& file)
{
    Image image;
    // Try to load our image data.
    if (!image.loadFromFile(file)) {
        std::cout << (std::string("failed to load file: ").append(file.c_str()));
        return false;
    }

    //Check for a previous created texture
    //Delete it if it has been created.
    if (m_id > 0) {
        glDeleteTextures(1, &m_id);
    }

    // Generate an OpenGL texture object.
    glGenTextures(1, &m_id);
    if (m_id == 0) {
        std::cout << (std::string("failed to generate opengl texture!"));
        return false;
    }


    vec2u size = image.size();

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                size.x, size.y, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    // Setup our texture interpolation settings.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);

    // Specify what we do when we use a texture coordinate outside of the normal range (0.0, 0.1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_repeat ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_repeat ? GL_CLAMP_TO_EDGE : GL_REPEAT);

    return true;
}

bool Texture::loadFromImage(const Image& image, const recti& area)
{
    // Retrieve the image size
    int width = static_cast<int>(image.size().x);
    int height = static_cast<int>(image.size().y);

    // Load the entire image if the source area is either empty or contains the whole image
    if (area.width == 0 || (area.height == 0) ||
       ((area.x <= 0) && (area.y <= 0) && (area.width >= width) && (area.height >= height)))
    {
        // Load the entire image
        if (create(image.size().x, image.size().y))
        {
            update(image);

            // Force an OpenGL flush, so that the texture will appear updated
            // in all contexts immediately (solves problems in multi-threaded apps)
            glFlush();

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // Load a sub-area of the image

        // Adjust the rectangle to the size of the image
        recti rectangle = area;
        if (rectangle.x < 0) rectangle.x = 0;
        if (rectangle.y < 0) rectangle.y = 0;

        if (rectangle.x + rectangle.width > width)
            rectangle.width  = width - rectangle.x;

        if (rectangle.y + rectangle.height > height)
            rectangle.height = height - rectangle.y;

        // Create the texture and upload the pixels
        if (create(rectangle.width, rectangle.height))
        {
            // Copy the pixels to the texture, row by row
            const uint8* pixels = image.getPixelsPtr() + 4 * (rectangle.x + (width * rectangle.y));
            glBindTexture(GL_TEXTURE_2D, m_id);
            for (int i = 0; i < rectangle.height; ++i)
            {
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, i, rectangle.width, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
                pixels += 4 * width;
            }

            // Force an OpenGL flush, so that the texture will appear updated
            // in all contexts immediately (solves problems in multi-threaded apps)
            glFlush();

            return true;
        }
        else
        {
            return false;
        }
    }
}

void Texture::update(const uint8* pixels, uint32 width, uint32 height, uint32 x, uint32 y)
{
    if (m_id > 0) {
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
}

void Texture::update(const uint8* pixels)
{
    // Update the whole texture
    update(pixels, m_size.x, m_size.y, 0, 0);
}

void Texture::update(const Image& image)
{
    // Update the whole texture
    update(image.getPixelsPtr(), image.size().x, image.size().y, 0, 0);
}

void Texture::update(const Image& image, uint32 x, uint32 y)
{
    update(image.getPixelsPtr(), image.size().x, image.size().y, x, y);
}

Image Texture::copyToImage() const
{
    // Easy case: empty texture
    if (!m_id)
        return Image();

    // Create an array of pixels
    std::vector<uint8> pixels(m_size.x * m_size.y * 4);

    if ((m_size == m_actualSize) && !m_pixelsFlipped)
    {
        // Texture is not padded nor flipped, we can use a direct copy
        glBindTexture(GL_TEXTURE_2D, m_id);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
    }
    else
    {
        // Texture is either padded or flipped, we have to use a slower algorithm

        // All the pixels will first be copied to a temporary array
        std::vector<uint8> allPixels(m_actualSize.x * m_actualSize.y * 4);

        glBindTexture(GL_TEXTURE_2D, m_id);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &allPixels[0]);

        // Then we copy the useful pixels from the temporary array to the final one
        const uint8* src = &allPixels[0];

        uint8* dst = &pixels[0];

        int srcPitch = m_actualSize.x * 4;
        int dstPitch = m_size.x * 4;

        // Handle the case where source pixels are flipped vertically
        if (m_pixelsFlipped)
        {
            src += srcPitch * (m_size.y - 1);
            srcPitch = -srcPitch;
        }

        for (unsigned int i = 0; i < m_size.y; ++i)
        {
            std::memcpy(dst, src, dstPitch);
            src += srcPitch;
            dst += dstPitch;
        }
    }


    // Create the image
    Image image;
    image.create(m_size.x, m_size.y, &pixels[0]);

    return image;
}

void Texture::setSmooth(bool smooth)
{
    m_smooth = smooth;

    // Make sure we are modifying this texture.
    bind();

    // Setup our texture interpolation settings.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_smooth ? GL_LINEAR : GL_NEAREST);
}

void Texture::setRepeat(bool repeat)
{
    m_repeat = repeat;
    // Make sure we are modifying this texture.
    bind();

    // Specify what we do when we use a texture coordinate outside of the normal range (0.0, 0.1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_repeat ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_repeat ? GL_CLAMP_TO_EDGE : GL_REPEAT);
}

} //namespace nx
