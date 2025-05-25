GCC = clang++
CFLAGS = --std=c++23 -Wall -O2

SRC = src/*.cpp \
	src/io_utils/*.cpp \
	src/arg_parser/*.cpp
INC = -Isrc/io_utils \
	-Isrc/arg_parser
TARGET = build/tsp_solver

all: $(SRC)
	$(GCC) $(CFLAGS) $(INC) -o $(TARGET) $^

