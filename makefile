CC=gcc
CXXFLAGS=-ggdb -Wall
LDLIBS=-lglut -lGLU -lGL -ljpeg -lm

all: corp

corp: corp.cpp
		$(CC) $(CXXFLAGS) $(LDLIBS) vector_util.cpp corp.cpp -o corp
clean:
	rm corp
