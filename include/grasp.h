#pragma once

#include "../include/algorithm.h"
#include <random>
#include <ctime>
#include <algorithm>

template <typename T>
class GRASP : public Algorithm<T> { // Greedy Randomized Adaptive Search Procedure
 public:
  typedef vector<vector<T>> Cluster;
  GRASP() : Algorithm<T>() {};
  ~GRASP() {};
  Solution<T> run(Problem<T> problem) {
     

    /*// Inicializo el conjunto de puntos
    Cluster points = problem.get_points();

    // Elegir un número inicial de clusters
    // 10% del número de puntos, con un mínimo de 2 clusters
    int num_clusters = points.size() * 0.1;
    if (num_clusters < 2) num_clusters = 2;

    // Generar la solución inicial vacía
    vector<vector<T>> initial_solution(num_clusters);
    vector<bool> point_assigned(points.size(), false);

    // Bucle de generación de solución
    while (true) {
      // Generar la lista restringida de candidatos
      vector<pair<int, double>> lrc = generate_lrc(points, initial_solution);

      // Si no hay candidatos disponibles, hemos terminado
      if (lrc.size() == 0) break;

      // Elegir un punto al azar de la lista restringida
      int random_index = rand() % lrc.size();
      int point_index = lrc[random_index].first;
      initial_solution[get_nearest_cluster(points[point_index], initial_solution)].push_back(points[point_index]);
      point_assigned[point_index] = true;
    }

    // Devolver la solución final
    Solution<T> solution(initial_solution);
    */
    Solution<T> solution = constructive_fase(problem);
    return solution;
  }

  Solution<T> constructive_fase(Problem<T> problem) {
    Cluster centroids;
    // Elegir un número inicial de clusters
    // 10% del número de puntos, con un mínimo de 2 clusters
    int num_clusters = problem.get_m() * 0.1;
    if (num_clusters < 2) num_clusters = 2;
    //cout << "Kmeans: " << num_clusters << " clusters" << endl;

    // Primero hay que elegir k puntos aletorios como centroides
    srand(time(nullptr));
    for (int i = 0; i < num_clusters; i++) {
      int random_index = rand() % problem.get_m();
      centroids.push_back(problem.get_points()[random_index]);
    }
    /*cout << "kmeans: Centroides elegidos aleatoriamente" << endl;
    for (int i = 0; i < num_clusters; i++) {
      cout << "kmeans: Centroid " << i << ": ";
      for (int j = 0; j < centroids[i].size(); j++) {
        cout << centroids[i][j] << " ";
      }
      cout << endl;
    }*/

    // Defino un máximo de iteraciones
    int max_iterations = 100;
    bool centroids_changed = true;
    int iteration = 0;

    // Inicializar los clusters
    vector<Cluster> grupos(num_clusters);

    // Mientras los centroides cambien y no se alcance el máximo de iteraciones
    while (centroids_changed && iteration < max_iterations) {
      iteration++;
      centroids_changed = false;

      // Vaciar los clusters
      for (int i = 0; i < num_clusters; i++) {
        grupos[i].clear();
      }

      // Ahora los puntos los asigno con la lrc
      for (int i = 0; i < problem.get_m(); i++) {
        vector<T> point = problem.get_points()[i];
        double min_distance = numeric_limits<double>::max();
        int random_best_cluster = get_nearest_cluster(point, centroids);
        /*
        for (int j = 0; j < num_clusters; j++) {
          double distance = euclidean_distance(point, centroids[j]);
          if (distance < min_distance) {
            min_distance = distance;
            closest_cluster = j;
          }
        }*/
        grupos[random_best_cluster].push_back(point);
      }

      // Calcular los nuevos centroides de cada cluster
      for (int i = 0; i < num_clusters; i++) {
        vector<T> new_centroid = centroid(grupos[i]);
        if (new_centroid != centroids[i]) {
          centroids[i] = new_centroid;
          centroids_changed = true;
        }
      }
    }

    // Devolver la solución final
    Solution<T> solution(grupos);
    return solution;
  }

  int get_nearest_cluster(vector<T> point, Cluster clusters) {
    int nearest_cluster = 0;
    vector<T> lrc;
    vector<pair<int, double>> lrc_distances;
    for (int i = 0; i < clusters.size(); i++) {
      double distance = euclidean_distance(point, clusters[i]);
      lrc_distances.push_back(make_pair(i, distance));
    }
    sort(lrc_distances.begin(), lrc_distances.end(), [](pair<int, double> a, pair<int, double> b) {
      return a.second < b.second;
    });
    int random_index = rand() % lrc_distances.size();
    nearest_cluster = lrc_distances[random_index].first;
    return nearest_cluster;
  }
};