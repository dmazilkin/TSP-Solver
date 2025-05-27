#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "tsp_solver.h"

class GeneticAlgorithm : public TSPSolver {
    public:
        void solve(void);
};

#endif //GENETIC_ALGORITHM_H
