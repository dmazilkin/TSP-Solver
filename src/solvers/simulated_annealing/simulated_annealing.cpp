#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

#include "simulated_annealing.h"

#define UNDEFINED -1

/******************** PUBLIC ********************/
SimulatedAnnealing::SimulatedAnnealing(void)
{
    this->configs_table = {
        { "TEMPERATURE", UNDEFINED },
        { "TEMPERATURE_FACTOR", UNDEFINED },
        { "MAX_EPOCHS", UNDEFINED },
    };
}

configs_status_t SimulatedAnnealing::configure_solver(std::map<std::string, int> solver_configs)
{
    configs_status_t configs_status = SOLVER_CONFIGS_OK;
    std::map<std::string, int>::iterator configs_it = this->configs_table.begin();

    while ((configs_status == SOLVER_CONFIGS_OK) and (configs_it != this->configs_table.end())) {
        std::string config = configs_it->first;

        if (solver_configs.contains(config)) {
            configs_it->second = solver_configs[config];
        }
        else {
            configs_status = SOLVER_CONFIGS_ERROR;
        }

        configs_it++;
    }

    if (configs_status == SOLVER_CONFIGS_ERROR) {
        std::cout << "ERROR! Required config for Genetic Algorithm not found!" << std::endl;
        return SOLVER_CONFIGS_ERROR;
    }

    return SOLVER_CONFIGS_OK;
}

solution_t SimulatedAnnealing::solve(std::vector<std::vector<float>> &dist)
{
    candidate_t candidate = initialize_candidate_(dist);
    calc_distance_(candidate, dist);

    std::cout << "Forst candidate:" << std::endl;
    for (int i = 0; i < candidate.gens.size(); i++) {
            std::cout << candidate.gens[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Distance = " << candidate.distance << std::endl;

    for (int i = 0; i < this->configs_table["MAX_EPOCHS"]; i++) {
        candidate_t neighbour = generate_neighbour_(candidate);
        calc_distance_(neighbour, dist);

        if (is_acceptable_(candidate, neighbour)) {
            candidate.gens = neighbour.gens;
            candidate.distance = neighbour.distance;
        }

        this->configs_table["TEMPERATURE"] *= this->configs_table["TEMPERATURE_FACTOR"];
    }

    solution_t solution = {
        .distance = candidate.distance,
        .gens = candidate.gens,
    };

    return solution;
}

/******************** PRIVATE ********************/
candidate_t SimulatedAnnealing::initialize_candidate_(std::vector<std::vector<float>> &dist)
{
    int candidate_size = dist.size();
    candidate_t candidate = {
        .distance=0.0,
        .gens=std::vector<int>(candidate_size, UNDEFINED),
    };

    for (int i = 0; i < candidate_size; i++) {
        candidate.gens[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(candidate.gens.begin(), candidate.gens.end(), g);

    return candidate;
}

void SimulatedAnnealing::calc_distance_(candidate_t &candidate, std::vector<std::vector<float>> &dist)
{
    int individual_size = dist.size();

    for (int j = 0; j < individual_size; j++) {

        if (j == individual_size - 1) {
            int current = candidate.gens[j];
            int next = candidate.gens[0];
            candidate.distance += dist[current][next];
        }
        else {
            int current = candidate.gens[j];
            int next = candidate.gens[j + 1];
            candidate.distance += dist[current][next];
        }
    }
}

candidate_t SimulatedAnnealing::generate_neighbour_(candidate_t candidate)
{   
    candidate_t neighbour = {
        .distance = 0.0,
        .gens = candidate.gens,
    };
    int individual_size = candidate.gens.size();
    /* Generate gens range to inherite from first parent */
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> gens_to_swap(0, individual_size-1);
    int first_gen = gens_to_swap(g);
    int second_gen = gens_to_swap(g);

    int temp_gen = neighbour.gens[first_gen];
    neighbour.gens[first_gen] = neighbour.gens[second_gen];
    neighbour.gens[second_gen] = temp_gen;

    return neighbour;
}

bool SimulatedAnnealing::is_acceptable_(candidate_t &candidate, candidate_t &neighbour)
{
    if (neighbour.distance < candidate.distance) {
        return true;
    }

    float probability = exp((-(neighbour.distance - candidate.distance)) / this->configs_table["TEMPERATURE"]);
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> gens_to_swap(0.0, 1.0);
    float acceptance_theshold = gens_to_swap(g);
    
    return probability >= acceptance_theshold;
}