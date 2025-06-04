#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <map>

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
        std::map<std::string, int> configs_table;
        std::vector<individual_t> initialize_population_ (std::vector<std::vector<float>> &dist);
        void calc_fitness_ (std::vector<individual_t> &population, std::vector<std::vector<float>> &dist);
        std::vector<int> generate_child_(std::vector<parent_t> &parents);
        bool is_duplicate(std::vector<int> &gens, int gen);
        std::vector<int> get_unique_gens(std::vector<int> parent, std::vector<int> child);
        std::vector<int> fill_child_gens_(std::vector<int> &child, std::vector<int> parent);
        std::vector<individual_t> crossover_ (std::vector<individual_t> &population);
        std::vector<parent_t> select_parents_(std::vector<individual_t> &population);
    public:
        GeneticAlgorithm();
        solution_t solve(std::vector<std::vector<float>> &dist) override;
        configs_status_t configure_solver(std::map<std::string, int> solver_configs) override;
};

#endif //GENETIC_ALGORITHM_H
