#include <nex/gfx/font.h>
#include <nex/system/instream.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace
{
    // FreeType callbacks that operate on a sf::InputStream
    unsigned long read(FT_Stream rec, unsigned long offset, unsigned char* buffer, unsigned long count)
    {
        nx::InStream* stream = static_cast<nx::InStream*>(rec->descriptor.pointer);
        if (static_cast<unsigned long>(stream->seek(offset)) == offset)
        {
            if (count > 0)
                return static_cast<unsigned long>(stream->read(reinterpret_cast<char*>(buffer), count));
            else
                return 0;
        }
        else
            return count > 0 ? 0 : 1; // error code is 0 if we're reading, or nonzero if we're seeking
    }

    void close(FT_Stream)
    {

    }
}

namespace nx
{

Font::Font() :
    mLibrary(0),
    mFace(0),
    mStreamRec(0),
    mRefCount(0),
    mInfo()
{ }

Font::Font(const Font& copy) :
    mLibrary(copy.mLibrary),
    mFace(copy.mFace),
    mStreamRec(copy.mStreamRec),
    mRefCount(copy.mRefCount),
    mInfo(copy.mInfo),
    mPages(copy.mPages),
    mPixelBuffer(copy.mPixelBuffer)
{
    // Note: as FreeType doesn't provide functions for copying/cloning,
    // we must share all the FreeType pointers

    if (mRefCount)
        (*mRefCount)++;
}

Font::~Font()
{
    cleanup();
}

bool Font::loadFromFile(const std::string& filename)
{
    // Cleanup the previous resources
    cleanup();
    mRefCount = new int(1);

    // Initialize FreeType
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        std::cout << "Failed to load font \"" << filename << "\" (failed to initialize FreeType)" << std::endl;
        return false;
    }
    mLibrary = library;

    // Load the new font face from the specified file
    FT_Face face;
    if (FT_New_Face(static_cast<FT_Library>(mLibrary), filename.c_str(), 0, &face) != 0)
    {
        std::cout << "Failed to load font \"" << filename << "\" (failed to create the font face)" << std::endl;
        return false;
    }

    // Select the unicode character map
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        std::cout << "Failed to load font \"" << filename << "\" (failed to set the Unicode character set)" << std::endl;
        FT_Done_Face(face);
        return false;
    }

    // Store the loaded font in our ugly void* :)
    mFace = face;

    // Store the font information
    mInfo.family = face->family_name ? face->family_name : std::string();

    return true;
}

bool Font::loadFromMemory(const void* data, std::size_t sizeInBytes)
{
    // Cleanup the previous resources
    cleanup();
    mRefCount = new int(1);

    // Initialize FreeType
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        std::cout << "Failed to load font from memory (failed to initialize FreeType)" << std::endl;
        return false;
    }
    mLibrary = library;

    // Load the new font face from the specified file
    FT_Face face;
    if (FT_New_Memory_Face(static_cast<FT_Library>(mLibrary), reinterpret_cast<const FT_Byte*>(data), static_cast<FT_Long>(sizeInBytes), 0, &face) != 0)
    {
        std::cout << "Failed to load font from memory (failed to create the font face)" << std::endl;
        return false;
    }

    // Select the Unicode character map
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        std::cout << "Failed to load font from memory (failed to set the Unicode character set)" << std::endl;
        FT_Done_Face(face);
        return false;
    }

    // Store the loaded font in our ugly void* :)
    mFace = face;

    // Store the font information
    mInfo.family = face->family_name ? face->family_name : std::string();

    return true;
}

