#include <iostream>

#include "arg_parser.h"

ArgParser::ArgParser(void) {
    input = "";
    output = "";
}

arg_parser_statur_t ArgParser::parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'i') {
                input = argv[i+1];
            }
            else if (argv[i][1] == 'o') {
                output = argv[i+1];
            }
            else if (argv[i][1] == '-') {
                if (argv[i][2] == 'i') {
                    input = argv[i+1];
                }
                else if (argv[i][2] == 'o') {
                    output = argv[i+1];
                }
            }
        }
    }

    if (!input.compare("")) {
        std::cout << "ERROR! Input file was not specified!" << std::endl;
        return ARG_PARSER_ERROR;
    }

    if (!output.compare("")) {
      std::cout << "ERROR! Output file was not specified!" << std::endl;
      return ARG_PARSER_ERROR;
    }

    return ARG_PARSER_SUCCESS;
}

std::string ArgParser::get_input(void) {
  return input;
}

std::string ArgParser::get_output(void) {
  return output;
}

