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

    // Primero hay que elegir k puntos aletorios como centroides
    srand(time(nullptr));
    for (int i = 0; i < num_clusters; i++) {
      int random_index = rand() % problem.get_m();
      centroids.push_back(problem.get_points()[random_index]);
    }

    // Defino un máximo de iteraciones
    int max_iterations = 100;
    int iteration = 0;

    // Bucle de generación de solución
    vector<bool> point_assigned(problem.get_m(), false);
    while (true && iteration < max_iterations) {
      iteration++;

      // Ahora se asignan los puntos con la lrc

        // Generar la lista restringida de candidatos
        vector<pair<int, double>> lrc;
        for (int i = 0; i < problem.get_m(); i++) {
            // Si el punto ya fue asignado, lo saltamos
            if (point_assigned[i]) continue;
            // Calculamos la distancia del punto al centroide más cercano
            double min_distance = numeric_limits<double>::max();
            for (int j = 0; j < centroids.size(); j++) {
                double distance = euclidean_distance(problem.get_points()[i], centroids[j]);
                if (distance < min_distance) min_distance = distance;
            }
            lrc.push_back(make_pair(i, min_distance));
        }

        // Si no hay candidatos disponibles, hemos terminado
        if (lrc.size() == 0) break;

        // Elegir un punto al azar de los 2 o 3 más alejados
        sort(lrc.begin(), lrc.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
            return a.second > b.second;
        });
        int num_candidates = min(3, (int)lrc.size());
        int random_index = rand() % num_candidates;
        int point_index = lrc[random_index].first;
        initial_solution[get_nearest_cluster(problem.get_points()[point_index], initial_solution)].push_back(problem.get_points()[point_index]);
        point_assigned[point_index] = true;
        // Si ya se asignaron todos los puntos, hemos terminado
        if (count(point_assigned.begin(), point_assigned.end(), false) == 0) break;
    }

    // Devolver la solución final
    Solution<T> solution(initial_solution);
    return solution;
  }

  int get_nearest_cluster(vector<T> point, Cluster clusters) {
    int nearest_cluster = 0;
    double min_distance = numeric_limits<double>::max();
    for (int i = 0; i < clusters.size(); i++) {
      double distance = euclidean_distance(point, centroid(clusters[i]));
      if (distance < min_distance) {
        min_distance = distance;
        nearest_cluster = i;
      }
    }
    return nearest_cluster;
  }
};