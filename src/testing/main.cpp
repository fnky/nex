#include <iostream>
#include <cmath>

#include <nex/core/windowprovider.h>

using namespace nx;

int main(int argc, char** args)
{
    WindowProvider* window = WindowProvider::newInstance();
    if (!window->create(800, 600, Style::Default))
    {
        return false;
    }


    return 0;
}
