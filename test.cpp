/*
 * CSC3022H - Assignment 4
 * test class using catch.hpp framework
 */

#include "catch.hpp"
#include "image.h"

using namespace global;

TEST_CASE("constructor", "[constructor]")
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
    bool imageEqual = false;
    if(image1 == image2) imageEqual = true;
    REQUIRE(imageEqual);
}

TEST_CASE("copy_assignment", "[copy_assignment]")
{
    Image image1("Lenna_standard-1.pgm");    // create an image object from file
    Image image2;

    image2 = image1;    // copy assign image

    // test
    bool imageEqual = false;
    if(image1 == image2) imageEqual = true;
    REQUIRE(imageEqual);
}

TEST_CASE("invert", "[invert]")
{
    Image image1("Lenna_standard-1.pgm");    // create an image object from file
    Image image2(image1);   // create a copy of the image object
    !image2;    // invert the copied image
    !image2;    // invert the copied image a second time

    // test
    bool imageEqual = false;
    if(image1 == image2) imageEqual = true;
    REQUIRE(imageEqual);
}

TEST_CASE("add_move", "[add][move]")
{
    Image image1("Lenna_standard-1.pgm");    // create an image object from file
    Image image2(image1);   // create a copy of the image object

    !image2;    // invert the copied image

    // adding an image with its mask will give a white image (all values are 255)
    Image image3(image1 + image2);

    bool imageIsWhite = true;
    Image::iterator beg = image3.begin(), end = image3.end();
    while(beg != end)
    {
        if(*beg != 255)
        {
            imageIsWhite = false;
        }
        ++beg;
    }

    // test
    REQUIRE(imageIsWhite);
}

TEST_CASE("subtract_move", "[subtract][move]")
{
    Image image1("Lenna_standard-1.pgm");    // create an image object from file

    // subtracting an image from itself will give a black image (all values are 0)
    Image image3(image1 - image1);

    bool imageIsBlack = true;
    Image::iterator beg = image3.begin(), end = image3.end();
    while(beg != end)
    {
        if(*beg != 0)
        {
            imageIsBlack = false;
        }
        ++beg;
    }

    // test
    REQUIRE(imageIsBlack);
}

TEST_CASE("save_load", "[save][load]")
{
    Image image1;
    image1.load("Lenna_standard-1.pgm");
    image1.save("image_copy.pgm");

    // test
    REQUIRE(image1.getSize() != 0);
}

TEST_CASE("mask_threshold", "[mask][threshold]")
{
    Image U1("Lenna_standard-1.pgm");   // create an image object from file
    Image M1(U1 * 150);                 // create a mask via thresholding
    Image M2(M1);                       // copy the mask
    !M2;                                // invert the mask copy
    Image R1(U1/M1);                    // create masked image 1 using the mask
    Image R2(U1/M2);                    // create masked image 2 using the inverted mask
    Image U2(R1+R2);                    // adding the two masked images gives the original image
    U2.save("mask_threshold_test.pgm"); // save the image to file

    // test
    bool imageEqual = false;
    if(U1 == U2) imageEqual = true;
    REQUIRE(imageEqual);
}

TEST_CASE("iterator", "[iterator]")
{
    Image image1;
    image1.load("Lenna_standard-1.pgm");

    Image::iterator beg = image1.begin(), end = image1.end();

    REQUIRE(*beg == 155);   // test dereference operator
    REQUIRE(beg != end);    // test inequality operator

    while(beg != end) ++beg;
    REQUIRE(!(beg != end)); // test increment operator and boundary case
}
