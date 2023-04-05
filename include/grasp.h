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

    // Fase de mejora

    // Creo la solución
    Solution<T> solution(grupos, initial_solution);

    return solution;
  }

  int get_nearest_cluster(vector<T> point, Cluster clusters) {
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
  Cluster constructive_fase(Problem<T> problem) {
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
};