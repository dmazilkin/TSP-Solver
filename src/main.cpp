#include <iostream>

#include "file_reader.h"
#include "arg_parser.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    /* Parse arguments */
    ArgParser parser;
    arg_parser_status_t arg_status = parser.parse(argc, argv);

    if (arg_status != ARG_PARSER_SUCCESS) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    /* Get file content */
    std::string content;
    FileReader reader;
    file_read_status_t reader_status = reader.read(parser.get_input(), content);

    if (reader_status != FILE_READER_SUCCESS) {
        std::cout << "ERROR! Exiting with error code..." << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}