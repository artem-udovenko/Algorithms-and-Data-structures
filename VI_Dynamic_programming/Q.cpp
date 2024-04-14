#include <iostream>
#include <vector>

bool Bit(int mask, int pos) { return (mask & (1 << pos)) != 0; }

int main() {
  int num;
  std::cin >> num;
  std::vector<std::vector<bool>> mat(num, std::vector<bool>(num));
  std::vector<int> dp(1 << num, 0);
  for (int i = 0; i < num; ++i) {
    std::string str;
    std::cin >> str;
    for (int j = 0; j < num; ++j) {
      mat[i][j] = (str[j] == 'Y');
    }
  }
  for (int mask = 0; mask < (1 << num); ++mask) {
    for (int i = 0; i < num; ++i) {
      if (Bit(mask, i)) {
        for (int j = i + 1; j < num; ++j) {
          if (Bit(mask, j) && mat[i][j] &&
              dp[mask - ((1 << i) + (1 << j))] > dp[mask] - 2) {
            dp[mask] = dp[mask - ((1 << i) + (1 << j))] + 2;
          }
        }
      }
    }
  }
  std::cout << dp[(1 << num) - 1];
}