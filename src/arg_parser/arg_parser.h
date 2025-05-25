#ifndef ARG_PARSER_H
#define ARG_PARSER_H

typedef enum {
    ARG_PARSER_SUCCESS = 0,
    ARG_PARSER_ERROR = -1,
} arg_parser_status_t;

class ArgParser {
    public:
      ArgParser(void);
      arg_parser_status_t parse(int argc, char* argv[]);
      std::string get_input(void);
      std::string get_output(void);
    private:
      std::string input;
      std::string output;
};

#endif //ARG_PARSER_H
