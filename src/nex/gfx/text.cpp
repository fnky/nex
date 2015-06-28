#include <nex/gfx/text.h>

// Standard includes.
#include <cmath>

namespace nx
{

Text::Text() :
    m_string(),
    m_font(0),
    m_characterSize(30),
    m_style(Regular),
    m_color(255, 255, 255),
    m_bounds(),
    m_geometryNeedUpdate(false)
{
    m_vertexArray.create();
    m_vertexBuffer.create();
}

Text::Text(const String& string, const Font& font, unsigned int characterSize) :
m_string            (string),
m_font              (&font),
m_characterSize     (characterSize),
m_style             (Regular),
m_color             (255, 255, 255),
m_bounds            (),
m_geometryNeedUpdate(true)
{

}

void Text::setString(const String& string)
{
    if (m_string != string)
    {
        m_string = string;
        m_geometryNeedUpdate = true;
    }
}

void Text::setFont(const Font& font)
{
    if (m_font != &font)
    {
        m_font = &font;
        m_geometryNeedUpdate = true;
    }
}

void Text::setCharacterSize(unsigned int size)
{
    if (m_characterSize != size)
    {
        m_characterSize = size;
        m_geometryNeedUpdate = true;
    }
}

void Text::setStyle(uint32 style)
{
    if (m_style != style)
    {
        m_style = style;
        m_geometryNeedUpdate = true;
    }
}

void Text::setColor(const Color& color)
{
    if (color != m_color)
    {
        m_color = color;

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            for (std::size_t i = 0; i < m_vertices.size(); ++i)
                m_vertices[i].color = m_color.toVector();
        }
    }
}

const String& Text::getString() const
{
    return m_string;
}

const Font* Text::getFont() const
{
    return m_font;
}

uint32 Text::getCharacterSize() const
{
    return m_characterSize;
}

uint32 Text::getStyle() const
{
    return m_style;
}

const Color& Text::getColor() const
{
    return m_color;
}

vec2f Text::findCharacterPos(std::size_t index) const
{
    // Make sure that we have a valid font
    if (!m_font)
        return vec2f();

    // Adjust the index if it's out of range
    if (index > m_string.getSize())
        index = m_string.getSize();

    // Precompute the variables needed by the algorithm
    bool  bold   = (m_style & Bold) != 0;
    float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
    float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));

    // Compute the position
    vec2f position;
    uint32 prevChar = 0;
    for (std::size_t i = 0; i < index; ++i)
    {
        uint32 curChar = m_string[i];

        // Apply the kerning offset
        position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        prevChar = curChar;

        // Handle special characters
        switch (curChar)
        {
            case ' ':  position.x += hspace;                 continue;
            case '\t': position.x += hspace * 4;             continue;
            case '\n': position.y += vspace; position.x = 0; continue;
        }

        // For regular characters, add the advance offset of the glyph
        position.x += static_cast<float>(m_font->getGlyph(curChar, m_characterSize, bold).advance);
    }

    return position;
}

/*void Text::draw(RenderTarget& target, RenderStates states) const
{
    if (m_font)
    {
        ensureGeometryUpdate();

        states.transform *= getTransform();
        states.texture = &m_font->getTexture(m_characterSize);
        target.draw(m_vertices, states);
    }
}*/

