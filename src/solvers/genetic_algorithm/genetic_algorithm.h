#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>

#include "tsp_solver.h"

typedef struct {
    float distance;
    float fitness;
    float cumulative_fitness;
    std::vector<int> gens;
} individual_t;

typedef struct {
    bool is_found;
    individual_t individual;
} parent_t;

class GeneticAlgorithm : public TSPSolver {
    private:
        std::vector<std::vector<int>> initialize_population_ (int population_size, int individual_size);
        std::vector<individual_t> calc_fitness_ (std::vector<std::vector<int>> population, std::vector<std::vector<float>> dist);
        std::vector<individual_t> crossover_ (std::vector<individual_t> fitness_population);
        std::vector<parent_t> select_parents_(std::vector<individual_t> population);
    public:
        void solve(std::vector<std::vector<float>> dist) override;
};

#endif //GENETIC_ALGORITHM_H
