#pragma once
#include "../include/solution.h"
#include <limits>

template <typename T>
class Algorithm {
 public:
    Algorithm() {};
    ~Algorithm() {};
    virtual Solution<T> run(Problem<T> problem) = 0;
};