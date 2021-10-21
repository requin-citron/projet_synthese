CC=gcc
CXXFLAGS=-ggdb -Wall
LDLIBS=-lglut -lGLU -lGL -ljpeg -lm
RM=rm


all: vector_util.o spring.o head.o loadJpeg.o dragon.o main.o oeil.o
		$(CC) $(CXXFLAGS) $(LDLIBS) $^ -o main
main.o: main.c main.h
		$(CC) $(CXXFLAGS) $(LDLIBS) -c $<
dragon.o:dragon.c dragon.h
		$(CC) $(CXXFLAGS) $(LDLIBS) -c $<
loadJpeg.o:loadJpeg.c loadJpeg.h
		$(CC) $(CXXFLAGS) $(LDLIBS) -c $<
head.o:head.c head.h
		$(CC) $(CXXFLAGS) $(LDLIBS) -c $<
spring.o:spring.c spring.h
		$(CC) $(CXXFLAGS) $(LDLIBS) -c $<
oeil.o:oeil.c oeil.h
		$(CC) $(CXXFLAGS) $(LDLIBS) -c $<
vector_util.o:vector_util.c vector_util.h
		$(CC) $(CXXFLAGS) $(LDLIBS) -c $<
clean:clean_objet
	$(RM) main
clean_objet:
	$(RM) *.o
