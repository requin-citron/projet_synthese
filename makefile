CC=gcc
CXXFLAGS=-ggdb -Wall
LDLIBS=-lglut -lGLU -lGL -ljpeg -lm

all: corp

corp: corp.c
		$(CC) $(CXXFLAGS) $(LDLIBS) vector_util.c corp.c spring.c -o corp
clean:
	rm corp
