#include <nex/core/displaymode.h>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <algorithm>
#include <iostream>

namespace nx
{

DisplayMode DisplayMode::getDesktopMode()
{
    DisplayMode desktopMode;

    // Open a connection with the X server
    Display* display = XOpenDisplay(NULL);
    if (display)
    {
        // Retrieve the default screen number
        int screen = DefaultScreen(display);

        // Check if the XRandR extension is present
        int version;
        if (XQueryExtension(display, "RANDR", &version, &version, &version))
        {
            // Get the current configuration
            XRRScreenConfiguration* config = XRRGetScreenInfo(display, RootWindow(display, screen));
            if (config)
            {
                // Get the current video mode
                Rotation currentRotation;
                int currentMode = XRRConfigCurrentConfiguration(config, &currentRotation);

                // Get the available screen sizes
                int nbSizes;
                XRRScreenSize* sizes = XRRConfigSizes(config, &nbSizes);
                if (sizes && (nbSizes > 0))
                    desktopMode = DisplayMode(sizes[currentMode].width, sizes[currentMode].height, DefaultDepth(display, screen));

                // Free the configuration instance
                XRRFreeScreenConfigInfo(config);
            }
            else
            {
                // Failed to get the screen configuration
                std::cout << "Failed to retrieve the screen configuration while trying to get the desktop video modes" << std::endl;
            }
        }
        else
        {
            // XRandr extension is not supported: we cannot get the video modes
            std::cout << "Failed to use the XRandR extension while trying to get the desktop video modes" << std::endl;
        }

        // Close the connection with the X server
        XCloseDisplay(display);
    }
    else
    {
        // We couldn't connect to the X server
        std::cout << "Failed to connect to the X server while trying to get the desktop video modes" << std::endl;
    }

    return desktopMode;
}

const std::vector<DisplayMode> DisplayMode::getFullscreenModes()
{
    std::vector<DisplayMode> modes;

    // Open a connection with the X server
    Display* display = XOpenDisplay(0);
    if (display)
    {
        // Retrieve the default screen number
        int screen = DefaultScreen(display);

        // Check if the XRandR extension is present
        int version;
        if (XQueryExtension(display, "RANDR", &version, &version, &version))
        {
            // Get the current configuration
            XRRScreenConfiguration* config = XRRGetScreenInfo(display, RootWindow(display, screen));
            if (config)
            {
                // Get the available screen sizes
                int nbSizes;
                XRRScreenSize* sizes = XRRConfigSizes(config, &nbSizes);
                if (sizes && (nbSizes > 0))
                {
                    // Get the list of supported depths
                    int nbDepths = 0;
                    int* depths = XListDepths(display, screen, &nbDepths);
                    if (depths && (nbDepths > 0))
                    {
                        // Combine depths and sizes to fill the array of supported modes
                        for (int i = 0; i < nbDepths; ++i)
                        {
                            for (int j = 0; j < nbSizes; ++j)
                            {
                                // Convert to VideoMode
                                DisplayMode mode(sizes[j].width, sizes[j].height, depths[i]);

                                // Add it only if it is not already in the array
                                if (std::find(modes.begin(), modes.end(), mode) == modes.end()) {

                                    // Only add if we have more that 16 bit per pixel.
                                    if (mode.bitsPerPixel >= 16)

                                    modes.push_back(mode);
                                }
                            }
                        }

                        // Free the array of depths
                        XFree(depths);
                    }
                }

                // Free the configuration instance
                XRRFreeScreenConfigInfo(config);
            }
            else
            {
                // Failed to get the screen configuration
                std::cout << "Failed to retrieve the screen configuration while trying to get the supported video modes" << std::endl;
            }
        }
        else
        {
            // XRandr extension is not supported: we cannot get the video modes
            std::cout << "Failed to use the XRandR extension while trying to get the supported video modes" << std::endl;
        }

        // Close the connection with the X server
        XCloseDisplay(display);
    }
    else
    {
        // We couldn't connect to the X server
        std::cout << "Failed to connect to the X server while trying to get the supported video modes" << std::endl;
    }

    std::sort(modes.begin(), modes.end(), std::greater<DisplayMode>());
    return modes;
}

} // namespace nx
