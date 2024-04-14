#include <iostream>
#include <vector>

int main() {
  int q1;
  int q2;
  std::cin >> q1 >> q2;
  std::vector<int> first(q1);
  std::vector<int> second(q2);
  std::vector<std::vector<int>> dp;
  for (int i = 0; i < q1; ++i) {
    std::cin >> first[i];
  }
  for (int i = 0; i < q2; ++i) {
    std::cin >> second[i];
  }
  const int kN = first.size() + 1;
  const int kM = second.size() + 1;
  dp = std::vector<std::vector<int>>(kN, std::vector<int>(kM, 0));
  for (int i = 1; i < kN; ++i) {
    int best = 0;
    for (int j = 1; j < kM; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (first[i - 1] == second[j - 1] && dp[i - 1][j] < best + 1) {
        dp[i][j] = best + 1;
      }
      if (first[i - 1] > second[j - 1] && dp[i - 1][j] > best) {
        best = dp[i - 1][j];
      }
    }
  }
  int ans = 0;
  for (int j = 0; j < kM; ++j) {
    if (dp[kN - 1][j] > ans) {
      ans = dp[kN - 1][j];
    }
  }
  std::cout << ans;
}