#include <deque>
#include <iostream>
#include <queue>

void Push(std::queue<int>& queue, int num, std::deque<int>& deque) {
  queue.push(num);
  while (!deque.empty() && deque.back() > num) {
    deque.pop_back();
  }
  deque.push_back(num);
}

void Pop(std::queue<int>& queue, std::deque<int>& deque) {
  if (queue.front() == deque.front()) {
    deque.pop_front();
  }
  queue.pop();
}

int main() {
  int number;
  int len;
  std::cin >> number >> len;
  const int kMaxn = 1000;
  std::vector<std::vector<int>> matrix(kMaxn, std::vector<int>(kMaxn, 0));
  std::vector<std::vector<int>> rmatrix(kMaxn, std::vector<int>(kMaxn, 0));
  std::vector<std::vector<int>> rrmatrix(kMaxn, std::vector<int>(kMaxn, 0));
  for (int i = 0; i < number; ++i) {
    for (int j = 0; j < number; ++j) {
      std::cin >> matrix[i][j];
    }
  }
  std::queue<int> queue;
  std::deque<int> deque;
  for (int i = 0; i < number; ++i) {
    queue = std::queue<int>();
    deque = std::deque<int>();
    for (int k = 0; k < len - 1; ++k) {
      Push(queue, matrix[i][k], deque);
    }
    for (int j = len - 1; j < number; ++j) {
      Push(queue, matrix[i][j], deque);
      rmatrix[i][j] = deque.front();
      Pop(queue, deque);
    }
  }
  for (int j = len - 1; j < number; ++j) {
    queue = std::queue<int>();
    deque = std::deque<int>();
    for (int k = 0; k < len - 1; ++k) {
      Push(queue, rmatrix[k][j], deque);
    }
    for (int i = len - 1; i < number; ++i) {
      Push(queue, rmatrix[i][j], deque);
      rrmatrix[i][j] = deque.front();
      Pop(queue, deque);
    }
  }
  for (int i = len - 1; i < number; ++i) {
    for (int j = len - 1; j < number; ++j) {
      std::cout << rrmatrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}