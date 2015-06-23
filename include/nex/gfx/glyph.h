#ifndef GLYPH_H_INCLUDE
#define GLYPH_H_INCLUDE

#include <nex/math/rect.h>

using sf::IntRect;
using sf::FloatRect;

namespace nx
{

struct Glyph
{
    Glyph() :
        advance(0)
    {}

    float advance;
    rectf bounds;
    recti textureRect;
};

} // namespace nx

#endif // GLYPH_H_INCLUDE
