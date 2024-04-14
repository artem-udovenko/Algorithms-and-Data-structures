#include <iostream>
#include <vector>

int quantity;
std::vector<std::vector<long long>> tree;

void Add(int x1, int y1) {
  for (int i = x1; i < quantity; i = (i | (i + 1))) {
    for (int j = y1; j < quantity; j = (j | (j + 1))) {
      ++tree[i][j];
    }
  }
}

long long Get(int x1, int y1) {
  long long result = 0;
  for (int i = x1; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = y1; j >= 0; j = (j & (j + 1)) - 1) {
      result += tree[i][j];
    }
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int queries;
  std::cin >> quantity >> queries;
  tree = std::vector<std::vector<long long>>(
      quantity, std::vector<long long>(quantity, 0));
  for (int i = 0; i < queries; ++i) {
    std::string string;
    std::cin >> string;
    if (string == "ADD") {
      int x1;
      int y1;
      std::cin >> x1 >> y1;
      Add(x1 - 1, y1 - 1);
    } else {
      int x1;
      int y1;
      int x2;
      int y2;
      std::cin >> x1 >> y1 >> x2 >> y2;
      if (x1 > x2) {
        std::swap(x1, x2);
      }
      if (y1 > y2) {
        std::swap(y1, y2);
      }
      std::cout << Get(x2 - 1, y2 - 1) - Get(x1 - 2, y2 - 1) -
                   Get(x2 - 1, y1 - 2) + Get(x1 - 2, y1 - 2)
                << '\n';
    }
  }
}