#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
class Problem {
 private:
  typedef vector<vector<T>> Cluster;
  int m_; // number of points
  int n_; // number of coordinates on the point
  vector<vector<T>> points_; // Set of points that can be any type

 public:
  Problem(int m, int n, vector<vector<T>> points) {
    m_ = m;
    n_ = n;
    points_ = points;
  }

  Problem(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
      string line;
      getline(file, line);
      m_ = stoi(line);
      getline(file, line);
      n_ = stoi(line);
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

  int get_m() const { return m_;};
  int get_n() { return n_;}
  vector<vector<T>> get_points() const { return points_;}

  void print() {
    cout << "m: " << m_ << endl;
    cout << "n: " << n_ << endl;
    cout << "points: " << endl;
    for (int i = 0; i < m_; i++) {
      for (int j = 0; j < n_; j++) {
        cout << points_[i][j] << " ";
      }
      cout << endl;
    }
  }
};