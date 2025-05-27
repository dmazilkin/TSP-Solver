#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

typedef enum {
    CONTEXT_SOLVER_OK = 0,
    CONTEXT_SOLVER_ERROR,
} context_solver_status_t;

class TSPSolver {
    public:
        virtual void solve(void);
};

class TSPContext {
    private:
        TSPSolver& context_solver;
        context_solver_status_t status;
        TSPSolver& get_context_solver(std::string solver);
        bool check_solver(std::string solver);
    public:
        TSPContext(std::string solver);
        void set_context_solver(std::string solver);
        void solve(void);
};

#endif //TSP_SOLVER_H
