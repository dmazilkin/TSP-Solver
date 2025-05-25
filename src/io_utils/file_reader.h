#ifndef FILE_READER_H
#define FILE_READER_H

typedef enum {
    FILE_READER_SUCCESS=0,
    FILE_READER_ERROR,
} file_read_status_t;

class FileReader {
    private:
        std::string line_type;
        std::string line_data;
    public:
        FileReader(void);
        file_read_status_t read_cfg(std::string file_path, std::string &config);
        file_read_status_t read_content(std::string path, std::string &content);
        std::string get_line_data(void);
        std::string get_line_type(void);
};

#endif //FILE_READER_H
