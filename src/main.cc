#include "../include/problem.h"
#include "../include/formulas.h"
#include "../include/solution.h"
#include "../include/algorithm.h"
#include "../include/voraz.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  string path = argv[1]; // archivo de entrada
  Problem<double> problem(path);
  //problem.print();
  Algorithm<double>* algorithm = new Kmeans<double>();

  Solution<double> solution = algorithm->run(problem);
  solution.evaluate();
  cout << "SSE: " << solution.get_sse() << endl;
  cout << "Clusters: " << solution.get_num_clusters() << endl;
  cout << "Centroids: " << endl;
  solution.print_centroids();
  solution.store_solution();
}