bool Font::loadFromStream(InStream& stream)
{
    // Cleanup the previous resources
    cleanup();
    mRefCount = new int(1);

    // Initialize FreeType
    // Note: we initialize FreeType for every font instance in order to avoid having a single
    // global manager that would create a lot of issues regarding creation and destruction order.
    FT_Library library;
    if (FT_Init_FreeType(&library) != 0)
    {
        std::cout << "Failed to load font from stream (failed to initialize FreeType)" << std::endl;
        return false;
    }
    mLibrary = library;

    // Make sure that the stream's reading position is at the beginning
    stream.seek(0);

    // Prepare a wrapper for our stream, that we'll pass to FreeType callbacks
    FT_StreamRec* rec = new FT_StreamRec;
    std::memset(rec, 0, sizeof(*rec));
    rec->base = 0;
    rec->size = static_cast<unsigned long>(stream.size());
    rec->pos = 0;
    rec->descriptor.pointer = &stream;
    rec->read = &read;
    rec->close = &close;

    // Setup the FreeType callbacks that will read our stream
    FT_Open_Args args;
    args.flags  = FT_OPEN_STREAM;
    args.stream = rec;
    args.driver = 0;

    // Load the new font face from the specified stream
    FT_Face face;
    if (FT_Open_Face(static_cast<FT_Library>(mLibrary), &args, 0, &face) != 0)
    {
        std::cout << "Failed to load font from stream (failed to create the font face)" << std::endl;
        delete rec;
        return false;
    }

    // Select the Unicode character map
    if (FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
    {
        std::cout << "Failed to load font from stream (failed to set the Unicode character set)" << std::endl;
        FT_Done_Face(face);
        delete rec;
        return false;
    }

    // Store the loaded font in our ugly void* :)
    mFace = face;
    mStreamRec = rec;

    // Store the font information
    mInfo.family = face->family_name ? face->family_name : std::string();

    return true;
}

const Font::Info& Font::getInfo() const
{
    return mInfo;
}

const Glyph& Font::getGlyph(uint32 codePoint, uint32 characterSize, bool bold) const
{
    // Get the page corresponding to the character size
    GlyphTable& glyphs = mPages[characterSize].glyphs;

    // Build the key by combining the code point and the bold flag
    uint32 key = ((bold ? 1 : 0) << 31) | codePoint;

    // Search the glyph into the cache
    GlyphTable::const_iterator it = glyphs.find(key);
    if (it != glyphs.end())
    {
        // Found: just return it
        return it->second;
    }
    else
    {
        // Not found: we have to load it
        Glyph glyph = loadGlyph(codePoint, characterSize, bold);
        return glyphs.insert(std::make_pair(key, glyph)).first->second;
    }
}

float Font::getKerning(uint32 first, uint32 second, uint32 characterSize) const
{
    // Special case where first or second is 0 (null character)
    if (first == 0 || second == 0)
        return 0.f;

    FT_Face face = static_cast<FT_Face>(mFace);

    if (face && FT_HAS_KERNING(face) && setCurrentSize(characterSize))
    {
        // Convert the characters to indices
        FT_UInt index1 = FT_Get_Char_Index(face, first);
        FT_UInt index2 = FT_Get_Char_Index(face, second);

        // Get the kerning vector
        FT_Vector kerning;
        FT_Get_Kerning(face, index1, index2, FT_KERNING_DEFAULT, &kerning);

        // X advance is already in pixels for bitmap fonts
        if (!FT_IS_SCALABLE(face))
            return static_cast<float>(kerning.x);

        // Return the X advance
        return static_cast<float>(kerning.x) / static_cast<float>(1 << 6);
    }
    else
    {
        // Invalid font, or no kerning
        return 0.f;
    }
}

float Font::getLineSpacing(uint32 characterSize) const
{
    FT_Face face = static_cast<FT_Face>(mFace);

    if (face && setCurrentSize(characterSize))
    {
        return static_cast<float>(face->size->metrics.height) / static_cast<float>(1 << 6);
    }
    else
    {
        return 0.f;
    }
}

float Font::getUnderlinePosition(uint32 characterSize) const
{
    FT_Face face = static_cast<FT_Face>(mFace);

    if (face && setCurrentSize(characterSize))
    {
        // Return a fixed position if font is a bitmap font
        if (!FT_IS_SCALABLE(face))
            return characterSize / 10.f;

        return -static_cast<float>(FT_MulFix(face->underline_position, face->size->metrics.y_scale)) / static_cast<float>(1 << 6);
    }
    else
    {
        return 0.f;
    }
}

float Font::getUnderlineThickness(uint32 characterSize) const
{
    FT_Face face = static_cast<FT_Face>(mFace);

    if (face && setCurrentSize(characterSize))
    {
        // Return a fixed thickness if font is a bitmap font
        if (!FT_IS_SCALABLE(face))
            return characterSize / 14.f;

        return static_cast<float>(FT_MulFix(face->underline_thickness, face->size->metrics.y_scale)) / static_cast<float>(1 << 6);
    }
    else
    {
        return 0.f;
    }
}

const Texture& Font::getTexture(uint32 characterSize) const
{
    return mPages[characterSize].texture;
}

Font& Font::operator =(const Font& right)
{
    Font temp(right);

    std::swap(mLibrary, temp.mLibrary);
    std::swap(mFace, temp.mFace);
    std::swap(mStreamRec, temp.mStreamRec);
    std::swap(mRefCount, temp.mRefCount);
    std::swap(mInfo, temp.mInfo);
    std::swap(mPages, temp.mPages);
    std::swap(mPixelBuffer, temp.mPixelBuffer);

    return *this;
}

void Font::cleanup()
{
    // Check if we must destroy the FreeType pointers
    if (mRefCount)
    {
        // Decrease the reference counter
        (*mRefCount)--;

        // Free the resources only if we are the last owner
        if (*mRefCount == 0)
        {
            // Delete the reference counter
            delete mRefCount;

            // Destroy the font face
            if (mFace)
                FT_Done_Face(static_cast<FT_Face>(mFace));

            // Destroy the stream rec instance, if any (must be done after FT_Done_Face!)
            if (mStreamRec)
                delete static_cast<FT_StreamRec*>(mStreamRec);

            // Close the library
            if (mLibrary)
                FT_Done_FreeType(static_cast<FT_Library>(mLibrary));
        }
    }

    // Reset members
    mLibrary = 0;
    mFace = 0;
    mStreamRec = 0;
    mRefCount = 0;
    mPages.clear();
    mPixelBuffer.clear();
}

Glyph Font::loadGlyph(uint32 codePoint, uint32 characterSize, bool bold) const
{
    // The glyph to return
    Glyph glyph;

    // First, transform our ugly void* to a FT_Face
    FT_Face face = static_cast<FT_Face>(mFace);
    if (!face)
        return glyph;

    // Set the character size
    if (!setCurrentSize(characterSize))
        return glyph;

    // Load the glyph corresponding to the code point
    if (FT_Load_Char(face, codePoint, FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT) != 0)
        return glyph;

    // Retrieve the glyph
    FT_Glyph glyphDesc;
    if (FT_Get_Glyph(face->glyph, &glyphDesc) != 0)
        return glyph;

    // Apply bold if necessary -- first technique using outline (highest quality)
    FT_Pos weight = 1 << 6;
    bool outline = (glyphDesc->format == FT_GLYPH_FORMAT_OUTLINE);
    if (bold && outline)
    {
        FT_OutlineGlyph outlineGlyph = (FT_OutlineGlyph)glyphDesc;
        FT_Outline_Embolden(&outlineGlyph->outline, weight);
    }

    // Convert the glyph to a bitmap (i.e. rasterize it)
    FT_Glyph_To_Bitmap(&glyphDesc, FT_RENDER_MODE_NORMAL, 0, 1);
    FT_Bitmap& bitmap = reinterpret_cast<FT_BitmapGlyph>(glyphDesc)->bitmap;

    // Apply bold if necessary -- fallback technique using bitmap (lower quality)
    if (bold && !outline)
    {
        FT_Bitmap_Embolden(static_cast<FT_Library>(mLibrary), &bitmap, weight, weight);
    }

    // Compute the glyph's advance offset
    glyph.advance = static_cast<float>(face->glyph->metrics.horiAdvance) / static_cast<float>(1 << 6);
    if (bold)
        glyph.advance += static_cast<float>(weight) / static_cast<float>(1 << 6);

    int width  = bitmap.width;
    int height = bitmap.rows;

    if ((width > 0) && (height > 0))
    {
        // Leave a small padding around characters, so that filtering doesn't
        // pollute them with pixels from neighbors
        const unsigned int padding = 1;

        // Get the glyphs page corresponding to the character size
        Page& page = mPages[characterSize];

        // Find a good position for the new glyph into the texture
        glyph.textureRect = findGlyphRect(page, width + 2 * padding, height + 2 * padding);

        // Make sure the texture data is positioned in the center
        // of the allocated texture rectangle
        glyph.textureRect.x += padding;
        glyph.textureRect.y += padding;
        glyph.textureRect.width -= 2 * padding;
        glyph.textureRect.height -= 2 * padding;

        // Compute the glyph's bounding box
        glyph.bounds.x = static_cast<float>(face->glyph->metrics.horiBearingX) / static_cast<float>(1 << 6);
        glyph.bounds.y = -static_cast<float>(face->glyph->metrics.horiBearingY) / static_cast<float>(1 << 6);
        glyph.bounds.width  = static_cast<float>(face->glyph->metrics.width) / static_cast<float>(1 << 6);
        glyph.bounds.height = static_cast<float>(face->glyph->metrics.height) / static_cast<float>(1 << 6);

        // Extract the glyph's pixels from the bitmap
        mPixelBuffer.resize(width * height * 4, 255);
        const uint8* pixels = bitmap.buffer;
        if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
        {
            // Pixels are 1 bit monochrome values
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    // The color channels remain white, just fill the alpha channel
                    std::size_t index = (x + y * width) * 4 + 3;
                    mPixelBuffer[index] = ((pixels[x / 8]) & (1 << (7 - (x % 8)))) ? 255 : 0;
                }
                pixels += bitmap.pitch;
            }
        }
        else
        {
            // Pixels are 8 bits gray levels
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    // The color channels remain white, just fill the alpha channel
                    std::size_t index = (x + y * width) * 4 + 3;
                    mPixelBuffer[index] = pixels[x];
                }
                pixels += bitmap.pitch;
            }
        }

        // Write the pixels to the texture
        unsigned int x = glyph.textureRect.x;
        unsigned int y = glyph.textureRect.y;
        unsigned int w = glyph.textureRect.width;
        unsigned int h = glyph.textureRect.height;
        page.texture.update(&mPixelBuffer[0], w, h, x, y);
    }

    // Delete the FT glyph
    FT_Done_Glyph(glyphDesc);

    // Force an OpenGL flush, so that the font's texture will appear updated
    // in all contexts immediately (solves problems in multi-threaded apps)
    glFlush();

    // Done :)
    return glyph;
}

