#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <vector>

#include "tsp_solver.h"

typedef enum {
    FILE_WRITER_SUCCESS=0,
    FILE_WRITER_ERROR,
} file_write_status_t;

class FileWriter {
    private:
        solution_t solution;
    public:
        file_write_status_t write_solution(solution_t &solution, std::string file_name);
};

#endif //FILE_WRITER_H