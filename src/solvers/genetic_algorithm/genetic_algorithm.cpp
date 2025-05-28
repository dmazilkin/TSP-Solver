#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "genetic_algorithm.h"
#include "tsp_solver.h"

#define POPULATION_SIZE 100

/******************** PUBLIC ********************/
void GeneticAlgorithm::solve(std::vector<std::vector<float>> dist)
{
    std::vector<std::vector<int>> population = initialize_population_(POPULATION_SIZE, dist.size());
    std::vector<float> population_fitness = calc_fitness_(population, dist);
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

std::vector<float> GeneticAlgorithm::calc_fitness_ (std::vector<std::vector<int>> population, std::vector<std::vector<float>> dist)
{
    std::vector<float> fitness (POPULATION_SIZE, 0);

    for (int i = 0; i < POPULATION_SIZE; i++) {

        for (int j = 0; j < population[0].size(); j++) {

            if (j == POPULATION_SIZE - 1) {
                int current = population[i][j];
                int next = population[i][0];
                fitness[i] += dist[current][next];
            }

            int current = population[i][j];
            int next = population[i][j + 1];
            fitness[i] += dist[current][next];
        }
    }

    std::sort(fitness.begin(), fitness.end());

    return fitness;
}