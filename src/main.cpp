#include <iostream>

#include "file_reader.h"
#include "arg_parser.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    /* Parse arguments */
    ArgParser parser;
    parser.parse(argc, argv);
    std::cout << "Input: " << parser.get_input() << std::endl;
    std::cout << "Output: " << parser.get_output() << std::endl;

    /* Get file content */
    std::string content;
    FileReader reader;
    reader.read("input/berlin52.tsp", content);

    return 0;
}