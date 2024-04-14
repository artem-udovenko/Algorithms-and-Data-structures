#include <deque>
#include <iostream>
#include <queue>

void Push(std::queue<long long>& queue, long long num,
          std::deque<long long>& deque) {
  queue.push(num);
  while (!deque.empty() && deque.back() < num) {
    deque.pop_back();
  }
  deque.push_back(num);
}

void Pop(std::queue<long long>& queue, std::deque<long long>& deque) {
  if (queue.front() == deque.front()) {
    deque.pop_front();
  }
  queue.pop();
}

int main() {
  int quantity;
  long long gsum = 0;
  std::cin >> quantity;
  std::vector<int> vec(quantity);
  for (int i = 0; i < quantity; ++i) {
    std::cin >> vec[i];
    gsum += vec[i];
  }
  std::vector<long long> result(quantity);
  long long sum = 0;
  for (int i = 0; i < quantity / 2; ++i) {
    sum += vec[i];
  }
  for (int i = 0; i < quantity; ++i) {
    result[i] = sum;
    sum -= vec[i];
    sum += vec[(i + quantity / 2) % quantity];
  }
  std::queue<long long> queue;
  std::deque<long long> deque;
  for (int i = 1; i < (quantity - quantity / 2) % quantity; ++i) {
    Push(queue, result[i], deque);
  }
  long long answer = gsum;
  for (int i = 0; i < quantity; ++i) {
    Push(queue, result[(i + quantity - quantity / 2) % quantity], deque);
    if (deque.front() < answer) {
      answer = deque.front();
    }
    Pop(queue, deque);
  }
  std::cout << gsum - answer << ' ' << answer;
}