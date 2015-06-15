#include <iostream>

#include <nex/filesystem/directory.h>

using namespace nx;

int main(int argc, char** args)
{

    Directory::create("../..");
    Directory::remove("../..");
    return 0;
}
