/*
 * CSC3022H - Assignment 4
 * Image class header file
 *
 * 27.04.15
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <memory>

class Image
{
private:
    int width, height;
    std::unique_ptr<unsigned char[]> data;

public:

    class iterator
    {
    private:
        unsigned char *ptr;

        // grant private access to Image class functions
        friend class Image;

        // construct only via Image class (begin/end)
        iterator(u_char *p) : ptr(p){}

    public:
        // copy constructor is public
        iterator(const iterator &rhs) : ptr(rhs.ptr){}

        // define overloaded ops: *, ++, --, =
        iterator & operator=(const iterator & rhs){}

        // other methods for iterator
    };

    Image(std::string filename);            // default constructor
    Image(const Image &rhs);                // copy constructor
    Image(Image &&rhs);                     // move constructor
    Image & operator = (const Image &rhs);  // copy assignment operator
    Image & operator = (Image &&rhs);       // move assignment operator
    ~Image();                               // destructor



    // define begin()/end() to get iterator to start and "one-past" end.
    // iterator begin(void){ return iterator(data.get()); }
};

#endif // IMAGE_H
