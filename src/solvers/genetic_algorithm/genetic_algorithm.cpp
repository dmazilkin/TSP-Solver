#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "genetic_algorithm.h"
#include "tsp_solver.h"

/******************** DEFINES ********************/
#define POPULATION_SIZE 100
#define PARENTS_COUNT 2
#define SAVE_WITHOUT_CHANGES 5

/******************** STATIC FUNCTIONS DECLARATION ********************/
static bool compare_populations(individual_t& ind1, individual_t& ind2);

/******************** PUBLIC ********************/
void GeneticAlgorithm::solve(std::vector<std::vector<float>> &dist)
{
    /* Initialize population */
    std::vector<individual_t> population = initialize_population_(dist);
    /* Generate new population */
    std::vector<individual_t> new_generation = crossover_(population);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < population[i].gens.size(); j++) {
            std::cout << population[i].gens[j] << " ";
        }
        std::cout << std::endl;
        std::cout << "Fitness: " << population[i].fitness << std::endl;
        std::cout << "Distance: " << population[i].distance << std::endl;
    }
}

/******************** PRIVATE ********************/
std::vector<individual_t> GeneticAlgorithm::initialize_population_ (std::vector<std::vector<float>> &dist)
{
    int individual_size = dist.size();
    std::vector<individual_t> population(POPULATION_SIZE,
        {
            .distance=0,
            .fitness=0,
            .cumulative_fitness=0,
            .gens=std::vector<int>(individual_size, 0),
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

    calc_fitness_(population, dist);

    return population;
}

void GeneticAlgorithm::calc_fitness_ (std::vector<individual_t> &population, std::vector<std::vector<float>> &dist)
{
    float max_dist = 0.0;
    int individual_size = dist.size();

    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < individual_size; j++) {

            if (j == POPULATION_SIZE - 1) {
                int current = population[i].gens[j];
                int next = population[i].gens[0];
                population[i].distance += dist[current][next];
            }

            int current = population[i].gens[j];
            int next = population[i].gens[j + 1];
            population[i].distance += dist[current][next];
        }

        if (population[i].distance > max_dist) {
            max_dist = population[i].distance;
        }

    }

    std::sort(population.begin(), population.end(), compare_populations);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i].fitness = POPULATION_SIZE - i;
    }
}

std::vector<individual_t> GeneticAlgorithm::crossover_(std::vector<individual_t> fitness_population)
{
    int fitness_sum = POPULATION_SIZE * (fitness_population[0].fitness + fitness_population[POPULATION_SIZE - 1].fitness) / 2;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitness_population[i].fitness = 100 * fitness_population[i].fitness / fitness_sum;
        if (i == 0) {
            fitness_population[i].cumulative_fitness = fitness_population[i].fitness;
        }
        else {
            fitness_population[i].cumulative_fitness = fitness_population[i-1].cumulative_fitness + fitness_population[i].fitness;
        }
    }

    std::vector<parent_t> parents = select_parents_(fitness_population);

    return fitness_population;
}

static bool compare_populations(individual_t& ind1, individual_t& ind2)
{
    return ind1.distance <= ind2.distance;
}

std::vector<parent_t> GeneticAlgorithm::select_parents_(std::vector<individual_t> population)
{
    /* Configure random uniform device */
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> roulette_wheel(0, 100);
    /* Select parents for new child */
    std::vector<parent_t> parents(PARENTS_COUNT,
        {
            .is_found=false,
            .individual={
                .distance=0.0,
                .fitness=0.0,
                .cumulative_fitness=0.0,
                .gens={ 0 },
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