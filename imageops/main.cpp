#include <iostream>
#include <fstream>
#include <sstream>
#include <image.h>

using namespace::std;
using namespace::global;

int main(int argc, char* argv[]) {

    Image image1(argv[1]);  // create an image object from file with filename from command line
    Image image2(image1);   // create a copy of the image object

    // save the copied image object to a file
    ofstream ostr("greyscale_ascii_version.pgm", std::ios::binary);
    ostr << image2;
    ostr.close();

    return 0;
}
