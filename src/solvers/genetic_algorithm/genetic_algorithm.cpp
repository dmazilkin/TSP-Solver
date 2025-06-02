#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "genetic_algorithm.h"
#include "tsp_solver.h"

/******************** DEFINES ********************/
#define POPULATION_SIZE 100
#define ROULUTTE_WHEEL_MIN 0
#define ROULUTTE_WHEEL_MAX 100
#define PARENTS_COUNT 2
#define BEST_COUNT 10
#define MAX_EPOCHS 500
#define UNDEFINED -1

/******************** STATIC FUNCTIONS DECLARATION ********************/
static bool compare_populations(individual_t &ind1, individual_t  &ind2);

/******************** PUBLIC ********************/
void GeneticAlgorithm::solve(std::vector<std::vector<float>> &dist)
{
    /* Initialize population */
    std::vector<individual_t> population = initialize_population_(dist);
    calc_fitness_(population, dist);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        std::cout << population[i].distance << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
    /* Start Genetic Algorithm */
    for (int i = 0; i < MAX_EPOCHS; i++) {
        /* Generate new population */
        std::vector<individual_t> new_generation = crossover_(population);
        calc_fitness_(new_generation, dist);
        population = new_generation;
        if (i == MAX_EPOCHS - 1) {
            for (int i = 0; i < POPULATION_SIZE; i++) {
                std::cout << population[i].distance << std::endl;
            }
        }
    }
}

/******************** PRIVATE ********************/
std::vector<individual_t> GeneticAlgorithm::initialize_population_(std::vector<std::vector<float>> &dist)
{
    int individual_size = dist.size();
    std::vector<individual_t> population(POPULATION_SIZE,
        {
            .distance=0,
            .fitness=0,
            .cumulative_fitness=0,
            .gens=std::vector<int>(individual_size, UNDEFINED),
        }
    );

    for (int i = 0; i < POPULATION_SIZE; i++) {

        for (int j = 0; j < individual_size; j++) {
            population[i].gens[j] = j;
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(population[i].gens.begin(), population[i].gens.end(), g);
    }


    return population;
}

void GeneticAlgorithm::calc_fitness_(std::vector<individual_t> &population, std::vector<std::vector<float>> &dist)
{
    float max_dist = 0.0;
    int individual_size = dist.size();

    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < individual_size; j++) {

            if (j == individual_size - 1) {
                int current = population[i].gens[j];
                int next = population[i].gens[0];
                population[i].distance += dist[current][next];
            }
            else {
                int current = population[i].gens[j];
                int next = population[i].gens[j + 1];
                population[i].distance += dist[current][next];
            }
        }

        if (population[i].distance > max_dist) {
            max_dist = population[i].distance;
        }
    }

    std::sort(population.begin(), population.end(), compare_populations);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i].fitness = POPULATION_SIZE - i;
    }

    int fitness_sum = POPULATION_SIZE * (population[0].fitness + population[POPULATION_SIZE - 1].fitness) / 2;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i].fitness = 100 * population[i].fitness / fitness_sum;
        if (i == 0) {
            population[i].cumulative_fitness = population[i].fitness;
        }
        else {
            population[i].cumulative_fitness = population[i-1].cumulative_fitness + population[i].fitness;
        }
    }
}

std::vector<individual_t> GeneticAlgorithm::crossover_(std::vector<individual_t> &population)
{
    int individual_size = population[0].gens.size();
    std::vector<individual_t> new_generation(POPULATION_SIZE,
        {
            .distance=0,
            .fitness=0,
            .cumulative_fitness=0,
            .gens=std::vector<int>(individual_size, UNDEFINED),
        }
    );

    /* Save first best individuals without changes */
    for (int i = 0; i < BEST_COUNT; i++) {
        new_generation[i].gens = population[i].gens;
    }

    /* Create new individuals from existed */
    for (int i = BEST_COUNT; i < POPULATION_SIZE; i++) {
        /* Select parents using uniform distribution */
        std::vector<parent_t> parents = select_parents_(population);
        std::vector<int> child = generate_child_(parents);
        new_generation[i].gens = child;
    }

    return new_generation;
}

static bool compare_populations(individual_t &ind1, individual_t &ind2)
{
    return ind1.distance < ind2.distance;
}

std::vector<parent_t> GeneticAlgorithm::select_parents_(std::vector<individual_t> &population)
{
    /* Configure random uniform device */
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> roulette_wheel(ROULUTTE_WHEEL_MIN, ROULUTTE_WHEEL_MAX);
    /* Select parents for new child */
    int individual_size = population[0].gens.size();
    std::vector<parent_t> parents(PARENTS_COUNT,
        {
            .is_found=false,
            .individual={
                .distance=0.0,
                .fitness=0.0,
                .cumulative_fitness=0.0,
                .gens=std::vector<int>(individual_size, UNDEFINED),
            },
        }
    );

    for (int i = 0; i < PARENTS_COUNT; i++) {
        int ind = 0;
        float cumulative_fitness = roulette_wheel(g);

        while (!parents[i].is_found and (ind < POPULATION_SIZE)) {
            if (population[ind].cumulative_fitness >= cumulative_fitness) {
                parents[i].individual = population[ind];
                parents[i].is_found = true;
            }
            else {
                ind++;
            }
        }
    }

    return parents;
}

std::vector<int> GeneticAlgorithm::generate_child_(std::vector<parent_t> &parents)
{
    int individual_size = parents[0].individual.gens.size();
    std::vector<int> child(individual_size, UNDEFINED);

    /* Generate gens range to inherite from first parent */
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> range_boundary(0, individual_size-1);
    int first_parent_start = range_boundary(g);
    int first_parent_stop = range_boundary(g);

    if (first_parent_start > first_parent_stop) {
        int temp = first_parent_start;
        first_parent_start = first_parent_stop;
        first_parent_stop = temp;
    }

    /* Inherite gens from first parent */
    std::vector<int> gens_from_first(first_parent_stop - first_parent_start, UNDEFINED);
    int gens_ind = 0;

    for (int i = first_parent_start; i < first_parent_stop; i++) {
        child[i] = parents[0].individual.gens[i];
        gens_from_first[gens_ind] = parents[0].individual.gens[i];
        gens_ind++;
    }

    /* Inherite gens from second parent */
    std::vector<int> parent_gens = get_unique_gens(parents[1].individual.gens, gens_from_first);
    child = fill_child_gens_(child, parent_gens);

    return child;
}

std::vector<int> GeneticAlgorithm::get_unique_gens(std::vector<int> parent, std::vector<int> child)
{
    int unique_count = parent.size() - child.size();
    std::vector<int> unique_gens(unique_count, UNDEFINED);
    int unique_ind = 0;

    for (int i = 0; i < parent.size(); i++) {
        bool is_unique = true;
        int child_ind = 0;

        while (is_unique and child_ind < child.size()) {
            is_unique = parent[i] != child[child_ind];
            child_ind++;
        }

        if (is_unique) {
            unique_gens[unique_ind] = parent[i];
            unique_ind++;
        }
    }

    return unique_gens;
}

std::vector<int> GeneticAlgorithm::fill_child_gens_(std::vector<int> &child, std::vector<int> parent)
{
    int parent_ind = 0;

    for (int i = 0; i < child.size(); i++) {
        if (child[i] == UNDEFINED) {
            child[i] = parent[parent_ind];
            parent_ind++;
        }
    }

    return child;
}