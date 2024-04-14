#include <iostream>
#include <stack>
#include <vector>

int Max(int x1, int x2, int x3) {
  if (x1 <= x2) {
    if (x2 <= x3) {
      return x3;
    }
    return x2;
  }
  if (x1 <= x3) {
    return x3;
  }
  return x1;
}

int num;
std::vector<int> vector;
std::vector<int> prev_gr;
std::vector<int> gr_len;
std::vector<int> prev_le;
std::vector<int> le_len;
std::stack<int> stack;

void Dynamics() {
  for (int i = 1; i < num; ++i) {
    int max_gr_len = 0;
    int max_le_len = 0;
    for (int j = 0; j < i; ++j) {
      if (vector[j] < vector[i] && gr_len[j] > max_gr_len) {
        max_gr_len = gr_len[j];
      }
      if (vector[j] > vector[i] && le_len[j] > max_le_len) {
        max_le_len = le_len[j];
      }
    }
    for (int j = 0; j < i; ++j) {
      if (vector[j] < vector[i] && gr_len[j] == max_gr_len) {
        le_len[i] = gr_len[j] + 1;
        prev_le[i] = j;
      }
      if (vector[j] > vector[i] && le_len[j] == max_le_len) {
        gr_len[i] = le_len[j] + 1;
        prev_gr[i] = j;
      }
    }
  }
}

void Write(int ind, bool flag) {
  stack.push(vector[ind]);
  if (flag) {
    if (prev_gr[ind] != -1) {
      Write(prev_gr[ind], !flag);
    }
    return;
  }
  if (prev_le[ind] != -1) {
    Write(prev_le[ind], !flag);
  }
}

int main() {
  std::cin >> num;
  vector = std::vector<int>(num);
  prev_gr = std::vector<int>(num, -1);
  gr_len = std::vector<int>(num, 1);
  prev_le = std::vector<int>(num, -1);
  le_len = std::vector<int>(num, 1);
  for (int i = 0; i < num; ++i) {
    std::cin >> vector[i];
  }
  Dynamics();
  int max_len = 0;
  for (int i = 0; i < num; ++i) {
    max_len = Max(gr_len[i], le_len[i], max_len);
  }
  std::cout << max_len << '\n';
  for (int i = 0; i < num; ++i) {
    if (max_len == gr_len[i]) {
      Write(i, true);
      break;
    }
    if (max_len == le_len[i]) {
      Write(i, false);
      break;
    }
  }
  while (!stack.empty()) {
    std::cout << stack.top() << ' ';
    stack.pop();
  }
  return 0;
}
