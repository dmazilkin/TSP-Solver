#include <iostream>
#include <vector>
#include <map>

#include "tsp_solver.h"
#include "genetic_algorithm.h"

static const std::vector<std::string> SOLVERS = { "GENETIC" };

/******************** PUBLIC ********************/
TSPContext::TSPContext(void) {
    this->context_status = CONTEXT_SOLVER_UNDEFINED;
    this->configs_status = SOLVER_CONFIGS_OK;
    this->context_solver = nullptr;
}

TSPContext::TSPContext(std::string solver_name) {
    set_context_solver(solver_name);
}

void TSPContext::set_context_solver(std::string solver_name) {
    solver_name_status_t solver_name_status = check_solver_name_(solver_name);

    if (solver_name_status == SOLVER_AVAILABLE) {
        set_context_solver_(solver_name);
        this->context_status = CONTEXT_SOLVER_DEFINED;
    }
    else {
        this->context_status = CONTEXT_SOLVER_UNDEFINED;
    }
}

void TSPContext::set_solver_configs(std::map<std::string, int> solver_configs)
{
    this->configs_status = this->context_solver->configure_solver(solver_configs);
}

void TSPContext::solve(std::vector<std::vector<float>> &dist) {
    if (this->context_solver != nullptr) {
        this->context_solver->solve(dist);
    }
}


context_solver_status_t TSPContext::get_context_solver_status(void) {
    return this->context_status;
}

configs_status_t TSPContext::get_configs_status(void) {
    return this->configs_status;
}

/******************** PRIVATE ********************/
solver_name_status_t TSPContext::check_solver_name_(std::string solver_name) {
    solver_name_status_t has_solver = SOLVER_UNAVAILABLE;

    for (int i = 0; i < SOLVERS.size(); ++i) {
        if (solver_name == SOLVERS[i]) {
            has_solver = SOLVER_AVAILABLE;
        }
    }

    return has_solver;
}

void TSPContext::set_context_solver_(std::string solver) {
    if (solver == "GENETIC") {
        this->context_solver = std::make_unique<GeneticAlgorithm>();
    }
}
