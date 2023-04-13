#pragma once

#include "../include/algorithm.h"
#include <random>
#include <ctime>
#include <algorithm>

template <typename T>
class GRASP : public Algorithm<T> { // Greedy Randomized Adaptive Search Procedure
 public:
  typedef vector<vector<T>> Cluster;
  typedef std::pair<int, T> farthestElement;
  GRASP() : Algorithm<T>() {};
  ~GRASP() {};
  Solution<T> run(Problem<T> problem) {
    // Fase constructiva
    //cout << "Inicia fase constructiva" << endl;
    Cluster initial_solution = constructive_fase(problem);
    //cout << "Finaliza fase constructiva. Tamaño de la solo ini: " << initial_solution.size() << endl << endl;

    // Fase de procesamiento
    vector<Cluster> grupos = procesamiento(problem, initial_solution);

    // Evaluar la solución
    // Evaluado al completo
    Solution<T> solution(grupos, initial_solution);
    solution.evaluate();
    double new_sse = std::numeric_limits<double>::infinity();
    double best_sse = solution.get_sse();

    // BÚSQUEDA LOCAL
    //cout << endl << "Inicia búsqueda local" << endl;
    Solution<T> optimo_local = local_search(problem, solution);
    //cout << "Finaliza búsqueda local" << endl << endl;
    
    // Retorno la solución
    return optimo_local;
  }

  Solution<T> local_search(const Problem<T>& problem, const Solution<T>& initial_solution) {
    double best_sse = initial_solution.get_sse(); // La mejor solucion hasta el momento
    
    Solution<T> best_solution;
    Cluster best_serv_points = initial_solution.get_service_points();

    // Ahora, debo buscar la mejor solución vecina, y si cambia
    // con respecto a la mejor solución hasta el momento, busco
    // en ese vecindario

    //int iterador = 0;
    Solution<T> current_best_solution = initial_solution;
    while (true) {
      //iterador++;
      //cout << "Interacion " << iterador << endl;
      // Encuentro la mejor de las soluciones del entorno
      best_solution = best_vecino(problem, best_serv_points);
      best_serv_points = best_solution.get_service_points();

      // Procesamiento
      vector<Cluster> grupos = procesamiento(problem, best_serv_points);

      // Evaluación
      Solution<T> new_solution(grupos, best_serv_points);
      new_solution.evaluate();
      double new_sse = new_solution.get_sse();

      /*cout << "Evaluación hecha" << endl;
      cout << "SSE actual: " << new_sse << endl;
      cout << "SSE mejor: " << best_sse << endl;*/

      if (new_sse < best_sse) {
        //cout << "El vecino es mejor que el actual" << endl;
        best_sse = new_sse;
        current_best_solution = new_solution; // Actualizo la mejor solución actual
      } else {
        break;
      }
    }

    return current_best_solution;
  }

  Solution<T> best_vecino(const Problem<T>& problem, const Cluster& initial_solution) {
    Solution<T> the_solution;
    // De todas las soluciones vecinas, encuentro la mejor
    // Genero espacio de soluciones vecinas
    vector<Cluster> vecinos = intercambio(problem, initial_solution);
    //cout << "Genero espacio de soluciones vecinas" << endl;
    /*for (int i = 0; i < vecinos.size(); i++) {
      cout << "Solución " << i << endl;
      for (int j = 0; j < vecinos[i].size(); j++) {
        cout << "Cluster " << j << endl;
        for (int k = 0; k < vecinos[i][j].size(); k++) {
          cout << vecinos[i][j][k] << " ";
        }
        cout << endl;
      }
      cout << endl;
    }*/
    // Encuentro la mejor solución vecina
    double best_sse = std::numeric_limits<T>::max();
    Cluster best_solution;
    for (int i = 0; i < vecinos.size(); i++) {
      // Procesamiento
      vector<Cluster> grupos = procesamiento(problem, vecinos[i]);
      // Evaluación (Total. Intentar parcial)
      Solution<T> new_solution(grupos, vecinos[i]);
      new_solution.evaluate();
      double new_sse = new_solution.get_sse();
      if (new_sse < best_sse) {
        best_solution = vecinos[i];
        best_sse = new_sse;
        the_solution = new_solution;
      }
    }
    //cout << "Mejor solución encontrada en el vecindario: " << best_sse << endl;
    /*for (int i = 0; i < best_solution.size(); i++) {
      cout << "Cluster " << i << endl;
      for (int j = 0; j < best_solution[i].size(); j++) {
        cout << best_solution[i][j] << " ";
      }
      cout << endl;
    }*/

    return the_solution;
  }

  vector<Cluster> procesamiento(const Problem<T>& problem, const Cluster& initial_solution) {
    // Asigno los puntos a los clusters al punto de servicio más cercano
    vector<Cluster> grupos(initial_solution.size());
    for (int i = 0; i < problem.get_m(); i++) {
      // Si el punto es uno de los clusteres, no lo añado
      if (find(initial_solution.begin(), initial_solution.end(), problem.get_points()[i]) != initial_solution.end()) {
        continue;
      }
      // Asigno cada punto al punto de servicio más cercano
      int nearest_cluster = get_nearest_cluster(problem.get_points()[i], initial_solution);
      grupos[nearest_cluster].push_back(problem.get_points()[i]);
    }
    return grupos;
  }

