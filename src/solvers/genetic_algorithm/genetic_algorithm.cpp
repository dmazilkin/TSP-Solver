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
#define BEST_COUNT 5

/******************** STATIC FUNCTIONS DECLARATION ********************/
static bool compare_populations(individual_t& ind1, individual_t& ind2);

/******************** PUBLIC ********************/
void GeneticAlgorithm::solve(std::vector<std::vector<float>> &dist)
{
    /* Initialize population */
    std::vector<individual_t> population = initialize_population_(dist);
    calc_fitness_(population, dist);
    /* Generate new population */
    std::vector<individual_t> new_generation = crossover_(population);
//    calc_fitness_(new_generation, dist);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < new_generation[i].gens.size(); j++) {
            std::cout << new_generation[i].gens[j] << " ";
        }
        std::cout << std::endl;
        std::cout << "Fitness: " << new_generation[i].fitness << std::endl;
        std::cout << "Distance: " << new_generation[i].distance << std::endl;
        std::cout << "Percentage: " << new_generation[i].cumulative_fitness << std::endl;
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


    return population;
}

void GeneticAlgorithm::calc_fitness_(std::vector<individual_t> &population, std::vector<std::vector<float>> &dist)
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
            .gens=std::vector<int>(individual_size, 0),
        }
    );

    /* Save first best individuals without changes */
    for (int i = 0; i < BEST_COUNT; i++) {
        new_generation[i].distance = population[i].distance;
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

static bool compare_populations(individual_t& ind1, individual_t& ind2)
{
    return ind1.distance <= ind2.distance;
}

std::vector<parent_t> GeneticAlgorithm::select_parents_(std::vector<individual_t> &population)
{
    /* Configure random uniform device */
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> roulette_wheel(ROULUTTE_WHEEL_MIN, ROULUTTE_WHEEL_MAX);
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

std::vector<int> GeneticAlgorithm::generate_child_(std::vector<parent_t> &parents)
{
    int individual_size = parents[0].individual.gens.size();
    std::vector<int> child(individual_size, 0);

    /* Generate gens range to inherite from first parent */
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> range_boundary(0, individual_size);
    int first_parent_start = range_boundary(g);
    int first_parent_stop = range_boundary(g);

    if (first_parent_start > first_parent_stop) {
        int temp = first_parent_start;
        first_parent_start = first_parent_stop;
        first_parent_stop = temp;
    }

    /* Inherite gens from first parent */
    for (int i = first_parent_start; i < first_parent_stop; i++) {
        child[i] = parents[0].individual.gens[i];
    }

    /* Inherite gens from second parent */
    int new_gen_ind = 0;
    int parent_gen_ind = 0;

    while (new_gen_ind < first_parent_stop) {
        if (!((new_gen_ind >= first_parent_start) and (new_gen_ind < first_parent_stop))) {
            int gen = parents[1].individual.gens[parent_gen_ind];

            while (has_gen_(child, gen, first_parent_start, first_parent_stop)) {
                parent_gen_ind++;
            }

            child[new_gen_ind] = gen;
            parent_gen_ind++;
        }

        new_gen_ind++;
    }

    return child;
}

bool GeneticAlgorithm::has_gen_(std::vector<int> &gens, int gen, int start, int stop)
{
    bool found = false;
    int ind = start;

    while ((ind < stop) or found) {
        found = gen == gens[ind];
        ind++;
    }

    return found;
}