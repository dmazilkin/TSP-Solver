# TSP-Solver

A Traveling Salesman Problem Solver implemented in C++. Supports two metaheuristic algorithms: **Genetic Algorithm** and **Simulated Annealing**.

The project is designed using **Object-Oriented Programming** methods and applies the **Strategy Design Pattern** to enable easy switching and integration of different solving algorithms.

## Implemented Algorithms

- **Genetic Algorithm (GA)** — works with a population of individuals using crossover to search for an optimal path.
- **Simulated Annealing (SA)** — a stochastic algorithm that probabilistically accepts worse solutions to escape local minima, especially at high temperatures. At the beginning of the search, where temperature is high, neighbor solutions are generated using the simple **swap** method. As the temperature decreases, the algorithm switches to the more powerful **2-opt** method for generating neighbour.

## Project Structure

In the project directory you can find the following:

 - **src** - directory with all sources for compiling:
    - **main.c** - entry point, contains logic to start the TSP solver,
    - **arg_parser** - parser for program options,
    - **file_utils** - contains functions for processing input files, configs and saving found solutions.
    - **solvers** - contains **TSPSolver** class, that defines the interface for all TSP-solving algorithms, and **TSPContext** class, that stores a pointer to a TSPSolver and manages its execution. Also contains **Genetic Algorithm** and **Simulated Annealing** implementations.
- **configs** - contains possible and adjustable configs for borh Genetic Algorithm and Simulated Annealing.
- **input** - contains common configs to set TSP solver type.

# Usage
## Compiling
First compile source files into one executable file. Simply start Makefile script from project folder as follows:
```console
make 
```
after compiling is completed, **tsp_solver** executable file can be found in *build/* directory. 

## Running program
To run **main** program the following command:
```console
./build/tsp_solver
```
also don't forget to provide *program options* for input, output and operation.

### Available program options
To compress files or text by running **main** program you should also provide paths some arguments:
- use *-i* or *--input* for input file,
- use *-o* or *--output* for output file,
- use *-c* for common configs,

### Examples
Example of input text can be found in *input/* directory. This input file was taken from [tsplib repo](https://github.com/mastqe/tsplib).

#### Running example:
```console
 ./build/tsp_solver -i input/berlin52.tsp -o output/berlin-sa.txt -c input/berlin52-sa.cfg
```