void Text::ensureGeometryUpdate() const
{
    // Do nothing, if geometry has not changed
    if (!m_geometryNeedUpdate)
        return;

    // Mark geometry as updated
    m_geometryNeedUpdate = false;

    // Clear the previous geometry
    m_vertices.clear();
    m_bounds = rectf();

    // No font: nothing to draw
    if (!m_font)
        return;

    // No text: nothing to draw
    if (m_string.isEmpty())
        return;

    // Compute values related to the text style
    bool bold = (m_style & Bold) != 0;
    bool underlined  = (m_style & Underlined) != 0;
    bool strikeThrough = (m_style & StrikeThrough) != 0;

    float italic = (m_style & Italic) ? 0.208f : 0.f; // 12 degrees
    float underlineOffset = m_font->getUnderlinePosition(m_characterSize);
    float underlineThickness = m_font->getUnderlineThickness(m_characterSize);

    // Compute the location of the strike through dynamically
    // We use the center point of the lowercase 'x' glyph as the reference
    // We reuse the underline thickness as the thickness of the strike through as well
    rectf xBounds = m_font->getGlyph(L'x', m_characterSize, bold).bounds;
    float strikeThroughOffset = xBounds.y + xBounds.height / 2.f;

    // Precompute the variables needed by the algorithm
    float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
    float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));
    float x = 0.f;
    float y = static_cast<float>(m_characterSize);

    // Create one quad for each character
    float minX = static_cast<float>(m_characterSize);
    float minY = static_cast<float>(m_characterSize);
    float maxX = 0.f;
    float maxY = 0.f;

    const vec3f color = m_color.toVector();

    uint32 prevChar = 0;
    for (std::size_t i = 0; i < m_string.getSize(); ++i)
    {
        uint32 curChar = m_string[i];

        // Apply the kerning offset
        x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
        prevChar = curChar;

        // If we're using the underlined style and there's a new line, draw a line
        if (underlined && (curChar == L'\n'))
        {
            float top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
            float bottom = top + std::floor(underlineThickness + 0.5f);

            m_vertices.append(Vertex2d(vec2f(0, top), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(x, top), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(x, top), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(x, bottom), color, vec2f(1, 1)));
        }

        // If we're using the strike through style and there's a new line, draw a line across all characters
        if (strikeThrough && (curChar == L'\n'))
        {
            float top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
            float bottom = top + std::floor(underlineThickness + 0.5f);

            m_vertices.append(Vertex2d(vec2f(0, top), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(x, top), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(x, top), color, vec2f(1, 1)));
            m_vertices.append(Vertex2d(vec2f(x, bottom), color, vec2f(1, 1)));
        }

        // Handle special characters
        if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
        {
            // Update the current bounds (min coordinates)
            minX = std::min(minX, x);
            minY = std::min(minY, y);

            switch (curChar)
            {
                case ' ':  x += hspace;        break;
                case '\t': x += hspace * 4;    break;
                case '\n': y += vspace; x = 0; break;
            }

            // Update the current bounds (max coordinates)
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);

            // Next glyph, no need to create a quad for whitespace
            continue;
        }

        // Extract the current glyph's description
        const Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, bold);

        float left = glyph.bounds.x;
        float top = glyph.bounds.y;
        float right = glyph.bounds.x + glyph.bounds.width;
        float bottom = glyph.bounds.y  + glyph.bounds.height;

        float u1 = static_cast<float>(glyph.textureRect.x);
        float v1 = static_cast<float>(glyph.textureRect.y);
        float u2 = static_cast<float>(glyph.textureRect.x + glyph.textureRect.width);
        float v2 = static_cast<float>(glyph.textureRect.y + glyph.textureRect.height);

        // Add a quad for the current character
        m_vertices.append(Vertex2d(vec2f(x + left  - italic * top,    y + top),    color, vec2f(u1, v1)));
        m_vertices.append(Vertex2d(vec2f(x + right - italic * top,    y + top),    color, vec2f(u2, v1)));
        m_vertices.append(Vertex2d(vec2f(x + left  - italic * bottom, y + bottom), color, vec2f(u1, v2)));
        m_vertices.append(Vertex2d(vec2f(x + left  - italic * bottom, y + bottom), color, vec2f(u1, v2)));
        m_vertices.append(Vertex2d(vec2f(x + right - italic * top,    y + top),    color, vec2f(u2, v1)));
        m_vertices.append(Vertex2d(vec2f(x + right - italic * bottom, y + bottom), color, vec2f(u2, v2)));

        // Update the current bounds
        minX = std::min(minX, x + left - italic * bottom);
        maxX = std::max(maxX, x + right - italic * top);
        minY = std::min(minY, y + top);
        maxY = std::max(maxY, y + bottom);

        // Advance to the next character
        x += glyph.advance;
    }

    // If we're using the underlined style, add the last line
    if (underlined)
    {
        float top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
        float bottom = top + std::floor(underlineThickness + 0.5f);

        m_vertices.append(Vertex2d(vec2f(0, top),    color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(x, top),    color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(x, top),    color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(x, bottom), color, vec2f(1, 1)));
    }

    // If we're using the strike through style, add the last line across all characters
    if (strikeThrough)
    {
        float top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
        float bottom = top + std::floor(underlineThickness + 0.5f);

        m_vertices.append(Vertex2d(vec2f(0, top),    color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(x, top),    color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(0, bottom), color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(x, top),    color, vec2f(1, 1)));
        m_vertices.append(Vertex2d(vec2f(x, bottom), color, vec2f(1, 1)));
    }

    // Update the bounding rectangle
    m_bounds.x = minX;
    m_bounds.y = minY;
    m_bounds.width = maxX - minX;
    m_bounds.height = maxY - minY;
}
} // namespace nx
