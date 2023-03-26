#pragma once

#include "../include/algorithm.h"
#include <random>
#include <ctime>

template <typename T>
class Kmeans : public Algorithm<T> { // K means
 public:
  typedef vector<vector<T>> Cluster;
  Kmeans() : Algorithm<T>() {};
  ~Kmeans() {};
  Solution<T> run(Problem<T> problem) {
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

      // Asignar cada punto al cluster cuyo centroide esté más cerca
      for (int i = 0; i < problem.get_m(); i++) {
        vector<T> point = problem.get_points()[i];
        double min_distance = numeric_limits<double>::max();
        int closest_cluster = 0;
        for (int j = 0; j < num_clusters; j++) {
          double distance = euclidean_distance(point, centroids[j]);
          if (distance < min_distance) {
            min_distance = distance;
            closest_cluster = j;
          }
        }
        grupos[closest_cluster].push_back(point);
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

    // Centroide
    /*cout << "El centroides calculado en kmeans es: " << endl;
    for (int i = 0; i < centroids.size(); i++) {
      cout << "Centroid " << i << ": ";
      for (int j = 0; j < centroids[i].size(); j++) {
        cout << centroids[i][j] << " ";
      }
      cout << endl;
    }*/
    return solution;
  };
};