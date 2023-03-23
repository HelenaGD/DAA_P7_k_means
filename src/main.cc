#include "../include/problem.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  string path = argv[1]; // archivo de entrada
  Problem<double> problem(path);
  //problem.print();
}