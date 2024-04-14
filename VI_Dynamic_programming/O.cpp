#include <iostream>
#include <stack>
#include <vector>

constexpr int kIntMax = 2147483647;

bool Bit(int mask, int pos) { return (mask & pos) != 0; }

int num;

void Dynamics(std::vector<std::vector<int>>& matrix,
              std::vector<std::vector<long long>>& dp,
              std::vector<std::vector<int>>& last) {
  for (int mask = 1; mask < (1 << num); ++mask) {
    int ver0 = 1;
    for (int i = 0; i < num; ++i) {
      bool flag = true;
      if (Bit(mask, ver0)) {
        int ver = 1;
        for (int j = 0; j < num; ++j) {
          if (Bit(mask, ver) && i != j) {
            flag = false;
            if (dp[mask ^ ver0][j] + matrix[i][j] < dp[mask][i]) {
              dp[mask][i] = dp[mask ^ ver0][j] + matrix[i][j];
              last[mask][i] = j;
            }
          }
          ver *= 2;
        }
      }
      dp[mask][i] *= int(!flag);
      ver0 *= 2;
    }
  }
}

int main() {
  std::cin >> num;
  std::vector<std::vector<int>> matrix(num, std::vector<int>(num));
  std::vector<std::vector<long long>> dp(1 << num,
                                         std::vector<long long>(num, kIntMax));
  std::vector<std::vector<int>> last(1 << num, std::vector<int>(num, -1));
  for (int i = 0; i < num; ++i) {
    for (int j = 0; j < num; ++j) {
      std::cin >> matrix[i][j];
    }
  }
  Dynamics(matrix, dp, last);
  int res = dp[(1 << num) - 1][0];
  int ind = 0;
  for (int i = 1; i < num; ++i) {
    if (dp[(1 << num) - 1][i] < res) {
      res = dp[(1 << num) - 1][i];
      ind = i;
    }
  }
  std::cout << res << '\n';
  std::stack<int> stack;
  int mask = (1 << num) - 1;
  for (; mask > 0; mask ^= (1 << ind), ind = last[mask + (1 << ind)][ind]) {
    stack.push(ind + 1);
  }
  while (!stack.empty()) {
    std::cout << stack.top() << ' ';
    stack.pop();
  }
}