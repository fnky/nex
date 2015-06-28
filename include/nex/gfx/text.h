#ifndef TEXT_H_INCLUDE
#define TEXT_H_INCLUDE

// Standard includes.
#include <string>
#include <vector>

// Nex includes.
#include <nex/system/string.h>
#include <nex/gfx/vertex2d.h>
#include <nex/gfx/vertexlist2d.h>
#include <nex/gfx/vertexbuffer.h>
#include <nex/gfx/vertexarray.h>
#include <nex/gfx/font.h>

namespace nx
{
class Text
{

public:

    enum Style
    {
        Regular       = 0,
        Bold          = 1 << 0,
        Italic        = 1 << 1,
        Underlined    = 1 << 2,
        StrikeThrough = 1 << 3
    };

    /**
     * @brief Default text constructor.
     */
    Text();

    Text(const String& string, const Font& font, uint32 characterSize = 30);

    void setString(const String& string);

    void setFont(const Font& font);

    void setCharacterSize(uint32 size);

    void setStyle(uint32 style);

    void setColor(const Color& color);

    const String& getString() const;

    const Font* getFont() const;

    uint32 getCharacterSize() const;

    uint32 getStyle() const;

    const Color& getColor() const;

    vec2f findCharacterPos(std::size_t index) const;

    //FloatRect getLocalBounds() const;

    //FloatRect getGlobalBounds() const;

    void render();

private:

    String m_string;

    const Font* m_font;

    uint32 m_characterSize;

    uint32 m_style;

    Color m_color;

    mutable VertexList2d m_vertices;

    mutable VertexBuffer m_vertexBuffer;

    mutable VertexArray m_vertexArray;

    mutable rectf m_bounds;

    mutable bool m_geometryNeedUpdate;

    void ensureGeometryUpdate() const;
};

} // namespace nx

#endif // TEXT_H_INCLUDE
