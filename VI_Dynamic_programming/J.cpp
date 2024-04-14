#include <iostream>
#include <vector>

int main() {
  int num;
  const int kMod = 1'000'000'007;
  std::cin >> num;
  std::vector<int> vector(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> vector[i];
  }
  std::vector<long long> dp(num + 1);
  const int kMax = 1'000'000;
  std::vector<int> last(kMax + 1, -1);
  dp[0] = 1;
  for (int i = 1; i <= num; ++i) {
    dp[i] = (2 * dp[i - 1]) % kMod;
    if (last[vector[i - 1]] > -1) {
      dp[i] += kMod - dp[last[vector[i - 1]]];
      dp[i] %= kMod;
    }
    last[vector[i - 1]] = (i - 1);
  }
  std::cout << (dp[num] - 1) % kMod;
  return 0;
}