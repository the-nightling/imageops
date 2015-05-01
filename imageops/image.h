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

namespace global{

class Image
{
private:
    std::string fileType;
    int width, height, size, maxGrayVal;
    std::unique_ptr<unsigned char[]> data;

public:
    Image(int width, int height, int maxGrayVal, unsigned char data[]);     // constructor
    Image(std::string filename);                // constructor
    Image(const Image &rhs);                    // copy constructor
    Image(Image &&rhs);                         // move constructor
    Image & operator = (const Image &rhs);      // copy assignment operator
    Image & operator = (Image &&rhs);           // move assignment operator
    ~Image();                                   // destructor

    friend std::ostream & operator << (std::ostream & os, const Image & image);     // input assignment operator
    friend std::istream & operator >> (std::istream & is, Image & image);           // output assignment operator
    Image & operator += (const Image &rhs);     // addition assignment operator

    // GETTERS
    int getWidth();
    int getHeight();
    int getSize();
    int getMaxGrayVal();
    std::string getFileType();

    // METHODS
    void copy(const Image &rhs);

    // inner iterator class
    class iterator
    {
    private:
        unsigned char *ptr;

        friend class Image;

        // constructor
        iterator(unsigned char *p) : ptr(p) {}

    public:
        // copy constructor
        iterator(const iterator &rhs) : ptr(rhs.ptr) {}

        // copy assignment operator
        iterator & operator = (const iterator &rhs)
        {
            if(this != &rhs)
            {
                *ptr = *rhs.ptr;
            }

            return *this;
        }

        // increment operator
        iterator & operator ++ ()
        {
            ptr += 1;
            return *this;
        }

        // dereferencing operator
        unsigned char & operator * ()
        {
            return *ptr;
        }

        // inequality operator
        bool operator != (const iterator &rhs)
        {
            return ptr != rhs.ptr;
        }
    };
    // end of inner iterator class

    // iterator access methods
    iterator begin(void) const;
    iterator end(void) const;
};

}
#endif // IMAGE_H
