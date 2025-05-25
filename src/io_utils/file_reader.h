#ifndef FILE_READER_H
#define FILE_READER_H

typedef enum {
    FILE_READ_SUCCESS=0,
    FILE_READ_ERROR,
} file_read_status_t;

class FileReader {
    public:
        file_read_status_t read(std::string path, std::string &content);
};

#endif //FILE_READER_H
