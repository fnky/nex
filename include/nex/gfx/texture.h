#ifndef TEXTURE_H_INCLUDE
#define TEXTURE_H_INCLUDE

// Nex includes.
#include <nex/system/typedefs.h>

#include <GL/glew.h>

// Standard includes.
#include <memory>

namespace nx
{

class Texture
{
public:
    Texture();
    ~Texture();

    /**
     * @brief Load a texture into the gpu texture from the specified file.
     * @param file = image file to load.
     * @return true if sucessfull.
     */
    bool loadFromFile(const std::string& file);

    /**
     * @brief Get the pixel width of the image that was loaded into opengl.
     * @return pixel width of the image.
     */
    uint32 getPixelWidth() const { return mPixelWidth; }

    /**
     * @brief Get the pixel height of the image that was loaded into opengl.
     * @return pixel height of the image.
     */
    uint32 getPixelHeight() const { return mPixelHeight; }

    /**
     * @brief Bind the texture to the opengl context.
     */
    inline void bind() const { glBindTexture(GL_TEXTURE_2D, mId); }

    /**
     * @brief update
     * @param pixels
     * @param width
     * @param height
     * @param x
     * @param y
     */
    void update(const uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

private:
    uint32 mId;
    uint32 mPixelWidth;
    uint32 mPixelHeight;

    static int mTexturesAlive;
};

typedef std::shared_ptr<Texture> TexturePtr;

} //namespace nx

#endif // TEXTURE_H_INCLUDE
