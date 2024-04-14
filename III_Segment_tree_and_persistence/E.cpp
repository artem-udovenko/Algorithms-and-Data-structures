#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> ccord(0);
int con = 0;

int BinSearch(int val) {
  int left = 0;
  int right = ccord.size();
  while (ccord[left] != val) {
    if (ccord[(left + right) / 2] == val) {
      return (left + right) / 2;
    }
    if (ccord[(left + right) / 2] < val) {
      left = (left + right) / 2;
    } else {
      right = (left + right) / 2;
    }
  }
  return left;
}

int Write(std::vector<long long>& tree, int ind, int pos,
          std::pair<int, int> pair) {
  if (pair.second == pair.first + 1) {
    ++tree[pos];
    return ccord[ind];
  }
  int delta;
  if ((pair.second + pair.first) / 2 <= ind) {
    delta =
        Write(tree, ind, 2 * pos + 2,
              std::pair<int, int>((pair.second + pair.first) / 2, pair.second));
    tree[pos] += delta;
    return delta;
  }
  delta =
      Write(tree, ind, 2 * pos + 1,
            std::pair<int, int>(pair.first, (pair.second + pair.first) / 2));
  tree[pos] += delta;
  return delta;
}

long long Count(std::vector<long long>& tree, int pos, std::pair<int, int> pair,
                int left, int right) {
  if (left <= pair.first && pair.second <= right) {
    if (pair.second == pair.first + 1) {
      return tree[pos] * ccord[pos - (1 << con) + 1];
    }
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
  char com;
  std::vector<std::pair<int, int>> vector(0);
  std::vector<int> cord(0);
  for (int i = 0; i < quantity; ++i) {
    int val;
    std::cin >> com >> val;
    vector.emplace_back(((com == '+') ? 0 : 1), val);
    cord.push_back(val);
  }
  std::sort(cord.begin(), cord.end());
  ccord.push_back(cord[0]);
  for (size_t i = 1; i < cord.size(); ++i) {
    if (ccord.back() != cord[i]) {
      ccord.push_back(cord[i]);
    }
  }
  while ((1 << con) <= ccord.size()) {
    ++con;
  }
  std::vector<long long> tree(2 * (1 << con), 0);
  for (int i = 0; i < quantity; ++i) {
    int val = vector[i].second;
    if (vector[i].first == 0) {
      Write(tree, BinSearch(val), 0, std::pair<int, int>(0, (1 << con)));
    } else {
      std::cout << Count(tree, 0, std::pair<int, int>(0, (1 << con)), 0,
                         BinSearch(val) + 1)
                << '\n';
    }
  }
}