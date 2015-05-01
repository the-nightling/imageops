/*
 * CSC3022H - Assignment 4
 * driver class:
 * - processes inputs from command line
 * - contains unit tests
 */

#define CATCH_CONFIG_RUNNER     // used for unit testing (supplying my own main)

#include <iostream>
#include <fstream>
#include <image.h>

#include "catch.hpp"    // for unit testing

using namespace::std;
using namespace::global;

int main(int argc, char* argv[]) {

    Image image1(argv[1]);  // create an image object from file with filename from command line
    Image image2(image1);   // create a copy of the image object

    // save the copied image object to a file
    ofstream ostr("image_copy.pgm", std::ios::binary);
    ostr << image2;
    ostr.close();

    // run unit tests
    Catch::Session().run();

    return 0;
}

TEST_CASE("contructor", "[contructor]")
{
    Image image1("Lenna_hat_mask-1.pgm");  // create an image object from file

    // test
    REQUIRE(image1.getFileType() == "P5");
    REQUIRE(image1.getHeight() == 512);
    REQUIRE(image1.getWidth() == 512);
    REQUIRE(image1.getSize() == 262144);
    REQUIRE(image1.getMaxGrayVal() == 255);
}

TEST_CASE("copy_constructor", "[copy_constructor]")
{
    Image image1("Lenna_hat_mask-1.pgm");  // create an image object from file
    Image image2(image1);   // create a copy of the image object

    // test
    REQUIRE(image1.getFileType() == image2.getFileType());
    REQUIRE(image1.getHeight() == image2.getHeight());
    REQUIRE(image1.getWidth() == image2.getWidth());
    REQUIRE(image1.getSize() == image2.getSize());
    REQUIRE(image1.getMaxGrayVal() == image2.getMaxGrayVal());
}

TEST_CASE("copy_assignment", "[copy_assignment]")
{
    Image image1("Lena_hat_mask-1.pgm");    // create an image object from file

    unsigned char *data = new unsigned char [512*512];
    Image image2(512, 512, 255, data);      // create an image object with empty data

    image2 = image1;    // copy assign image

    // test
    REQUIRE(image1.getFileType() == image2.getFileType());
    REQUIRE(image1.getHeight() == image2.getHeight());
    REQUIRE(image1.getWidth() == image2.getWidth());
    REQUIRE(image1.getSize() == image2.getSize());
    REQUIRE(image1.getMaxGrayVal() == image2.getMaxGrayVal());

    free(data);
}
