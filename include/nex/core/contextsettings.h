#ifndef CONTEXTSETTINGS_H_INCLUDE
#define CONTEXTSETTINGS_H_INCLUDE

#include <nex/system/typedefs.h>

namespace nx
{

/**
 * @brief This struct defines some settings for the opengl context.
 */
struct ContextSettings
{
    ContextSettings(uint32 depth = 0,
                    uint32 stencil = 0,
                    uint32 antialiasing = 0,
                    uint32 major = 4,
                    uint32 minor = 4) :
        depthBits(depth),
        stencilBits(stencil),
        antialiasingLevel(antialiasing),
        majorVersion(major),
        minorVersion(minor)
    { }

    uint32 depthBits;
    uint32 stencilBits;
    uint32 antialiasingLevel;
    uint32 majorVersion;
    uint32 minorVersion;
};

} // namespace nx

#endif // CONTEXTSETTINGS_H_INCLUDE
