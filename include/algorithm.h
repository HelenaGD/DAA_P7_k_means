#include "../include/solution.h"

template <typename T>
class Algorithm {
 public:
    Algorithm();
    ~Algorithm();
    virtual Solution run(Problem problem) = 0;
};