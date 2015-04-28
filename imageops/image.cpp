#include "image.h"
#include <iostream>
#include <sstream>
#include <fstream>

Image::Image(int width, int height)
{
    this->width = width;
    this->height = height;
    this->size = width*height;

    data = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
    for(int i = 0; i < size; i++) {
        data[i] = ' ';
    }
}

Image::Image(std::string filename)
{
    // open file stream in binary mode
    std::ifstream inputFileStream(filename, std::ios::binary);

    // parse file header
    inputFileStream >> fileType >> std::ws;
    std::string line; std::getline(inputFileStream, line);
    inputFileStream >> std::ws;
    inputFileStream >> height >> width >> maxGrayVal;
    size = width*height;

    // check data
    std::cout << "File type: " << fileType << std::endl;
    std::cout << "Line: " << line << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Size: " << size << std::endl;
    std::cout << "Max gray value: " << maxGrayVal << std::endl;

    // parse data values
    data = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
    for(int i = 0; i < size; i++) {
        unsigned char chr = inputFileStream.get();
        data[i] = chr;
    }

    // close file stream
    inputFileStream.close();
}

Image::Image(const Image &rhs)
    : fileType(rhs.fileType)
    , width(rhs.width)
    , height(rhs.height)
    , size(rhs.size)
    , maxGrayVal(rhs.maxGrayVal)
{
    data = std::unique_ptr<unsigned char[]>(new unsigned char[size]);
    for(int i = 0; i < size; i++) {
        data[i] = rhs.data[i];
    }
}

Image::Image(Image &&rhs)
    : fileType(std::move(rhs.fileType))
    , width(std::move(rhs.width))
    , height(std::move(rhs.height))
    , size(std::move(rhs.size))
    , maxGrayVal(std::move(rhs.maxGrayVal))
    , data(std::move(rhs.data))
{}

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
        for(int i = 0; i < size; i++) {
            data[i] = rhs.data[i];
        }
    }

    return *this;
}

Image & Image::operator = (Image &&rhs)
{
    fileType = std::move(rhs.fileType);
    width = std::move(rhs.width);
    height = std::move(rhs.height);
    size = std::move(rhs.size);
    maxGrayVal = std::move(rhs.maxGrayVal);
    data = std::move(rhs.data);

    return *this;
}

Image::~Image()
{}

Image::iterator Image::begin() const
{
     return iterator(data.get());
}

Image::iterator Image::end() const
{
    return iterator(data.get()+size-2);
}

void Image::copy(const Image &rhs)
{
    fileType = rhs.fileType;
    width = rhs.width;
    height = rhs.height;
    size = rhs.size;
    maxGrayVal = rhs.maxGrayVal;

    this->copy(rhs);

    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

    while(beg != end)
    {
        *beg = *inStart;
        ++beg; ++inStart;
    }
}
