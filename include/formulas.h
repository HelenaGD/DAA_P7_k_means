#pragma once
#include <cmath>
#include <vector>
using namespace std;

// Función de la distancia euclidea
template <typename T>
double euclidean_distance(vector<T> point1, vector<T> point2) {
  double distance = 0;
  for (int i = 0; i < point1.size(); i++) {
    distance += pow(point1[i] - point2[i], 2);
  }
  return sqrt(distance);
}

// El método para calcular el centroide del r-esimo cluster
template <typename T>
vector<T> centroid(vector<vector<T>> cluster) {
  vector<T> centroid;
  for (int i = 0; i < cluster[0].size(); i++) {
    centroid.push_back(0);
  }
  for (int i = 0; i < cluster.size(); i++) {
    for (int j = 0; j < cluster[i].size(); j++) {
      centroid[j] += cluster[i][j];
    }
  }
  for (int i = 0; i < centroid.size(); i++) {
    centroid[i] /= cluster.size();
  }
  return centroid;
}