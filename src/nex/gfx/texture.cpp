#include <nex/gfx/texture.h>
#include <nex/gfx/image.h>

// Standard includes.
#include <iostream>

namespace nx
{

int Texture::mTexturesAlive = 0;

Texture::Texture() :
    mId(0)
{
    std::cout << "texture ctor" << std::endl;
}

Texture::~Texture()
{
    std::cout << "texture dtor" << std::endl;

    if (mId) {
        glDeleteTextures(1, &mId);
        mId = 0;
    }
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
    if (mId > 0) {
        glDeleteTextures(1, &mId);
    }

    // Generate an OpenGL texture object.
    glGenTextures(1, &mId);
    if (mId == 0) {
        std::cout << (std::string("failed to generate opengl texture!"));
        return false;
    }


    vec2u size = image.size();

    glBindTexture(GL_TEXTURE_2D, mId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                size.x, size.y, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    // Setup our texture interpolation settings.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Specify what we do when we use a texture coordinate outside of the normal range (0.0, 0.1)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return true;
}

void Texture::update(const uint8* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
    if (mId > 0) {
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
}

} //namespace nx
