#include <iostream>
#include <vector>

int num;
int grp;
int cap;
std::vector<std::vector<std::pair<int, int>>> bsk;
std::vector<long long> dp;

void Func(int ind, std::vector<std::vector<long long>>& bps) {
  int temp = bsk[ind].size();
  for (int j = 0; j < temp; ++j) {
    if (bsk[ind][j].first <= cap) {
      if (bsk[ind][j].second > bps[j][bsk[ind][j].first]) {
        bps[j][bsk[ind][j].first] = bsk[ind][j].second;
      }
    }
    for (int k = 0; k <= cap; ++k) {
      if (dp[k] > 0 && k + bsk[ind][j].first <= cap) {
        if (bsk[ind][j].second + dp[k] > bps[j][k + bsk[ind][j].first]) {
          bps[j][k + bsk[ind][j].first] = bsk[ind][j].second + dp[k];
        }
      }
    }
  }
}

int main() {
  std::cin >> num >> grp >> cap;
  bsk = std::vector<std::vector<std::pair<int, int>>>(grp);
  for (int i = 0; i < num; ++i) {
    int mas;
    int cos;
    int gr;
    std::cin >> mas >> cos >> gr;
    bsk[gr - 1].emplace_back(mas, cos);
  }
  dp = std::vector<long long>(cap + 1);
  for (int i = 0; i < grp; ++i) {
    if (bsk[i].empty()) {
      continue;
    }
    std::vector<std::vector<long long>> bps(bsk[i].size(), dp);
    Func(i, bps);
    int temp = bsk[i].size();
    for (int k = 0; k <= cap; ++k) {
      long long max = dp[k];
      for (int j = 0; j < temp; ++j) {
        if (bps[j][k] > max) {
          max = bps[j][k];
        }
      }
      dp[k] = max;
    }
  }
  long long max = 0;
  for (int k = 0; k <= cap; ++k) {
    if (dp[k] > max) {
      max = dp[k];
    }
  }
  std::cout << max;
  return 0;
}