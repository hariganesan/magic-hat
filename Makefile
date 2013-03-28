# Hari Ganesan 1/16/13
# Makefile for magic-hat

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include -L/sw/lib
SDL=-lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image
COCOA=-framework Cocoa
GL=-framework OpenGL -L/sw/lib
SRC=src
MAIN=src/main

all: $(SRC)/*.o main clean

# build main
main: main.o Decisions.o BridgeGame.o CardGame.o Elements.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

$(SRC)/*.o: $(SRC)/*.cpp
	$(CC) $(CFLAGS) -c $^

main.o: $(MAIN)/main.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
