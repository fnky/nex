#ifndef FONT_H_INCLUDE
#define FONT_H_INCLUDE

// Nex includes
#include <nex/gfx/glyph.h>
#include <nex/gfx/texture.h>
#include <nex/gfx/image.h>
#include <nex/system/string.h>
#include <nex/math/vec2.h>
#include <nex/math/rect.h>

// Standard includes.
#include <map>
#include <string>
#include <vector>

namespace nx
{

class InStream;

class Font
{
public:

    /**
     * @brief Hold some basic font information.
     */
    struct Info
    {
        std::string family;
    };

    /**
     * @brief Default constructor defines an empty font.
     */
    Font();

    /**
     * @brief Copy constructor.
     * @param copy = Instance to copy.
     */
    Font(const Font& copy);

    /**
     * @brief Destructor.
     */
    ~Font();

    /**
     * @brief Load the font from a file.
     * @param filename = Path of the font file to load.
     * @return true if loading succeeded, false if it failed.
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Load the font from a file in memory.
     * @param data = Pointer to the file data in memory.
     * @param sizeInBytes = Size of the data to load, in bytes.
     * @return true if loading succeeded, false if it failed.
     */
    bool loadFromMemory(const void* data, std::size_t sizeInBytes);

    /**
     * @brief Load the font from a custom stream.
     * @param stream = Source stream to read from.
     * @return true if loading succeeded, false if it failed.
     */
    bool loadFromStream(InStream& stream);

    /**
     * @brief Get the font information.
     * @return A structure that holds the font information.
     */
    const Info& getInfo() const;

    /**
     * @brief Retrieve a glyph of the font.
     * @param codePoint = Unicode code point of the character to get.
     * @param characterSize = Reference character size.
     * @param bold = Retrieve the bold version or the regular one?
     * @return The glyph corresponding to codePoint and characterSize.
     */
    const Glyph& getGlyph(uint32 codePoint, uint32 characterSize, bool bold) const;

    /**
     * @brief Get the kerning offset of two glyphs.
     * @param first = Unicode code point of the first character.
     * @param second = Unicode code point of the second character.
     * @param characterSize =  Reference character size.
     * @return Kerning value for first and second, in pixels.
     */
    float getKerning(uint32 first, uint32 second, uint32 characterSize) const;

    /**
     * @brief Get the line spacing.
     * @param characterSize = Reference character size.
     * @return Line spacing, in pixels.
     */
    float getLineSpacing(uint32 characterSize) const;

    /**
     * @brief Get the position of the underline.
     * @param characterSize = Reference character size.
     * @return underline position, in pixels.
     */
    float getUnderlinePosition(uint32 characterSize) const;

    /**
     * @brief Get the thickness of the underline.
     * @param characterSize = Reference character size.
     * @return Underline thickness, in pixels.
     */
    float getUnderlineThickness(uint32 characterSize) const;

    /**
     * @brief Retrieve the texture containing the loaded glyphs of a certain size.
     * @param characterSize = Reference character size.
     * @return Texture containing the glyphs of the requested size.
     */
    const Texture& getTexture(uint32 characterSize) const;

    /**
     * @brief Overload of assignment operator.
     * @param right = right Instance to assign.
     * @return Reference to self.
     */
    Font& operator =(const Font& right);

private:

    /**
     * @brief Structure defining a row of glyphs.
     */
    struct Row
    {
        Row(uint32 rowTop, uint32 rowHeight) : width(0), top(rowTop), height(rowHeight) {}

        uint32 width;
        uint32 top;
        uint32 height;
    };

    typedef std::map<uint32, Glyph> GlyphTable;

    /**
     * @brief Structure defining a page of glyphs.
     */
    struct Page
    {
        Page();

        GlyphTable glyphs;
        nx::Texture texture;
        uint32 nextRow;
        std::vector<Row> rows;
    };

    typedef std::map<unsigned int, Page> PageTable;

    /**
     * @brief Free all internal resources.
     */
    void cleanup();

    /**
     * @brief Load a new glyph and store it in the cache.
     * @param codePoint = Unicode code point of the character to load.
     * @param characterSize = Reference character size.
     * @param bold = Retrieve the bold version or the regular one?
     * @return The glyph corresponding to codePoint and characterSize.
     */
    Glyph loadGlyph(uint32 codePoint, uint32 characterSize, bool bold) const;

    /**
     * @brief Find a suitable rectangle within the texture for a glyph.
     * @param page = Page of glyphs to search in.
     * @param width = Width of the rectangle.
     * @param height = Height of the rectangle.
     * @return Found rectangle within the texture.
     */
    recti findGlyphRect(Page& page, uint32 width, uint32 height) const;

    /**
     * @brief Make sure that the given size is the current one.
     * @param characterSize = Reference character size.
     * @return true on success, false if any error happened.
     */
    bool setCurrentSize(uint32 characterSize) const;

    /**
     * @brief Pointer to the internal library interface (it is typeless to avoid exposing implementation details).
     */
    void* m_library;

    /**
     * @brief Pointer to the internal font face (it is typeless to avoid exposing implementation details).
     */
    void* m_face;

    /**
     * @brief Pointer to the stream rec instance (it is typeless to avoid exposing implementation details).
     */
    void* m_streamRec;

    /**
     * @brief Reference counter used by implicit sharing.
     */
    int* m_refCount;

    /**
     * @brief Information about the font.
     */
    Info m_info;

    /**
     * @brief Table containing the glyphs pages by character size.
     */
    mutable PageTable m_pages;

    /**
     * @brief Pixel buffer holding a glyph's pixels before being written to the texture
     */
    mutable std::vector<uint8> m_pixelBuffer;

};

} // namespace nx

#endif // FONT_H_INCLUDE
