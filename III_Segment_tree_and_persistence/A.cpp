#include <iomanip>
#include <iostream>
#include <vector>
#define MP 16

int Cheer(int dur, std::vector<int>& tree, int ind, int left, int right) {
  if (right <= dur) {
    return tree[(ind + (1 << (MP + 2))) % (1 << (MP + 2))];
  }
  if (left >= dur) {
    return 0;
  }
  return Cheer(dur, tree, 2 * ind + 1, left, (left + right) / 2) +
         Cheer(dur, tree, 2 * ind + 2, (left + right) / 2, right);
}

int Find(int dur, int ind, int left, int right) {
  if (right == left + 1) {
    return ind;
  }
  if ((left + right) / 2 <= dur) {
    return Find(dur, 2 * ind + 2, (left + right) / 2, right);
  }
  return Find(dur, 2 * ind + 1, left, (left + right) / 2);
}

void Increase(std::vector<int>& tree, int ind, int delta) {
  while (ind >= 0) {
    tree[(ind + (1 << (MP + 2))) % (1 << (MP + 2))] += delta;
    ind = (ind + 1) / 2 - 1;
  }
}

int main() {
  const int kPr = 6;
  std::cout << std::setprecision(kPr);
  int quantity;
  std::cin >> quantity;
  std::vector<std::pair<int, int>> vec(quantity, std::pair<int, int>(0, 0));
  int us = 0;
  for (int i = 0; i < quantity; ++i) {
    std::string com;
    std::cin >> com;
    if (com == "RUN") {
      std::cin >> vec[i].first >> vec[i].second;
      if (vec[i].first > us) {
        us = vec[i].first;
      }
    } else {
      std::cin >> vec[i].first;
      vec[i].second = -1;
    }
  }
  std::vector<int> tree((1 << (MP + 2)), 0);
  std::vector<int> data(us + 1, 0);
  int count = 0;
  for (int i = 0; i < quantity; ++i) {
    int dur;
    if (vec[i].second == -1) {
      dur = data[vec[i].first % (us + 1)];
      if (dur == 0) {
        std::cout << 0 << '\n';
      } else {
        if (count == 1) {
          std::cout << 1 << '\n';
        } else {
          std::cout << 1.0 * Cheer(dur, tree, 0, 0, (1 << MP)) / (count - 1)
                    << '\n';
        }
      }
    } else {
      if (data[vec[i].first % (us + 1)] == 0) {
        ++count;
      } else {
        Increase(tree, Find(data[vec[i].first % (us + 1)], 0, 0, (1 << MP)),
                 -1);
      }
      Increase(tree, Find(vec[i].second, 0, 0, (1 << MP)), 1);
      data[vec[i].first % (us + 1)] = vec[i].second;
    }
  }
  return 0;
}