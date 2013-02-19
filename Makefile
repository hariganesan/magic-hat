# Hari Ganesan 1/16/13
# Makefile for magic-hat

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include -L/sw/lib
SDL=-lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image
COCOA=-framework Cocoa
GL=-framework OpenGL -L/sw/lib

all: main clean

# build main
main: main.o CardGame.o Elements.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^

CardGame.o: CardGame.cpp
	$(CC) $(CFLAGS) -c $^

Elements.o: Elements.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
