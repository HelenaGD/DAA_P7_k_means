#pragma once
#include "../include/solution.h"
#include <limits>

template <typename T>
class Algorithm {
 public:
    Algorithm() {};
    ~Algorithm() {};
    virtual Solution<T> run(Problem<T> problem) = 0;
    void reset_movements() {
        for (int i = 0; i < movements_.size(); i++) {
            movements_[i] = false;
        }
    };
 protected:
  vector<bool> movements_;
};