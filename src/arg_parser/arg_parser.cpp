#include <iostream>

#include "arg_parser.h"

ArgParser::ArgParser(void) {
    input = "";
    output = "";
}

arg_parser_status_t ArgParser::parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'i') {
                input = argv[i+1];
            }
            else if (argv[i][1] == 'o') {
                output = argv[i+1];
            }
            else if (argv[i][1] == 'c') {
                cfg = argv[i+1];
            }
            else if (argv[i][1] == '-') {
                if (argv[i][2] == 'i') {
                    input = argv[i+1];
                }
                else if (argv[i][2] == 'o') {
                    output = argv[i+1];
                }
                else if (argv[i][2] == 'c') {
                    cfg = argv[i+1];
                }
                else {
                    std::cout << "ERROR! Unknown option: " << argv[i] << '.' << std::endl;
                    return ARG_PARSER_ERROR;
                }
            }
            else {
                std::cout << "ERROR! Unknown option: " << argv[i] << '.' << std::endl;
                return ARG_PARSER_ERROR;
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

    if (!cfg.compare("")) {
        std::cout << "ERROR! Configuration file was not specified!" << std::endl;
        return ARG_PARSER_ERROR;
    }

    return ARG_PARSER_SUCCESS;
}

std::string ArgParser::get_input(void) {
  return input;
}

std::string ArgParser::get_cfg(void) {
    return cfg;
}

std::string ArgParser::get_output(void) {
  return output;
}

