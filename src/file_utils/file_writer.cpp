#include <iostream>
#include <fstream>

#include "file_writer.h"

file_write_status_t FileWriter::write_solution(solution_t &solution, std::string file_name)
{
    std::ofstream file(file_name);
    
    if (!file.is_open()) {
        std::cout << "ERROR! Cannot create output file.";
        return FILE_WRITER_ERROR;
    }

    file << "Gens:\n";
    
    for (int i = 0; i < solution.gens.size(); i++) {
        file << solution.gens[i];
        file << ' ';
    }
    file << '\n';

    file << "Distance:\n";
    file << solution.distance;

    return FILE_WRITER_SUCCESS;
}