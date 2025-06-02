#ifndef FILE_READER_H
#define FILE_READER_H

#include <map>

typedef enum {
    FILE_READER_SUCCESS=0,
    FILE_READER_ERROR,
} file_read_status_t;

class FileReader {
    private:
        std::string line_type;
        std::string line_data;
        std::string solver;
        std::map<std::string, int> solver_cfg;
        int data_size;
    public:
        FileReader(void);
        file_read_status_t read_cfg(std::string file_path, std::string &config);
        file_read_status_t read_solver_cfg(void);
        file_read_status_t read_content(std::string path, std::string &content);
        std::string get_line_data(void);
        std::string get_line_type(void);
        std::string get_solver(void);
        int get_data_size(void);
        std::map<std::string, int> get_solver_cfg(void);
};

#endif //FILE_READER_H
