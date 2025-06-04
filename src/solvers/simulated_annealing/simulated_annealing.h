#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include <map>

#include "tsp_solver.h"

typedef struct {
    float distance;
    std::vector<int> gens;
} candidate_t;

class SimulatedAnnealing : public TSPSolver {
    private:
        std::map<std::string, int> configs_table;
        candidate_t initialize_candidate_(std::vector<std::vector<float>> &dist);
        void calc_distance_(candidate_t &candidate, std::vector<std::vector<float>> &dist);
        candidate_t generate_neighbour_(candidate_t candidate);
        bool is_acceptable_(candidate_t &candidate, candidate_t &neighbour);
    public:
        SimulatedAnnealing();
        solution_t solve(std::vector<std::vector<float>> &dist);
        configs_status_t configure_solver(std::map<std::string, int> solver_configs);
};

#endif //SIMULATED_ANNEALING_H
