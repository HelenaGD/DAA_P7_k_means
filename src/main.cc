#include "../include/problem.h"
#include "../include/formulas.h"
#include "../include/solution.h"
#include "../include/algorithm.h"
#include "../include/voraz.h"
#include "../include/grasp.h"
#include "../include/generador.h"

#include <filesystem>

using namespace std;

namespace fs = std::filesystem;

void execute(string file, Algorithm<double>* algorithm, Problem<double> problem) {
  unsigned t0, t1;
  t0 = clock();
  Solution<double> solution = algorithm->run(problem);
  solution.evaluate();
  t1 = clock();
  double time = (double(t1-t0)/CLOCKS_PER_SEC);
  cout << "SSE: " << solution.get_sse() << endl;
  cout << "CPU Time: " << time << " seconds" << endl << endl;
  /*cout << "Clusters: " << solution.get_num_clusters() << endl;
  cout << "Centroids: " << endl;
  solution.print_centroids();*/
  solution.store_solution(file);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  string path = argv[1]; // archivo de entrada
  Problem<double> problem(path);
  //problem.print();
  fs::path file_path(path);
  string file_name = file_path.filename().string();
  // Encontrar la posición del último punto
  size_t pos = file_name.find_last_of('.');
  string new_file_name = file_name;

  // Si se encontró el punto, eliminar la extensión
  if (pos != std::string::npos) {
    new_file_name = new_file_name.substr(0, pos);
  }

  GENERATOR generator;
  generator.generate(file_name, new_file_name + "_kmeans.csv", problem, 1);
  generator.generate(file_name, new_file_name + "_grasp.csv", problem, 2);

  // Para hacer una sola ejecución y obtener el archivo con los grupos
  /*Algorithm<double>* algorithm = new Kmeans<double>();
  execute("kmeans", algorithm, problem);

  algorithm = new GRASP<double>();
  execute("grasp", algorithm, problem);*/
}