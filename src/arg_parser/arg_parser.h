#ifndef ARG_PARSER_H
#define ARG_PARSER_H

typedef enum {
    ARG_PARSER_SUCCESS = 0,
    ARG_PARSER_ERROR = -1,
} arg_parser_status_t;

class ArgParser {
    private:
        std::string input;
        std::string output;
        std::string cfg;
    public:
      ArgParser(void);
      arg_parser_status_t parse(int argc, char* argv[]);
      std::string get_input(void);
      std::string get_output(void);
      std::string get_cfg(void);
};

#endif //ARG_PARSER_H
