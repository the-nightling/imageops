CC = g++
CPPFLAGS = -std=c++11 -fPIC
LDFLAGS = -std=c++11 -fPIC
RM = rm -f	# forcibly removes file(s)

PROGRAM = imageops
PROGRAM_OBJECTS = image.o main.o test.o

# build rules
$(PROGRAM): $(PROGRAM_OBJECTS)
	$(CC) $(PROGRAM_OBJECTS) -o $(PROGRAM) $(LIBS)

main.o: main.cpp image.h catch.hpp
	$(CC) main.cpp $(CPPFLAGS) -c

image.o: image.cpp image.h
	$(CC) image.cpp $(CPPFLAGS) -c

run:
	./${PROGRAM}

test:
	./${PROGRAM} -s

# other rules
clean:
	$(RM) $(PROGRAM_OBJECTS)
	$(RM) $(PROGRAM)