recti Font::findGlyphRect(Page& page, uint32 width, uint32 height) const
{
    // Find the line that fits well the glyph
    Row* row = NULL;
    float bestRatio = 0;
    for (std::vector<Row>::iterator it = page.rows.begin(); it != page.rows.end() && !row; ++it)
    {
        float ratio = static_cast<float>(height) / it->height;

        // Ignore rows that are either too small or too high
        if ((ratio < 0.7f) || (ratio > 1.f))
            continue;

        // Check if there's enough horizontal space left in the row
        if (width > page.texture.size().x - it->width)
            continue;

        // Make sure that this new row is the best found so far
        if (ratio < bestRatio)
            continue;

        // The current row passed all the tests: we can select it
        row = &*it;
        bestRatio = ratio;
    }

    // If we didn't find a matching row, create a new one (10% taller than the glyph)
    if (!row)
    {
        int rowHeight = height + height / 10;
        while ((page.nextRow + rowHeight >= page.texture.size().y) || (width >= page.texture.size().x))
        {
            // Not enough space: resize the texture if possible
            unsigned int textureWidth  = page.texture.size().x;
            unsigned int textureHeight = page.texture.size().y;
            if ((textureWidth * 2 <= Texture::getMaximumSize()) && (textureHeight * 2 <= Texture::getMaximumSize()))
            {
                // Make the texture 2 times bigger
                nx::Image newImage;
                newImage.create(textureWidth * 2, textureHeight * 2, Color(255, 255, 255, 0));
                newImage.copy(page.texture.copyToImage(), 0, 0);
                page.texture.loadFromImage(newImage);
            }
            else
            {
                // Oops, we've reached the maximum texture size...
                std::cout << "Failed to add a new character to the font: the maximum texture size has been reached" << std::endl;
                return recti(0, 0, 2, 2);
            }
        }

        // We can now create the new row
        page.rows.push_back(Row(page.nextRow, rowHeight));
        page.nextRow += rowHeight;
        row = &page.rows.back();
    }

    // Find the glyph's rectangle on the selected row
    recti rect(row->width, row->top, width, height);

    // Update the row informations
    row->width += width;

    return rect;
}
bool Font::setCurrentSize(unsigned int characterSize) const
{
    // FT_Set_Pixel_Sizes is an expensive function, so we must call it
    // only when necessary to avoid killing performances

    FT_Face face = static_cast<FT_Face>(mFace);
    FT_UShort currentSize = face->size->metrics.x_ppem;

    if (currentSize != characterSize)
    {
        FT_Error result = FT_Set_Pixel_Sizes(face, 0, characterSize);

        if (result == FT_Err_Invalid_Pixel_Size)
        {
            // In the case of bitmap fonts, resizing can
            // fail if the requested size is not available
            if (!FT_IS_SCALABLE(face))
            {
                std::cout << "Failed to set bitmap font size to " << characterSize << std::endl;
                std::cout << "Available sizes are: ";
                for (int i = 0; i < face->num_fixed_sizes; ++i)
                    std::cout << face->available_sizes[i].height << " ";
                std::cout << std::endl;
            }
        }

        return result == FT_Err_Ok;
    }
    else
    {
        return true;
    }
}

Font::Page::Page() :
nextRow(3)
{
    // Make sure that the texture is initialized by default
    nx::Image image;
    image.create(128, 128, Color(255, 255, 255, 0));

    // Reserve a 2x2 white square for texturing underlines
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y)
            image.setPixel(x, y, Color(255, 255, 255, 255));

    // Create the texture
    texture.loadFromImage(image);
    texture.setSmooth(true);
}

} // namespace nx
