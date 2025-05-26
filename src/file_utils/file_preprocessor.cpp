#include <iostream>
#include <sstream>
#include <vector>

#include "file_preprocessor.h"

void FilePreprocessor::create_dist_matrix(std::string content, int size, std::vector<std::vector<int>> &dist) {
    std::vector<std::vector<int>> coords(size, std::vector<int>(2, 0));
    get_coords(content, size, coords);


}

void FilePreprocessor::get_coords(std::string content, int size, std::vector<std::vector<int>> &coords) {
    std::stringstream content_stream(content);
    std::string line;
    int row = 0;

    while (row < size) {
        std::getline(content_stream, line);
        std::stringstream line_stream(line);
        std::string column;

        for (int i = 0; i < 3; i++) {
            getline(line_stream, column, ' ');

            if (i > 0) {
                coords[row][i-1] = std::stof(column);
            }
        }

        row++;
    }
}