#pragma once
#include <vector>
#include "formulas.h"

using namespace std;

template <typename T>
class Solution {
 private:
  typedef vector<vector<T>> Cluster;
  vector<Cluster> clusters_;
  int num_clusters_;
  double sse_;
 public:
  Solution(vector<Cluster> clusters) {
    num_clusters_ = clusters.size();
    clusters_ = clusters;
    sse_ = 0;
  }

  /**
   * Método para evaluar la solución en función
   * de la distancia de los puntos de cada cluster
   * a su centroide
  */
  void evaluate() {
    vector<T> the_centroid;
    // Primero itero sobre los clusters
    for (int k = 0; k < clusters_.size(); k++) {
      the_centroid = centroid(clusters_[k]);
      // Para todos los puntos del cluster
      for (int i = 0; i < clusters_[k].size(); i++) {
        // Calculo la distancia euclidea entre el centroide y el punto
        sse_ += pow(euclidean_distance(the_centroid, clusters_[k][i]), 2);
      }
    }
  }

  double get_sse() { return sse_; }
  vector<Cluster> get_clusters() { return clusters_; }
  int get_num_clusters() { return num_clusters_; }
};