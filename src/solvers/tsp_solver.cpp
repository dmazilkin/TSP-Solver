#include <iostream>
#include <vector>

#include "tsp_solver.h"
#include "genetic_algorithm.h"

static const std::vector<std::string> SOLVERS = { "GENERIC" };

TSPContext::TSPContext(std::string solver) {
    status = check_solver(solver);

    if (status) {
        context_solver = get_context_solver(solver);
    }
}

bool TSPContext::check_solver(std::string solver) {
    bool has_solver = false;

    for (int i = 0; i < solvers.size(); ++i) {
        if (solver == solvers[i]) {
            has_solver = true;
        }
    }

    return has_solver;
}

TSPSolver& TSPContext::get_context_solver(std::string solver) {
    switch (solver) {
        case "GENETIC":
            return GeneticAlgorithm();
        else:
            /* Should never happen */
            break;
  }
}