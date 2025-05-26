#include <iostream>
#include <sstream>
#include <vector>

#include "file_preprocessor.h"

void FilePreprocessor::create_dist_matrix(std::string content, int size, std::vector<std::vector<float>> &dist) {
    std::vector<std::vector<float>> coords(size, std::vector<float>(2, 0.0));
    get_coords(content, size, coords);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            float x = coords[i][0] - coords[j][0];
            float y = coords[i][1] - coords[j][1];
            dist[i][j] = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
        }
    }
}

void FilePreprocessor::get_coords(std::string content, int size, std::vector<std::vector<float>> &coords) {
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