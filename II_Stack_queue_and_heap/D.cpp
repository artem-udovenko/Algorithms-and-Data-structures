#include <deque>
#include <iostream>
#include <queue>

void Enqueue(std::queue<int>& queue, std::deque<int>& deque) {
  int number;
  std::cin >> number;
  queue.push(number);
  while (!deque.empty() && deque.back() > number) {
    deque.pop_back();
  }
  deque.push_back(number);
  std::cout << "ok" << '\n';
}

void Dequeue(std::queue<int>& queue, std::deque<int>& deque) {
  if (queue.empty()) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << queue.front() << '\n';
  if (queue.front() == deque.front()) {
    deque.pop_front();
  }
  queue.pop();
}

void Front(std::queue<int>& queue) {
  if (queue.empty()) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << queue.front() << '\n';
}

void Size(std::queue<int>& queue) { std::cout << queue.size() << '\n'; }

void Clear(std::queue<int>& queue, std::deque<int>& deque) {
  queue = std::queue<int>();
  deque = std::deque<int>();
  std::cout << "ok" << '\n';
}

void Min(std::deque<int>& deque) {
  if (deque.empty()) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << deque.front() << '\n';
}

int main() {
  std::queue<int> queue;
  std::deque<int> deque;
  int query;
  std::cin >> query;
  for (int i = 0; i < query; ++i) {
    std::string com;
    std::cin >> com;
    switch (com[0]) {
      case 'e':
        Enqueue(queue, deque);
        break;
      case 'd':
        Dequeue(queue, deque);
        break;
      case 'f':
        Front(queue);
        break;
      case 's':
        Size(queue);
        break;
      case 'c':
        Clear(queue, deque);
        break;
      case 'm':
        Min(deque);
        break;
    }
  }
  return 0;
}