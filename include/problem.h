#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

template <typename T>
class Problem {
 private:
  int m_; // number of points
  int k_; // number of clusters
  vector<vector<T>> points_; // Set of points that can be any type

 public:
  Problem(int m, int k, vector<vector<T>> points) {
    m_ = m;
    k_ = k;
    points_ = points;
  }

  Problem(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
      string line;
      getline(file, line);
      m_ = stoi(line);
      getline(file, line);
      k_ = stoi(line);
      while (getline(file, line)) {
        vector<T> point;
        stringstream ss(line);
        string element;
        while (getline(ss, element, ' ')) {
          element = element.replace(element.find(','), 1, ".");
          point.push_back(stod(element));
        }
        points_.push_back(point);
      }
    }
  }

  int get_m() { return m_;};
  int get_k() { return k_;}
  vector<vector<T>> get_points() { return points_;}

  // Función de la distancia euclidea
  double euclidean_distance(vector<T> point1, vector<T> point2) {
    double distance = 0;
    for (int i = 0; i < point1.size(); i++) {
      distance += pow(point1[i] - point2[i], 2);
    }
    return sqrt(distance);
  }

  // El método para calcular el centroide del r-esimo cluster
  vector<T> centroid(int r, vector<int> cluster) {
    vector<T> centroid;
    for (int i = 0; i < cluster.size(); i++) {
      centroid.push_back(0);
    }
    int count = 0;
    for (int i = 0; i < cluster.size(); i++) {
      if (cluster[i] == r) {
        for (int j = 0; j < k_; j++) {
          centroid[j] += points_[i][j];
        }
        count++;
      }
    }
    for (int i = 0; i < k_; i++) {
      centroid[i] /= count;
    }
    return centroid;
  }

  void print() {
    cout << "m: " << m_ << endl;
    cout << "k: " << k_ << endl;
    cout << "points: " << endl;
    for (int i = 0; i < m_; i++) {
      for (int j = 0; j < k_; j++) {
        cout << points_[i][j] << " ";
      }
      cout << endl;
    }
  }
};