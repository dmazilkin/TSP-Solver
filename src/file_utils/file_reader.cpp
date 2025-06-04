#include <iostream>
#include <fstream>
#include <sstream>

#include "file_reader.h"

static const std::string SOLVER_CONFIG_PATH = "configs/";

FileReader::FileReader(void)
{
    this->line_type = "";
    this->line_data = "";
    this->solver = "";
    this->solver_cfg = std::map<std::string, int>{};
    this->data_size = 0;
}

file_read_status_t FileReader::read_cfg(std::string path, std::string &config)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "ERROR! Configuration file not found: " << path << "!" << std::endl;
        return FILE_READER_ERROR;
    }

    std::string cfg;

    while (std::getline(file, cfg, '=')) {

        if (cfg == "data") {
            std::getline(file, this->line_data);
        }

        if (cfg == "type") {
            std::getline(file, this->line_type);
        }

        if (cfg == "solver") {
            std::getline(file, this->solver);
        }
    }

    if (this->line_data == "") {
        std::cout << "ERROR! Data specifier not found in configuration file!" << std::endl;
        return FILE_READER_ERROR;
    }

    if (this->line_type == "") {
        std::cout << "ERROR! Data type specifier not found in configuration file!" << std::endl;
        return FILE_READER_ERROR;
    }

    if (this->solver == "") {
        std::cout << "ERROR! Solver specifier not found in configuration file!" << std::endl;
        return FILE_READER_ERROR;
    }

    file.close();

    return FILE_READER_SUCCESS;
}

file_read_status_t FileReader::read_content(std::string path, std::string &content)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "ERROR! Content file not found: " << path << "!" << std::endl;
        return FILE_READER_ERROR;
    }

    std::string cfg;
    std::string value;

    while (std::getline(file, cfg)) {
        if (cfg == this->line_data) {
            std::getline(file, value);
            while (value != "EOF") {
                content += value + '\n';
                data_size++;
                std::getline(file, value);
            }
        }
    }

    file.close();

    return FILE_READER_SUCCESS;
}

file_read_status_t FileReader::read_solver_cfg(void)
{
    std::string path = SOLVER_CONFIG_PATH + this->solver + ".cfg";
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "ERROR! Solver configurations file not found: " << path << "!" << std::endl;
        return FILE_READER_ERROR;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream config_line(line);
        std::string key = "";
        std::string value = "";
        std::getline(config_line, key, '=');
        std::getline(config_line, value);
        this->solver_cfg[key] = stoi(value);
    }

    file.close();

    return FILE_READER_SUCCESS;
}

std::string FileReader::get_line_data(void)
{
    return this->line_data;
}

std::string FileReader::get_line_type(void)
{
    return this->line_type;
}

std::string FileReader::get_solver(void) {
    return this->solver;
}

int FileReader::get_data_size(void) {
    return this->data_size;
}

std::map<std::string, int> FileReader::get_solver_cfg(void) {
    return this->solver_cfg;
}