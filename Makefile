# Hari Ganesan 1/16/13
# Makefile for magic-hat

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include -L/sw/lib
SDL=-lSDLmain -lSDL -lSDL_ttf
COCOA=-framework Cocoa
GL=-framework OpenGL -L/sw/lib

# build main
main: main.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
	rm *.h.gch
