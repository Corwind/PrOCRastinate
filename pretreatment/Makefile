CC=clang++
CXX=clang++
CXXFLAGS=-Wall -Werror -Wextra -std=c++1y -pthread `sdl2-config --cflags`
LIBS=`sdl2-config --libs` -lSDL2_image
SRC=main.cc grayscale.cc convolution.cc ../tools/surface.cc ../tools/events.cc
OBJ=$(SRC:.cc=.o)
BIN=main


all: ${BIN}


${BIN}: ${OBJ}
	${CC} ${CXXFLAGS} -o $@ $^ ${LIBS}


clean:
	${RM} ${OBJ} ${BIN}
