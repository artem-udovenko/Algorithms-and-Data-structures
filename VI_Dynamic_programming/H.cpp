#include <iostream>
#include <stack>
#include <vector>

std::string first;
std::string second;
std::vector<std::vector<unsigned long int>> dp;
std::vector<std::vector<std::pair<int, int>>> prev;
std::stack<int> stack1;
std::stack<int> stack2;

void Print(int ind, int jnd) {
  if (ind * jnd == 0) {
    return;
  }
  if (prev[ind][jnd] == std::pair<int, int>(ind - 1, jnd - 1)) {
    stack1.push(ind);
    stack2.push(jnd);
    Print(ind - 1, jnd - 1);
    return;
  }
  Print(prev[ind][jnd].first, prev[ind][jnd].second);
}

int main() {
  std::cin >> first >> second;
  const int kN = first.size() + 1;
  const int kM = second.size() + 1;
  dp = std::vector<std::vector<unsigned long int>>(
      kN, std::vector<unsigned long int>(kM, 0));
  prev = std::vector<std::vector<std::pair<int, int>>>(
      kN, std::vector<std::pair<int, int>>(kM));
  for (int i = 1; i < kN; ++i) {
    for (int j = 1; j < kM; ++j) {
      if (first[i - 1] == second[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        prev[i][j] = std::pair<int, int>(i - 1, j - 1);
      } else if (dp[i - 1][j] >= dp[i][j - 1]) {
        dp[i][j] = dp[i - 1][j];
        prev[i][j] = std::pair<int, int>(i - 1, j);
      } else {
        dp[i][j] = dp[i][j - 1];
        prev[i][j] = std::pair<int, int>(i, j - 1);
      }
    }
  }
  Print(kN - 1, kM - 1);
  std::cout << stack1.size() << '\n';
  while (!stack1.empty()) {
    std::cout << stack1.top() << ' ';
    stack1.pop();
  }
  std::cout << '\n';
  while (!stack2.empty()) {
    std::cout << stack2.top() << ' ';
    stack2.pop();
  }
}