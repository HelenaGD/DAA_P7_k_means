#include <gtest/gtest.h>
#include "../include/problem.h"

TEST(Problem, Constructor) {
  Problem<double> problem(3, 2, {{1, 2}, {3, 4}, {5, 6}});
  EXPECT_EQ(problem.get_m(), 3);
  EXPECT_EQ(problem.get_k(), 2);
  vector<vector<double>> result = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(problem.get_points(), result);
}

// Ejecutamos los casos de prueba
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}