#include <iostream>
#include <vector>

int Write(std::vector<int>& tree, int ind, int val, int pos,
          std::pair<int, int> pair) {
  int delta;
  if (pair.second == pair.first + 1) {
    if (tree[pos] >= 0) {
      delta = val - tree[pos];
      tree[pos] = val;
      return delta;
    }
    delta = val + tree[pos];
    tree[pos] = -val;
    return -delta;
  }
  if ((pair.second + pair.first) / 2 <= ind) {
    delta =
        Write(tree, ind, val, 2 * pos + 2,
              std::pair<int, int>((pair.second + pair.first) / 2, pair.second));
    tree[pos] += delta;
    return delta;
  }
  delta =
      Write(tree, ind, val, 2 * pos + 1,
            std::pair<int, int>(pair.first, (pair.second + pair.first) / 2));
  tree[pos] += delta;
  return delta;
}

int Count(std::vector<int>& tree, int pos, std::pair<int, int> pair, int left,
          int right) {
  if (left <= pair.first && pair.second <= right) {
    return tree[pos];
  }
  if (left >= pair.second || right <= pair.first) {
    return 0;
  }
  return Count(tree, 2 * pos + 1,
               std::pair<int, int>(pair.first, (pair.first + pair.second) / 2),
               left, right) +
         Count(tree, 2 * pos + 2,
               std::pair<int, int>((pair.first + pair.second) / 2, pair.second),
               left, right);
}

int main() {
  int quantity;
  std::cin >> quantity;
  int con = 0;
  while ((1 << con) < quantity) {
    con += 1;
  }
  std::vector<int> tree(1 << (con + 2), 0);
  for (int i = 0; i < quantity; ++i) {
    int val;
    std::cin >> val;
    val *= -(((i % 2) * 2) - 1);
    Write(tree, i, val, 0, std::pair<int, int>(0, (1 << con)));
  }
  int quer;
  std::cin >> quer;
  for (int i = 0; i < quer; ++i) {
    int com;
    std::cin >> com;
    if (com == 1) {
      int left;
      int right;
      std::cin >> left >> right;
      if (left % 2 == 1) {
        std::cout << Count(tree, 0, std::pair<int, int>(0, (1 << con)),
                           left - 1, right)
                  << '\n';
      } else {
        std::cout << -Count(tree, 0, std::pair<int, int>(0, (1 << con)),
                            left - 1, right)
                  << '\n';
      }
    } else {
      int ind;
      int val;
      std::cin >> ind >> val;
      Write(tree, ind - 1, val, 0, std::pair<int, int>(0, (1 << con)));
    }
  }
  return 0;
}