  int get_nearest_cluster(const vector<T>& point, const Cluster& clusters) {
    vector<pair<int, double>> lrc_distances;
    // Obtengo la distancia de cada punto de servicio al punto
    for (int i = 0; i < clusters.size(); i++) {
      double distance = euclidean_distance(point, clusters[i]);
      lrc_distances.push_back(make_pair(i, distance));
    }
    sort(lrc_distances.begin(), lrc_distances.end(), [](pair<int, double> a, pair<int, double> b) {
      return a.second < b.second;
    });
    int nearest_cluster = lrc_distances[0].first;
    return nearest_cluster;
  }

  /**
   * @brief Genera la solución inicial mediante la fase constructiva
  */
  Cluster constructive_fase(const Problem<T>& problem) {
    Cluster service_points;
    // Elegir un número inicial de clusters
    // 10% del número de puntos, con un mínimo de 2 clusters
    int num_clusters = problem.get_m() * 0.1;
    if (num_clusters < 2) num_clusters = 2;
    //cout << "GRASP: " << num_clusters << " clusters" << endl;

    // Primero hay que elegir 1 punto aleatorio como centroide
    srand(time(nullptr));
    int random_index = rand() % problem.get_m();
    service_points.push_back(problem.get_points()[random_index]);
    /*cout << "kmeans: Centroides elegidos aleatoriamente" << endl;
    for (int i = 0; i < num_clusters; i++) {
      cout << "kmeans: Centroid " << i << ": ";
      for (int j = 0; j < centroids[i].size(); j++) {
        cout << centroids[i][j] << " ";
      }
      cout << endl;
    }*/

    do { // Hasta llegar al número de clusters elegido
      std::vector<farthestElement> distances;
      std::vector<farthestElement> bestKDistances;
      farthestElement choosedElement;

      // Calculo la distancia de todos los puntos a los servicios
      for (int i = 0; i < problem.get_m(); i++) { // Para cada punto
        T min_distance = std::numeric_limits<T>::max(); // Inicializo la distancia mínima a infinito
        for (int j = 0; j < service_points.size(); j++) { // Para cada punto de servicio
          T distance = euclidean_distance(problem.get_points()[i], service_points[j]); // Calculo la distancia
          if (distance < min_distance) min_distance = distance; // Si es menor que la mínima, actualizo
        }
        distances.push_back(std::make_pair(i, min_distance)); // Guardo el punto y su distancia
      }

      // Ordeno los puntos por distancia más alejada
      std::sort(distances.begin(), distances.end(), [](const farthestElement& a, const farthestElement& b) {
        return a.second > b.second;
      });

      // Elijo aleatoriamente entre los 3 puntos más alejados
      int random_index_dist = rand() % 3;
      choosedElement = distances[random_index_dist];

      // Añado el punto elegido a los puntos de servicio
      service_points.push_back(problem.get_points()[choosedElement.first]);
    } while (service_points.size() < num_clusters);

    // Devolver la solución final
    return service_points;
  }

  vector<Cluster> intercambio(const Problem<T>& problem, const Cluster& initial_solution) {
    Cluster vecindario = problem.get_points();
    vector<Cluster> grupos;
    Cluster dummy;
    // Ahora debo intercambiar los puntos de servicio por alguno de los puntos del entorno
    for (int i = 0; i < initial_solution.size(); i++) {
      for (int j = 0; j < vecindario.size(); j++) {
        // Si el punto es uno de los clusteres, no lo añado
        //if (find(initial_solution.begin(), initial_solution.end(), vecindario[j]) != initial_solution.end()) {
          if (initial_solution[i] == vecindario[j]) {
          continue;
        }
        // Intercambio el punto de servicio por el punto del entorno
        dummy = initial_solution;
        dummy[i] = vecindario[j];
        grupos.push_back(dummy); // Añado la nueva solución vecina
      }
    }
    return grupos;
  }

  vector<Cluster> insercion(const Problem<T>& problem, const Cluster& initial_solution) {
    Cluster vecindario = problem.get_points();
    vector<Cluster> grupos;
    Cluster dummy;
    // Ahora debo insertar un punto del entorno en la solución
    for (int i = 0; i < vecindario.size(); i++) {
      // Si el punto es uno de los clusteres, no lo añado
      if (find(initial_solution.begin(), initial_solution.end(), vecindario[i]) != initial_solution.end()) {
        continue;
      }
      // Inserto el punto del entorno en la solución
      dummy = initial_solution;
      dummy.push_back(vecindario[i]);
      grupos.push_back(dummy); // Añado la nueva solución vecina
    }
    return grupos;
  }

  vector<Cluster> eliminacion(const Cluster& initial_solution) {
    vector<Cluster> grupos;
    Cluster dummy;
    // Ahora debo eliminar un punto de servicio de la solución
    for (int i = 0; i < initial_solution.size(); i++) {
      // Elimino el punto de servicio de la solución
      dummy = initial_solution;
      dummy.erase(dummy.begin() + i);
      grupos.push_back(dummy); // Añado la nueva solución vecina
    }
    return grupos;
  }
};