#include <iostream>
#include <vector>

const int kLim = 18;
const int kMax = 100'000;

int main() {
  int height;
  int planes;
  std::cin >> height >> planes;
  std::vector<std::vector<int>> dp(kLim);
  dp[0] = std::vector<int>(kMax, 1);
  for (int i = 1; i < kLim; ++i) {
    dp[i] = std::vector<int>(1, 1);
    while (dp[i][dp[i].size() - 1] < kMax) {
      dp[i].push_back(dp[i][dp[i].size() - 1] + dp[i - 1][dp[i].size() - 1]);
    }
  }
  int res = 0;
  if (planes >= kLim) {
    while ((1 << res) < height) {
      ++res;
    }
    std::cout << res;
  } else {
    if (planes == 0) {
      std::cout << (height > 1 ? -1 : 0);
    } else {
      while (dp[planes][res] < height) {
        ++res;
      }
      std::cout << res;
    }
  }
}