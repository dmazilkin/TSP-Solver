#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "genetic_algorithm.h"
#include "tsp_solver.h"

/******************** DEFINES ********************/
#define POPULATION_SIZE 100

/******************** STATIC FUNCTIONS DECLARATION ********************/
static bool compare_populations(individual_t& ind1, individual_t& ind2);

/******************** PUBLIC ********************/
void GeneticAlgorithm::solve(std::vector<std::vector<float>> dist)
{
    std::vector<std::vector<int>> population = initialize_population_(POPULATION_SIZE, dist.size());
    std::vector<individual_t> fitness_population = calc_fitness_(population, dist);
    std::vector<individual_t> new_generation = crossover(fitness_population);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < new_generation[0].gens.size(); j++) {
            std::cout << new_generation[0].gens[j] << " ";
        }
        std::cout << std::endl;
        std::cout << "Fitness: " << new_generation[i].fitness << std::endl;
    }
}

/******************** PRIVATE ********************/
std::vector<std::vector<int>> GeneticAlgorithm::initialize_population_ (int population_size, int individual_size)
{
    std::vector<std::vector<int>> population(population_size, std::vector<int>(individual_size, 0));

    for (int i = 0; i < population_size; i++) {

        for (int j = 0; j < individual_size; j++) {
            population[i][j] = j;
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(population[i].begin(), population[i].end(), g);
    }

    return population;
}

std::vector<individual_t> GeneticAlgorithm::calc_fitness_ (std::vector<std::vector<int>> population, std::vector<std::vector<float>> dist)
{
    std::vector<individual_t> fitness_population(POPULATION_SIZE);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitness_population[i].gens = population[i];
        for (int j = 0; j < population[0].size(); j++) {

            if (j == POPULATION_SIZE - 1) {
                int current = population[i][j];
                int next = population[i][0];
                fitness_population[i].fitness += dist[current][next];
            }

            int current = population[i][j];
            int next = population[i][j + 1];
            fitness_population[i].fitness += dist[current][next];
        }
    }

    return fitness_population;
}

std::vector<individual_t> GeneticAlgorithm::crossover (std::vector<individual_t> fitness_population)
{
    std::sort(fitness_population.begin(), fitness_population.end(), compare_populations);

    return fitness_population;
}

static bool compare_populations(individual_t& ind1, individual_t& ind2)
{
    return ind1.fitness <= ind2.fitness;
}