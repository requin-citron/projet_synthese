CC=gcc
CXXFLAGS=-ggdb -Wall
LDLIBS=-lglut -lGLU -lGL -ljpeg -lm

all: corp

corp: corp.cpp
		$(CC) $(CXXFLAGS) $(LDLIBS) corp.cpp -o corp
clean:
	rm corp
