#include <iostream>
#include <vector>
#define PAIR std::pair<int, int>

std::vector<std::vector<int>> merge_tree;
std::vector<int> vector;
int result;

int BinSearchLeft(int depth, PAIR borders, int value) {
  int left = borders.first;
  int right = borders.second;
  if (merge_tree[depth][left] >= value) {
    return left;
  }
  if (merge_tree[depth][right] < value) {
    return right + 1;
  }
  if (merge_tree[depth][right] == value) {
    return right;
  }
  while (right != left + 1) {
    int check = merge_tree[depth][(left + right) / 2];
    if (check == value) {
      return (left + right) / 2;
    }
    if (check < value) {
      left = (left + right) / 2;
    } else {
      right = (left + right) / 2;
    }
  }
  return right;
}

int BinSearchRight(int depth, PAIR borders, int value) {
  int left = borders.first;
  int right = borders.second;
  if (merge_tree[depth][right] <= value) {
    return right;
  }
  if (merge_tree[depth][left] > value) {
    return left - 1;
  }
  if (merge_tree[depth][left] == value) {
    return left;
  }
  while (right != left + 1) {
    int check = merge_tree[depth][(left + right) / 2];
    if (check == value) {
      return (left + right) / 2;
    }
    if (check < value) {
      left = (left + right) / 2;
    } else {
      right = (left + right) / 2;
    }
  }
  return left;
}

void ConstructMerge(int depth, int left, int right) {
  if (right < left) {
    return;
  }
  if (right == left) {
    merge_tree[depth][left] = vector[left];
    return;
  }
  ConstructMerge(depth + 1, left, (left + right) / 2);
  ConstructMerge(depth + 1, (left + right) / 2 + 1, right);
  int ind1 = left;
  int ind2 = (left + right) / 2 + 1;
  int ind = left;
  while (ind1 < (left + right) / 2 + 1 || ind2 < right + 1) {
    if (ind1 == (left + right) / 2 + 1) {
      merge_tree[depth][ind++] = merge_tree[depth + 1][ind2++];
      continue;
    }
    if (ind2 == right + 1) {
      merge_tree[depth][ind++] = merge_tree[depth + 1][ind1++];
      continue;
    }
    if (merge_tree[depth + 1][ind1] <= merge_tree[depth + 1][ind2]) {
      merge_tree[depth][ind++] = merge_tree[depth + 1][ind1++];
      continue;
    }
    merge_tree[depth][ind++] = merge_tree[depth + 1][ind2++];
  }
}

void Count(int depth, PAIR borders, PAIR segment, int min, int max) {
  if (borders.first > borders.second) {
    return;
  }
  if (borders.first > segment.second || borders.second < segment.first) {
    return;
  }
  if (segment.first <= borders.first && borders.second <= segment.second) {
    int left = BinSearchLeft(depth, borders, min);
    int right = BinSearchRight(depth, borders, max);
    result += right - left + 1;
    return;
  }
  Count(depth + 1, PAIR(borders.first, (borders.first + borders.second) / 2),
        segment, min, max);
  Count(depth + 1,
        PAIR((borders.first + borders.second) / 2 + 1, borders.second), segment,
        min, max);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int quantity;
  int queries;
  std::cin >> quantity >> queries;
  vector = std::vector<int>(quantity, 0);
  for (int i = 0; i < quantity; ++i) {
    std::cin >> vector[i];
  }
  int power = 0;
  while ((1 << power) < quantity) {
    ++power;
  }
  merge_tree =
      std::vector<std::vector<int>>(2 * power, std::vector<int>(quantity, 0));
  ConstructMerge(0, 0, quantity - 1);
  for (int i = 0; i < queries; ++i) {
    int x0;
    int y0;
    int min;
    int max;
    std::cin >> x0 >> y0 >> min >> max;
    result = 0;
    Count(0, PAIR(0, quantity - 1), PAIR(x0 - 1, y0 - 1), min, max);
    std::cout << result << '\n';
  }
}