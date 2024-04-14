#include <iostream>
#include <stack>
#include <vector>
#define INT_MAX 2'147'483'647
#define INT_MIN -2'147'483'648

int BinarySearch(std::vector<int>& array, int val) {
  int left = 0;
  int right = array.size() - 1;
  while (left != right - 1) {
    ((array[(left + right) / 2] >= val) ? left : right) = (left + right) / 2;
  }
  return right;
}

int main() {
  int num;
  std::cin >> num;
  std::vector<int> array(num);
  std::vector<int> dp(num);
  std::vector<int> position(num);
  std::vector<int> previous(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> array[i];
    dp[i] = INT_MIN;
  }
  dp[0] = INT_MAX;
  position[0] = -1;
  int max_length = 0;
  for (int i = 0; i < num; ++i) {
    int jnd = BinarySearch(dp, array[i]);
    if (dp[jnd - 1] >= array[jnd] && array[jnd] >= dp[jnd]) {
      dp[jnd] = array[i];
      position[jnd] = i;
      previous[i] = position[jnd - 1];
      if (jnd > max_length) {
        max_length = jnd;
      }
    }
  }
  std::stack<int> stack;
  int pos = position[max_length];
  while (pos > -1) {
    stack.push(pos + 1);
    pos = previous[pos];
  }
  std::cout << max_length << '\n';
  while (!stack.empty()) {
    std::cout << stack.top() << ' ';
    stack.pop();
  }
  return 0;
}
