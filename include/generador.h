#include "iteracion.h"
#include "problem.h"
#include "algorithm.h"
#include "voraz.h"
#include "grasp.h"

#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class GENERATOR {
 private:
 public:
  GENERATOR() {};
  ~GENERATOR() {};
  
  void generate(string name, string csv_file, Problem<double> problem, int type, int num_executions = 10) {
    // Obtener el tiempo actual
    time_t seed = time(NULL);

    vector<Iteracion> iteraciones;
    unsigned t0, t1;

    for (int i = 0; i < num_executions; i++) {
      Algorithm<double>* algorithm;
      // Cambiar la semilla aleatoria
      srand(seed + i);

      if (type == 1) algorithm = new Kmeans<double>();
      else if (type == 2) algorithm = new GRASP<double>();
      t0 = clock();
      Solution<double> solution = algorithm->run(problem);
      solution.evaluate();
      t1 = clock();
      double time = (double(t1-t0)/CLOCKS_PER_SEC);
      Iteracion iteracion;
      iteracion.Identificador_ = name;
      iteracion.m_ = problem.get_m();
      iteracion.k_ = solution.get_num_clusters();
      iteracion.ejecuciones_ = i + 1;
      iteracion.sse_ = solution.get_sse();
      iteracion.tiempo_ = time;
      iteraciones.push_back(iteracion);
      sleep(1);
    }
    guardar_csv(csv_file, iteraciones);
  }

  void guardar_csv(string nombre_archivo, vector<Iteracion> iteraciones) {
    ofstream archivo("solutions/" + nombre_archivo);
    
    // Escribir encabezado
    archivo << "Problema,m,K,Ejecución,SSE,CPU" << endl;
    
    // Escribir cada fila
    for (auto iteracion : iteraciones) {
      archivo << iteracion.Identificador_ << ","
              << iteracion.m_ << ","
              << iteracion.k_ << ","
              << iteracion.ejecuciones_ << ","
              << iteracion.sse_ << ","
              << iteracion.tiempo_ << endl;
    }
    
    archivo.close();
  }

};