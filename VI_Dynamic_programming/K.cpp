#include <iostream>
#include <vector>

int num;
int cap;
std::vector<int> mas;
std::vector<int> cos;
std::vector<std::vector<std::pair<long long, std::vector<int>>>> dp;
int flag = 0;

void Input() {
  std::cin >> num >> cap;
  mas = std::vector<int>(num);
  cos = std::vector<int>(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> mas[i];
  }
  for (int i = 0; i < num; ++i) {
    std::cin >> cos[i];
  }
}

void Output() {
  long long max = 0;
  for (int j = 0; j <= cap; ++j) {
    if (dp[(flag + 1) % 2][j].first > max) {
      max = dp[(flag + 1) % 2][j].first;
    }
  }
  for (int j = 0; j <= cap; ++j) {
    if (dp[(flag + 1) % 2][j].first == max) {
      for (int ind : dp[(flag + 1) % 2][j].second) {
        std::cout << ind << '\n';
      }
      break;
    }
  }
}

int main() {
  Input();
  dp = std::vector<std::vector<std::pair<long long, std::vector<int>>>>(
      2, std::vector<std::pair<long long, std::vector<int>>>(
          cap + 1, std::pair(0, std::vector<int>())));
  for (int i = 0; i < num; ++i) {
    dp[flag] = std::vector<std::pair<long long, std::vector<int>>>(
        cap + 1, {0, std::vector<int>()});
    if (mas[i] <= cap) {
      dp[flag][mas[i]] = {cos[i], {i + 1}};
    }
    for (int j = 0; j <= cap; ++j) {
      if (dp[(flag + 1) % 2][j].first > 0) {
        if (dp[(flag + 1) % 2][j].first > dp[flag][j].first) {
          dp[flag][j] = dp[(flag + 1) % 2][j];
        }
        if (j + mas[i] <= cap) {
          if (dp[flag][j + mas[i]].first <
              dp[(flag + 1) % 2][j].first + cos[i]) {
            dp[flag][j + mas[i]].first = dp[(flag + 1) % 2][j].first + cos[i];
            dp[flag][j + mas[i]].second = dp[(flag + 1) % 2][j].second;
            dp[flag][j + mas[i]].second.push_back(i + 1);
          }
        }
      }
    }
    flag = (flag + 1) % 2;
  }
  Output();
  return 0;
}