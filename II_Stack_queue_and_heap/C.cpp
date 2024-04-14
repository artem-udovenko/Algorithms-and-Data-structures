#include <deque>
#include <iostream>
#include <queue>

int main() {
  int number;
  std::cin >> number;
  char ch;
  int ind;
  std::queue<int> queue;
  std::deque<int> deque;
  for (int i = 0; i < number; ++i) {
    std::cin >> ch;
    if (ch == '+') {
      std::cin >> ind;
      deque.push_back(ind);
    } else if (ch == '*') {
      std::cin >> ind;
      deque.push_front(ind);
    } else {
      std::cout << queue.front() << '\n';
      queue.pop();
    }
    if (deque.size() > queue.size()) {
      queue.push(deque.front());
      deque.pop_front();
    }
  }
  return 0;
}