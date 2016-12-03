CC=clang++
CXX=clang++
CXXFLAGS=-Wall -Werror -Wextra -std=c++1y -pthread
SRC=main.cc neuralnet.cc
OBJ=$(SRC:.cc=.o)
BIN=main


all: ${BIN}


${BIN}: ${OBJ}
	${CC} ${CXXFLAGS} -o $@ $^


clean:
	${RM} ${OBJ} ${BIN}
