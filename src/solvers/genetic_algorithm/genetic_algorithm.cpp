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

//    for (int i = 0; i < POPULATION_SIZE; i++) {
//        for (int j = 0; j < fitness_population[i].gens.size(); j++) {
//            std::cout << fitness_population[i].gens[j] << " ";
//        }
//        std::cout << std::endl;
//        std::cout << "Fitness: " << fitness_population[i].fitness << std::endl;
//        std::cout << "Distance: " << fitness_population[i].distance << std::endl;
//    }
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
    float max_dist = 0.0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitness_population[i].gens = population[i];

        for (int j = 0; j < population[0].size(); j++) {

            if (j == POPULATION_SIZE - 1) {
                int current = population[i][j];
                int next = population[i][0];
                fitness_population[i].distance += dist[current][next];
            }

            int current = population[i][j];
            int next = population[i][j + 1];
            fitness_population[i].distance += dist[current][next];
        }

        if (fitness_population[i].distance > max_dist) {
            max_dist = fitness_population[i].distance;
        }

    }

    std::sort(fitness_population.begin(), fitness_population.end(), compare_populations);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        fitness_population[i].fitness = POPULATION_SIZE - i;
    }

    return fitness_population;
}

std::vector<individual_t> GeneticAlgorithm::crossover(std::vector<individual_t> fitness_population)
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

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> roulette_wheel(0, 100);
    float first_cumulative = roulette_wheel(g);
    float second_cumulative = roulette_wheel(g);
    individual_t first_parent;
    individual_t second_parent;
    bool first_found = false;
    bool second_found = false;
    int first_ind = 0;
    int second_ind = 0;

    while (!first_found and (first_ind < POPULATION_SIZE)) {
        if (fitness_population[first_ind].cumulative_fitness > first_cumulative) {
            first_parent = fitness_population[first_ind];
            first_found = true;
        }
        else {
            first_ind++;
        }
    }

    while (!second_found and (second_ind < POPULATION_SIZE)) {
        if (fitness_population[second_ind].cumulative_fitness > second_cumulative) {
            second_parent = fitness_population[second_ind];
            second_found = true;
        }
        else {
            second_ind++;
        }
    }

    std::cout << first_cumulative << std::endl;
    std::cout << first_ind << std::endl;
    std::cout << first_parent.distance << " " << first_parent.fitness << " " << first_parent.cumulative_fitness << std::endl;

    std::cout << second_cumulative << std::endl;
    std::cout << second_ind << std::endl;
    std::cout << second_parent.distance << " " << second_parent.fitness << " " << second_parent.cumulative_fitness << std::endl;


    return fitness_population;
}

static bool compare_populations(individual_t& ind1, individual_t& ind2)
{
    return ind1.distance <= ind2.distance;
}