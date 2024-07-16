
#include "algorithm/DP.h"


std::pair<std::vector<int>, double> dpAlgorithm(std::vector<std::vector<double>> graph) {

  int n = graph.size();
  int start = 0;
  std::vector<std::vector<double>> dp(1 << n, std::vector<double>(n, std::numeric_limits<double>::max()));
  dp[1 << start][start] = 0;
  for (int mask = 0; mask < (1 << n); ++mask) {
    for (int u = 0; u < n; ++u) {
      if (mask & (1 << u)) {
        for (int v = 0; v < n; ++v) {
          if (!(mask & (1 << v))) {
            dp[mask | (1 << v)][v] = std::min(dp[mask | (1 << v)][v], dp[mask][u] + graph[u][v]);
          }
        }
      }
    }
  }

  double min_cost = std::numeric_limits<double>::max();
  int last = -1;
  for (int i = 0; i < n; ++i) {
    if (i != start) {
      double cost = dp[(1 << n) - 1][i] + graph[i][start];
      if (cost < min_cost) {
        min_cost = cost;
        last = i;
      }
    }
  }

  std::vector<int> path;
  int mask = (1 << n) - 1;
  while (mask) {
    path.push_back(last);
    int prev_last = -1;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i) && dp[mask][last] == dp[mask ^ (1 << last)][i] + graph[i][last]) {
        prev_last = i;
        break;
      }
    }
    mask ^= (1 << last);
    last = prev_last;
  }
  std::reverse(path.begin(), path.end());
  path.push_back(start);

  return {path, min_cost};
}