#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "tsp_solver.h"

class GeneticAlgorithm : public TSPSolver {
    private:
        std::vector<std::vector<int>> initialize_population_ (int population_size, int individual_size);
        std::vector<float> calc_fitness_ (std::vector<std::vector<int>> population, std::vector<std::vector<float>> dist);
    public:
        void solve(std::vector<std::vector<float>> dist) override;
};

#endif //GENETIC_ALGORITHM_H
