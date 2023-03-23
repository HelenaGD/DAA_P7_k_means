template <typename T>
class Solution {
 private:
  vector<vector<vector<T>>> clusters_;
  double sse_;
 public:
  Solution(vector<vector<vector<T>>> clusters) {
    clusters_ = clusters;
    sse_ = 0;
  }

  void evaluate(Problem<T> problem) {
    vector<T> centroid;
    for (int k = 0; k < clusters_.size(); k++) {
      centroid = problem.centroid(clusters_[k].size());
      for (int i = 0; i < clusters_[k].size(); i++) {
        for (int j = 0; j < clusters_[k][i].size(); j++) {
          sse_ += pow(problem.euclidean_distance(centroid, clusters_[i][j]), 2);
        }
      }
    }
  }

  double get_sse() { return sse_; }
  vector<vector<vector<T>>> get_clusters() { return clusters_; }
};