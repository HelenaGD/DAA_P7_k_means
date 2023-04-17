#pragma once
#include "../include/solution.h"
#include <limits>

#define RESET "\033[0m"
#define RED "\033[31m"
#define CYAN "\033[36m"

template <typename T>
class Algorithm {
 public:
    Algorithm() {};
    ~Algorithm() {};
    virtual Solution<T> run(Problem<T> problem) = 0;
};