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

TEST(Problem, centroid) {
  vector<vector<double>> cluster = {{1, 2, 3}, {3, 4, 5}};
  Problem<double> problem(3, 2, cluster);
  EXPECT_EQ(problem.centroid(cluster), vector<double>({2, 3, 4}));

  vector<vector<int>> cluster2 = {{1, 2, 3, 4}, {4, 5, 6, 7}};
  Problem<int> problem2(3, 2, cluster2);
  EXPECT_EQ(problem2.centroid(cluster2), vector<int>({2, 3, 4, 5}));

  vector<vector<int>> cluster3 = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};
  Problem<int> problem3(3, 2, cluster3);
  EXPECT_EQ(problem3.centroid(cluster3), vector<int>({4, 5, 6, 7}));
}

// Ejecutamos los casos de prueba
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}