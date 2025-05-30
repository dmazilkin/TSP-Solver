#ifndef FILE_PREPROCESSOR_H
#define FILE_PREPROCESSOR_H

class FilePreprocessor {
    private:
        void get_coords(std::string content, int size, std::vector<std::vector<float>> &coords);
    public:
        void create_dist_matrix(std::string content, int size, std::vector<std::vector<float>> &dist);
};

#endif //FILE_PREPROCESSOR_H
