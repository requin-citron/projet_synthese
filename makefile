CC=gcc
CFLAGS=-ggdb -Wall
LDLIBS=-lglut -lGLU -lGL -ljpeg -lm
RM=rm


all: vector_util.o spring.o head.o loadJpeg.o dragon.o main.o oeil.o laser.o fire.o corne.o ailes.o sun.o
		$(CC) $(CFLAGS) $(LDLIBS) $^ -o main
main.o: main.c main.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
dragon.o:dragon.c dragon.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
loadJpeg.o:loadJpeg.c loadJpeg.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
head.o:head.c head.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
spring.o:spring.c spring.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
oeil.o:oeil.c oeil.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
vector_util.o:vector_util.c vector_util.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
laser.o:laser.c laser.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
fire.o:fire.c fire.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
corne.o:corne.c corne.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
ailes.o: ailes.c ailes.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
sun.o: sun.c sun.h
		$(CC) $(CFLAGS) $(LDLIBS) -c $<
clean:clean_objet
		$(RM) main
clean_objet:
		$(RM) *.o
doc:
		doxygen
clean_doc:
		$(RM) -rf ./html
