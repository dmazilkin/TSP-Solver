#include <iostream>
#include <fstream>

#include "file_reader.h"

FileReader::FileReader(void) {
    line_type = "";
    line_data = "";
}

file_read_status_t FileReader::read_cfg(std::string path, std::string &config) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "ERROR! Configuration file not found: " << path << "!" << std::endl;
        return FILE_READER_ERROR;
    }

    std::string cfg;
    while (std::getline(file, cfg, '=')) {

        if (cfg == "data") {
            std::getline(file, line_data);
        }

        if (cfg == "type") {
            std::getline(file, line_type);
        }

        if (cfg == "size") {
            std::getline(file, line_size);
        }
    }

    file.close();

    return FILE_READER_SUCCESS;
}

file_read_status_t FileReader::read_content(std::string path, std::string &content) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "ERROR! Content file not found: " << path << "!" << std::endl;
        return FILE_READER_ERROR;
    }

    file.close();

    return FILE_READER_SUCCESS;
}

std::string FileReader::get_line_data(void) {
    return line_data;
}

std::string FileReader::get_line_type(void) {
    return line_type;
}

std::string FileReader::get_line_size(void) {
    return line_size;
}