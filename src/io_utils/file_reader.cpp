#include <iostream>
#include <fstream>

#include "file_reader.h"

file_read_status_t FileReader::read(std::string path, std::string &content) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "ERROR! File not found: " << path << "!" << std::endl;
        return FILE_READER_ERROR;
    }

    return FILE_READER_SUCCESS;
}