CSC3022H - Assignment 4
Author: 
Date: 02/05/15
---------------------------------------------------------------------------------------------------

Description:
Everything was implemented except for the bonus question.

---------------------------------------------------------------------------------------------------

Instructions:
A makefile is available to compile and run the program.

The following commands may be used to compile, run, test and clean up respectively:-

make			: compile the program
make run		: run the program with default parameters
make test		: run all unit tests
make clean		: will remove all binary files


Normal usage of the program is done using the command line, as per the tutorial specification:
	$ ./imageops <option> OutputImageName
	
	where the following options are available:
	-a InputImageName1 InputImageName2
	-s InputImageName1 InputImageName2
	-i InputImageName
	-l InputImageName1 InputImageName2
	-t InputImageName f

The image files 'Lenna_standard-1.pgm' and 'Lenna_hat_mask-1.pgm' are used for testing and need to be in the same folder as the executable.
All unit tests, supplied in the test.cpp file, can be run using:
	$ make test

This can also be achieved using:
	$ ./imageops -s
	(without the 'InputImageName1' and 'InputImageName2' arguments)

Additional catch.hpp command line options can be accessed by chaining them to '-s':
	$ ./imageops -s -l
	(lists all available tests)


Test cases:
constructor
copy_constructor
copy_assignment
invert
add_move
subtract_move
save_load
mask_threshold
iterator

---------------------------------------------------------------------------------------------------

List of files:
main.cpp
catch.hpp
image.h
image.cpp
.git/
README.txt
Makefile
