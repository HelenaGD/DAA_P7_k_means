#include <gtest/gtest.h>
#include "../include/problem.h"

TEST(Problem, Constructor) {
  Problem<double> problem(3, 2, {{1, 2}, {3, 4}, {5, 6}});
  EXPECT_EQ(problem.get_m(), 3);
  EXPECT_EQ(problem.get_k(), 2);
  vector<vector<double>> result = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(problem.get_points(), result);
}

TEST(Problem, euclidean_distance) {
  Problem<double> problem(3, 2, {{1, 2}, {3, 4}, {5, 6}});
  EXPECT_EQ(problem.euclidean_distance({1, 2}, {3, 4}), 2.8284271247461903);
  Problem<int> problem2(3, 2, {{1, 2, 3}, {4, 5, 6}});
  EXPECT_EQ(problem2.euclidean_distance({1, 2, 3}, {4, 5, 6}), 5.196152422706632);
}

// Ejecutamos los casos de prueba
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}