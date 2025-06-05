#include <iostream>
#include <vector>
#include <map>

#include "file_reader.h"
#include "arg_parser.h"
#include "file_preprocessor.h"
#include "tsp_solver.h"
#include "file_writer.h"

int main(int argc, char* argv[]) {
    std::cout << "TSP Solver started." << std::endl;

    /* Parse arguments */
    ArgParser parser;
    arg_parser_status_t arg_status = parser.parse(argc, argv);

    if (arg_status != ARG_PARSER_SUCCESS) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    /* Read common configs and specific solver configs */
    std::string content;
    FileReader reader;
    file_read_status_t cfg_status = reader.read_cfg(parser.get_cfg(), content);

    if (cfg_status != FILE_READER_SUCCESS) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    file_read_status_t solver_cfg_status = reader.read_solver_cfg();

    if (solver_cfg_status != FILE_READER_SUCCESS) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    /* Read content */
    file_read_status_t content_status = reader.read_content(parser.get_input(), content);

    if (content_status != FILE_READER_SUCCESS) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    /* Process file content */
    int matrix_size = reader.get_data_size();
    std::vector<std::vector<float>> dist(matrix_size, std::vector<float>(matrix_size, 0.0));
    FilePreprocessor file_preprocessor;
    file_preprocessor.create_dist_matrix(content, matrix_size, dist);

    /* Initialize provided solver and start it */
    TSPContext tsp_context;
    tsp_context.set_context_solver(reader.get_solver());

    if (tsp_context.get_context_solver_status() != CONTEXT_SOLVER_DEFINED) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    tsp_context.set_solver_configs(reader.get_solver_cfg());

    if (tsp_context.get_configs_status() != SOLVER_CONFIGS_OK) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    solution_t found_solution = tsp_context.solve(dist);

    /* Save solution */
    FileWriter writer;
    file_write_status_t writer_status = writer.write_solution(found_solution, parser.get_output());

    if (writer_status != FILE_WRITER_SUCCESS) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Solution found! Exiting TSP Solver..." << std::endl;

    return EXIT_SUCCESS;
}