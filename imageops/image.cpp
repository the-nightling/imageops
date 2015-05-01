#include "image.h"
#include <iostream>
#include <sstream>
#include <fstream>

namespace global{

// default constructor
Image::Image()
{
    this->fileType = "P5";
    this->width = 0;
    this->height = 0;
    this->size = 0;
    this->maxGrayVal = 0;
    this->data = nullptr;
}

// constructor (if image properties and data available)
Image::Image(int width, int height, int maxGrayVal, unsigned char data[])
{
    this->fileType = "P5";
    this->width = width;
    this->height = height;
    this->size = width*height;
    this->maxGrayVal = maxGrayVal;
    this->data = std::unique_ptr<unsigned char[]>(new unsigned char[size]); // create unique pointer
    for(int i = 0; i < size; i++) {
        this->data[i] = data[i];    // assign pointer values from data buffer
    }
}

// constructor (if only filename available)
Image::Image(std::string filename)
{
    // open file stream in binary mode
    std::ifstream inputFileStream(filename, std::ios::binary);

    // parse file stream into image object
    inputFileStream >> *this;

    // close file stream
    inputFileStream.close();
}

// copy constructor
Image::Image(const Image &rhs)
    : fileType(rhs.fileType)
    , width(rhs.width)
    , height(rhs.height)
    , size(rhs.size)
    , maxGrayVal(rhs.maxGrayVal)
{
    data = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
    this->copy(rhs);
}

// move constructor
Image::Image(Image &&rhs)
    : fileType(std::move(rhs.fileType))
    , width(std::move(rhs.width))
    , height(std::move(rhs.height))
    , size(std::move(rhs.size))
    , maxGrayVal(std::move(rhs.maxGrayVal))
{
    data = std::unique_ptr<unsigned char[]>(new unsigned char[rhs.size]);
    data = std::move(rhs.data);
}

// copy assignment operator
Image & Image::operator = (const Image &rhs)
{
    if(this != &rhs)
    {
        fileType = rhs.fileType;
        width = rhs.width;
        height = rhs.height;
        size = rhs.size;
        maxGrayVal = rhs.maxGrayVal;
        data = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
        this->copy(rhs);    // use copy method to deep copy data
    }

    return *this;
}

// move assignment operator
Image & Image::operator = (Image &&rhs)
{
    if(this != &rhs)
    {
        fileType = std::move(rhs.fileType);
        width = std::move(rhs.width);
        height = std::move(rhs.height);
        size = std::move(rhs.size);
        maxGrayVal = std::move(rhs.maxGrayVal);
        data = std::unique_ptr<unsigned char[]>(new unsigned char[rhs.size]);
        data = std::move(rhs.data);
    }

    return *this;
}

// destructor
Image::~Image()
{
    // no need to free memory since unique pointer is being used
}

// input assignment operator (input stream has to be binary for P5)
std::istream & operator >> (std::istream & is, Image & image)
{
    // parse file header
    is >> image.fileType >> std::ws;
    std::string line; std::getline(is, line);
    is >> std::ws;
    is >> image.height >> image.width >> image.maxGrayVal;
    image.size = image.width*image.height;
    is >> std::ws;

    // check data (comment out as necessary)
    /*
    std::cout << "File type: " << image.fileType << std::endl;
    std::cout << "Line: " << line << std::endl;
    std::cout << "Height: " << image.height << std::endl;
    std::cout << "Width: " << image.width << std::endl;
    std::cout << "Size: " << image.size << std::endl;
    std::cout << "Max gray value: " << image.maxGrayVal << std::endl;
    //*/

    // parse data values
    image.data = std::unique_ptr<unsigned char[]>(new unsigned char[image.size]);
    for(int i = 0; i < image.size; i++) {
        unsigned char chr = is.get();
        image.data[i] = chr;
    }

    return is;
}

// output assignment operator (output stream has to be binary for P5)
std::ostream & operator << (std::ostream & os, const Image & image)
{
    // write header
    os << "P5\n" << "#\n" << image.width << " " << image.height << "\n" << image.maxGrayVal << std::endl;

    // write data
    for(int i = 0; i < image.size; i++) {
        os << (unsigned char)image.data[i];
    }

    return os;
}

// equality operator
bool Image::operator == (const Image &rhs)
{
    if(
            this->getHeight() != rhs.getHeight() ||
            this->getWidth() != rhs.getWidth() ||
            this->getSize() != rhs.getSize() ||
            this->getMaxGrayVal() != rhs.getMaxGrayVal()
            )
    {
        return false;
    }
    else
    {
        bool result = true;
        Image::iterator beg = this->begin(), end = this->end();
        Image::iterator inStart = rhs.begin();

        while(beg != end)
        {
            if(*beg != *inStart)
            {
                result = false;
            }

            ++beg; ++inStart;
        }

        return result;
    }

}

// invert operator
Image & Image::operator ! ()
{
    Image::iterator beg = this->begin(), end = this->end();

    while(beg != end)
    {
        *beg = 255 - *beg;
        ++beg;
    }

    return *this;
}

// addition assignment operator
Image & Image::operator += (const Image &rhs)
{
    try
    {
        if(this->size != rhs.size) throw "Image size not equal.";

        Image::iterator beg = this->begin(), end = this->end();
        Image::iterator inStart = rhs.begin();

        while(beg != end)
        {
            if(*beg + *inStart > 255)
            {
                *beg = (unsigned char) 255;
            }
            else{
                *beg += *inStart;
            }

            ++beg; ++inStart;
        }
    } catch(const char *msg) {
        std::cerr << msg << std::endl;
    }

    return *this;
}

// subtraction assignment operator
Image & Image::operator -= (const Image &rhs)
{
    try
    {
        if(this->size != rhs.size) throw "Image size not equal.";

        Image::iterator beg = this->begin(), end = this->end();
        Image::iterator inStart = rhs.begin();

        while(beg != end)
        {
            if(*beg - *inStart < 0)
            {
                *beg = (unsigned char) 0;
            }
            else{
                *beg -= *inStart;
            }

            ++beg; ++inStart;
        }
    } catch(const char *msg) {
        std::cerr << msg << std::endl;
    }

    return *this;
}

// mask operator
Image Image::operator / (const Image &rhs)
{
    unsigned char *tempData = new unsigned char [rhs.size];
    Image result(rhs.width, rhs.height, rhs.maxGrayVal, tempData);

    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = rhs.begin();
    Image::iterator resultStart = result.begin();

    while(beg != end)
    {
        if(*inStart == 255)
        {
            *resultStart = *beg;
        }
        else
        {
            *resultStart = 0;
        }

        ++beg; ++inStart; ++resultStart;
    }

    return result;
}

// threshold operator
Image Image::operator *(int f)
{
    unsigned char *tempData = new unsigned char [size];
    Image result(width, height, maxGrayVal, tempData);

    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator resultStart = result.begin();

    while(beg != end)
    {
        if(*beg > f)
        {
            *resultStart = 255;
        }
        else
        {
            *resultStart = 0;
        }

        ++beg; ++resultStart;
    }

    return result;
}

// addition operator (relies on addition assignment operator)
Image operator + (const Image &lhs, const Image &rhs)
{
    Image result = lhs;

    return result += rhs;
}

// subtraction operator (relies on subtraction assignment operator)
Image operator - (const Image &lhs, const Image &rhs)
{
    Image result = lhs;

    return result -= rhs;
}

// GETTERS
int Image::getWidth() const {return this->width;}
int Image::getHeight() const {return this->height;}
int Image::getSize() const {return this->size;}
int Image::getMaxGrayVal() const {return this->maxGrayVal;}
std::string Image::getFileType() const {return this->fileType;}

// Method to deep copy data from an image object (uses iterators)
void Image::copy(const Image &rhs)
{
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = rhs.begin();

    while(beg != end)
    {
        *beg = *inStart;
        ++beg; ++inStart;
    }
}

// Method to load an image from file
Image & Image::load(std::string filename)
{
    try{
    // open file stream in binary mode
    std::ifstream inputFileStream(filename, std::ios::binary);

    if(inputFileStream)
    {
        // parse file stream into image object
        inputFileStream >> *this;

        // close filestream
        inputFileStream.close();
    }
    else
    {
        throw "Error opening file.";
    }

    } catch(const char *msg) {
        std::cerr << msg << std::endl;
    }
    return *this;
}

// Method to save an image to file
void Image::save(std::string filename)
{
    // open filestream in binary mode
    std::ofstream ostr(filename, std::ios::binary);

    // write image object into filestream
    ostr << *this;

    // close filestream
    ostr.close();
}

// ITERATOR ACCESS METHODS
Image::iterator Image::begin() const
{
    return iterator(data.get());
}

Image::iterator Image::end() const
{
    return iterator(data.get()+size-2);
}

}
