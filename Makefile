GCC = clang++
CFLAGS = --std=c++23 -Wall -O2

SRC = src/*.cpp \
	src/file_utils/*.cpp \
	src/arg_parser/*.cpp \
	src/solvers/*.cpp \
	src/solvers/genetic_algorithm/*.cpp \
	src/solvers/simulated_annealing/*.cpp

INC = -Isrc/file_utils \
	-Isrc/arg_parser \
	-Isrc/solvers \
	-Isrc/solvers/genetic_algorithm \
	-Isrc/solvers/simulated_annealing

TARGET = build/tsp_solver

all: $(SRC)
	clear
	$(GCC) $(CFLAGS) $(INC) -o $(TARGET) $^

