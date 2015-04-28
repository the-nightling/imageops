#include <iostream>
#include <fstream>
#include <sstream>
#include <image.h>
using namespace::std;

int main(int argc, char* argv[]) {

    Image image1(argv[1]);
    Image image2(image1);

    //*
    // write a new P2 binary ascii image
    ofstream ostr("greyscale_ascii_version.pgm");
    // write header
    ostr << "P2\n" << image2.width << " " << image2.height << "\n" << image2.maxGrayVal << endl;
    // write data
    int line_ctr = 0;
    for(int i = 0; i < image2.size; i++) {
        // print pixel value
        ostr << (unsigned int)image2.data[i] << " ";
        // endl every ~20 pixels for some readability
        if(++line_ctr % 20 == 0) ostr << endl;
    }
    ostr.close();

    //*/

    return 0;
}
