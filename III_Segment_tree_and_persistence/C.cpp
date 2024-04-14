#include <iostream>
#include <vector>

int con = 0;

int Max(int a1, int b1) { return (a1 > b1) ? a1 : b1; }

int Write(std::vector<int>& tree, int ind, int val, int pos,
          std::pair<int, int> pair) {
  if (pair.second == pair.first + 1) {
    tree[pos] = val;
    return val;
  }
  if ((pair.second + pair.first) / 2 <= ind) {
    tree[pos] = Max(tree[2 * pos + 1],
                    Write(tree, ind, val, 2 * pos + 2,
                          std::pair<int, int>((pair.second + pair.first) / 2,
                                              pair.second)));
    return tree[pos];
  }
  tree[pos] = Max(
      tree[2 * pos + 2],
      Write(tree, ind, val, 2 * pos + 1,
            std::pair<int, int>(pair.first, (pair.second + pair.first) / 2)));
  return tree[pos];
}

int Count(std::vector<int>& tree, int pos, std::pair<int, int> pair, int ind,
          int val) {
  if (tree[pos] < val) {
    return -1;
  }
  if (pair.first == pair.second - 1) {
    return pos - ((1 << con) - 1);
  }
  if (ind >= (pair.first + pair.second) / 2) {
    return Count(
        tree, 2 * pos + 2,
        std::pair<int, int>((pair.first + pair.second) / 2, pair.second), ind,
        val);
  }
  int lr =
      Count(tree, 2 * pos + 1,
            std::pair<int, int>(pair.first, (pair.first + pair.second) / 2),
            ind, val);
  if (lr >= 0) {
    return lr;
  }
  int rr =
      Count(tree, 2 * pos + 2,
            std::pair<int, int>((pair.first + pair.second) / 2, pair.second),
            ind, val);
  return rr;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int quantity;
  int quer;
  std::cin >> quantity >> quer;

  while ((1 << con) < quantity) {
    con += 1;
  }
  std::vector<int> tree(1 << (con + 2), 0);
  for (int i = 0; i < quantity; ++i) {
    int val;
    std::cin >> val;
    Write(tree, i, val, 0, std::pair<int, int>(0, (1 << con)));
  }
  for (int i = 0; i < quer; ++i) {
    int com;
    std::cin >> com;
    if (com == 1) {
      int ind;
      int val;
      std::cin >> ind >> val;
      int count =
          Count(tree, 0, std::pair<int, int>(0, (1 << con)), ind - 1, val);
      if (count < 0) {
        std::cout << -1 << '\n';
      } else {
        std::cout << count + 1 << '\n';
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