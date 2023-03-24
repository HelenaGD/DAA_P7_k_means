#include <gtest/gtest.h>
#include "../include/formulas.h"
#include "../include/problem.h"
#include "../include/solution.h"

extern double euclidean_distance();
extern vector<double> centroid();

TEST(Problem, Constructor) {
  Problem<double> problem(3, 2, {{1, 2}, {3, 4}, {5, 6}});
  EXPECT_EQ(problem.get_m(), 3);
  EXPECT_EQ(problem.get_n(), 2);
  vector<vector<double>> result = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(problem.get_points(), result);
}

TEST(Formulas, euclidean_distance) {
  double resultado = euclidean_distance(vector<double>{1, 2}, vector<double>{3, 4});
  EXPECT_EQ(resultado, 2.8284271247461903);
  double resultado_2 = euclidean_distance(vector<double>{1, 2, 3}, vector<double>{4, 5, 6});
  EXPECT_EQ(resultado_2, 5.196152422706632);
}

TEST(Formulas, centroid) {
  vector<vector<double>> cluster = {{1, 2, 3}, {3, 4, 5}};
  EXPECT_EQ(centroid(cluster), vector<double>({2, 3, 4}));

  vector<vector<int>> cluster2 = {{1, 2, 3, 4}, {4, 5, 6, 7}};
  EXPECT_EQ(centroid(cluster2), vector<int>({2, 3, 4, 5}));

  vector<vector<int>> cluster3 = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};
  EXPECT_EQ(centroid(cluster3), vector<int>({4, 5, 6, 7}));
}

TEST(Formulas, Constructor) {
  vector<vector<double>> cluster = {{1, 2, 3}, {3, 4, 5}};
  vector<vector<vector<double>>> clusters = {cluster, cluster};
  Problem<double> problem(3, 2, cluster);
  Solution<double> solution(clusters);
  EXPECT_EQ(solution.get_clusters(), clusters);
}

TEST(Solution, evaluate) {
  vector<vector<double>> cluster2 = {{1, 2, 3, 4}, {4, 5, 6, 7}}; // Centroide {2, 3, 4, 5}
  vector<vector<double>> cluster3 = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}}; // Centroide {4, 5, 6, 7}
  vector<vector<vector<double>>> clusters = {cluster2, cluster3};
  vector<vector<double>> puntos = {{1, 2, 3, 4}, {4, 5, 6, 7}, {1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}};

  Solution<double> solution(clusters); // Solucion compuesta por vector de clusters
  solution.evaluate();
  EXPECT_EQ(solution.get_sse(), 90);
}

// Ejecutamos los casos de prueba
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}