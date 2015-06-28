#ifndef TEXTURE_H_INCLUDE
#define TEXTURE_H_INCLUDE

// Nex includes.
#include <nex/system/typedefs.h>
#include <nex/math/vec2.h>
#include <nex/gfx/image.h>

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
     * @brief Create the texture.
     * @param width = Width of the texture.
     * @param height = Height of the texture.
     * @return true if creation was successful.
     */
    bool create(uint32 width, uint32 height);

    /**
     * @brief Load a texture into the gpu texture from the specified file.
     * @param file = image file to load.
     * @return true if sucessfull.
     */
    bool loadFromFile(const std::string& file);

    /**
     * @brief Load the texture from an image.
     * @param image = Image to load into the texture.
     * @param area = Area of the image to load.
     * @return true if loading was successful.
     */
    bool loadFromImage(const Image& image, const recti& area = recti());

    /**
     * @brief Bind the texture to the opengl context.
     */
    inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }

    /**
     * @brief Unbind the texture from the opengl context.
     */
    inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    /**
     * @brief Copy this texture to an image.
     * @return The current image.
     */
    Image copyToImage() const;

    /**
     * @brief Update a part of the texture from an array of pixels.
     * @param pixels = Array of pixels to copy to the texture.
     * @param width = Width of the pixel region contained in pixels.
     * @param height = Height of the pixel region contained in pixels.
     * @param x = X offset in the texture where to copy the source pixels.
     * @param y = Y offset in the texture where to copy the source pixels.
     */
    void update(const uint8* pixels, uint32 width, uint32 height, uint32 x, uint32 y);

    /**
     * @brief Update the whole texture from an array of pixels.
     * @param pixels = Array of pixels to copy to the texture.
     */
    void update(const uint8* pixels);

    /**
     * @brief Update the texture from an image.
     * @param image = Image to copy to the texture.
     */
    void update(const Image& image);

    /**
     * @brief Update a part of the texture from an image.
     * @param image = Image to copy to the texture.
     * @param x = X offset in the texture where to copy the source image.
     * @param y = Y offset in the texture where to copy the source image.
     */
    void update(const Image& image, uint32 x, uint32 y);

    /**
     * @brief Query the maximum opengl texture size.
     * @return The maximum texture size.
     */
    static uint32 getMaximumSize();

    /**
     * @brief Get the size of the image.
     * @return The current image size.
     */
    inline vec2u size() const { return m_size; }

    /**
     * @brief Enable texture smoothing.
     * @param smooth = True oder false.
     */
    void setSmooth(bool smooth);

    /**
     * @brief Get the state of the this textures smoothing.
     * @return the state of the smooth.
     */
    inline bool getSmooth() const { return m_smooth; }

    /**
     * @brief Set the texture to repeate uv coordinates outside of the 0.0 <-> 0.1 range.
     * @param repeat = Repeat or not.
     */
    void setRepeat(bool repeat);

    /**
     * @brief Get the state of the textures repeat.
     * @return the repeat state.
     */
    inline bool getRepeat() const { return m_repeat; }

private:
    mutable bool m_pixelsFlipped;

    bool m_smooth;
    bool m_repeat;

    uint32 m_id;
    vec2u m_size;
    vec2u m_actualSize;

    static int m_texturesAlive;
};

typedef std::shared_ptr<Texture> TexturePtr;

} //namespace nx

#endif // TEXTURE_H_INCLUDE
