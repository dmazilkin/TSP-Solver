GCC = clang++
CFLAGS = --std=c++23 -Wall -O2

SRC = src/*.cpp
TARGET = build/tsp_solver

all: $(SRC)
	$(GCC) $(CFLAGS) -o $(TARGET) $^

