# Hari Ganesan 1/16/13
# Makefile for magic-hat

# compiler options
CC=g++
CFLAGS=-Wall
INCLUDE=-I/sw/include -Itools/json_spirit_v4.05/json_spirit
SDL=-lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image
COCOA=-framework Cocoa
GL=-framework OpenGL
LIB= -L/sw/lib
SRC=src
MAIN=src/main
JSON=-ljson_spirit

all: $(SRC)/*.o main clean

# build main
main: main.o Decisions.o BridgeGame.o Tutorial.o CardGame.o Elements.o
	$(CC) -o $@ $(COCOA) $(GL) $(LIB) $(SDL) $^

$(SRC)/*.o: $(SRC)/*.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $^

main.o: $(MAIN)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $^

clean:
	rm *.o
