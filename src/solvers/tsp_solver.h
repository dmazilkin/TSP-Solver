#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <memory>
#include <map>

typedef enum {
    SOLVER_CONFIGS_OK = 0,
    SOLVER_CONFIGS_ERROR,
} configs_status_t;

typedef enum {
    CONTEXT_SOLVER_DEFINED = 0,
    CONTEXT_SOLVER_UNDEFINED,
} context_solver_status_t;

typedef enum {
    SOLVER_AVAILABLE = 0,
    SOLVER_UNAVAILABLE,
} solver_name_status_t;

class TSPSolver {
    public:
        virtual ~TSPSolver() = default;
        virtual void solve(std::vector<std::vector<float>> &dist) = 0;
        virtual configs_status_t configure_solver(std::map<std::string, int> solver_configs) = 0;
};

class TSPContext {
    private:
        std::unique_ptr<TSPSolver> context_solver;
        context_solver_status_t context_status;
        configs_status_t configs_status;
        TSPSolver get_context_solver_(std::string solver_name);
        void set_context_solver_(std::string solver_name);
        solver_name_status_t check_solver_name_(std::string solver_name);
    public:
        TSPContext(void);
        TSPContext(std::string solver_name);
        void set_context_solver(std::string solver_name);
        context_solver_status_t get_context_solver_status(void);
        void set_solver_configs(std::map<std::string, int> solver_configs);
        configs_status_t get_configs_status(void);
        void solve(std::vector<std::vector<float>> &dist);
};

#endif //TSP_SOLVER_H
