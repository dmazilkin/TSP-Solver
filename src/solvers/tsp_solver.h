#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <memory>

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
        virtual void solve(void) = 0;
        virtual ~TSPSolver() = default;
};

class TSPContext {
    private:
        std::unique_ptr<TSPSolver> context_solver;
        context_solver_status_t context_status;
        TSPSolver get_context_solver_(std::string solver_name);
        void set_context_solver_(std::string solver_name);
        solver_name_status_t check_solver_name_(std::string solver_name);
    public:
        TSPContext(void);
        TSPContext(std::string solver_name);
        void set_context_solver(std::string solver_name);
        void solve(void);
};

#endif //TSP_SOLVER_H
