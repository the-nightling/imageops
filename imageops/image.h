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
public:
    std::string fileType;
    int width, height, size, maxGrayVal;
    std::unique_ptr<unsigned char[]> data;
public:
    Image(int width, int height);
    Image(std::string filename);
    Image(const Image &rhs);
    Image(Image &&rhs);
    Image & operator = (const Image &rhs);
    Image & operator = (Image &&rhs);
    ~Image();

    //Image & operator + (const Image &lhs, const Image &rhs);

    void copy(const Image &rhs);

    class iterator
    {
    private:
        unsigned char *ptr;

        friend class Image;

        iterator(unsigned char *p) : ptr(p) {}

    public:
        iterator(const iterator &rhs) : ptr(rhs.ptr) {}
        iterator & operator = (const iterator &rhs)
        {
            if(this != &rhs)
            {
                *ptr = *rhs.ptr;
            }

            return *this;
        }

        iterator & operator ++ ()
        {
            ptr += 1;
            return *this;
        }

        unsigned char & operator * ()
        {
            return *ptr;
        }

        bool operator != (const iterator &rhs)
        {
            return ptr != rhs.ptr;
        }
    };

    iterator begin(void) const;

    iterator end(void) const;
};

#endif // IMAGE_H
