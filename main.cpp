/*
 * CSC3022H - Assignment 4
 * driver class:
 * - processes inputs from command line
 * - contains unit tests
 */

#define CATCH_CONFIG_RUNNER     // used for unit testing (supplying my own main)

#include <iostream>
#include <fstream>

#include "image.h"
#include "catch.hpp"    // for unit testing

using namespace::std;
using namespace::global;

int main(int argc, char* argv[]) {

    int result = 0;

    // run program
    if(argc < 2)
    {
        std::cout << "Insufficient number of parameters supplied." << std::endl;
        return 0;
    }
    else if(argc != 5 && std::string(argv[1]) == "-s")
    {
        // run unit tests
        result = Catch::Session().run(argc, argv);
    }
    else
    {
        if(std::string(argv[1]) == "-a")
        {
            if(argc < 5)
            {
                std::cout << "Insufficient number of parameters supplied." << std::endl;
            }
            else
            {
                Image I1, I2, I3;
                I1.load(argv[2]);
                I2.load(argv[3]);
                I3 = I1 + I2;
                I3.save(argv[4]);
            }
        }
        else if(std::string(argv[1]) == "-s")
        {
            if(argc < 5)
            {
                std::cout << "Insufficient number of parameters supplied." << std::endl;
            }
            else
            {
                Image I1, I2, I3;
                I1.load(argv[2]);
                I2.load(argv[3]);
                I3 = I1 - I2;
                I3.save(argv[4]);
            }
        }
        else if(std::string(argv[1]) == "-i")
        {
            if(argc < 4)
            {
                std::cout << "Insufficient number of parameters supplied." << std::endl;
            }
            else
            {
                Image I1;
                I1.load(argv[2]);
                !I1;
                I1.save(argv[3]);
            }
        }
        else if(std::string(argv[1]) == "-l")
        {
            if(argc < 5)
            {
                std::cout << "Insufficient number of parameters supplied." << std::endl;
            }
            else
            {
                Image I1, I2, I3;
                I1.load(argv[2]);
                I2.load(argv[3]);
                I3 = I1 / I2;
                I3.save(argv[4]);
            }
        }
        else if(std::string(argv[1]) == "-t")
        {
            if(argc < 5)
            {
                std::cout << "Insufficient number of parameters supplied." << std::endl;
            }
            else
            {
                Image I1, I2;
                I1.load(argv[2]);
                int f = std::atoi(std::string(argv[3]).c_str());
                I2 = I1 * f;
                I2.save(argv[4]);
            }
        }
        else
        {
            std::cout << "Unknown command: ";
            for(int i = 0; i < argc; i++)
            {
                std::cout << argv[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    return result;
}
