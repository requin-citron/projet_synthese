CC=gcc
CXXFLAGS=-ggdb -Wall
LDLIBS=-lglut -lGLU -lGL -ljpeg -lm

all: corp

corp: main.c
		$(CC) $(CXXFLAGS) $(LDLIBS) vector_util.c main.c spring.c head.c loadJpeg.c -o main
clean:
	rm main
