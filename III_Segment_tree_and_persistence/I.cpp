#include <algorithm>
#include <iostream>
#include <vector>
#define INT_MAX 2147483647

void Initialization(
    int quantity, int power, std::vector<int>& array,
    std::vector<std::vector<std::pair<int, int>>>& sparse_table1,
    std::vector<std::vector<std::pair<int, int>>>& sparse_table2) {
  for (int i = 0; i < quantity; ++i) {
    sparse_table1[0][i] = std::pair<int, int>(array[i], i);
  }
  for (int i = 1; i < power; ++i) {
    for (int j = 0; j < quantity - (1 << (i - 1)); ++j) {
      sparse_table1[i][j] = (sparse_table1[i - 1][j].first <
                             sparse_table1[i - 1][j + (1 << (i - 1))].first)
                            ? sparse_table1[i - 1][j]
                            : sparse_table1[i - 1][j + (1 << (i - 1))];
    }
  }
  for (int i = 0; i < quantity; ++i) {
    sparse_table2[0][i] = std::pair<int, int>(INT_MAX, -1);
  }
  for (int i = 0; i < quantity - 1; ++i) {
    sparse_table2[1][i] = (array[i] > array[i + 1])
                          ? std::pair<int, int>(array[i], i)
                          : std::pair<int, int>(array[i + 1], i + 1);
  }
  for (int i = 2; i < power; ++i) {
    for (int j = 0; j < quantity - (1 << (i - 1)); ++j) {
      std::vector<std::pair<int, int>> temp;
      temp.push_back(sparse_table1[i - 1][j]);
      temp.push_back(sparse_table1[i - 1][j + (1 << (i - 1))]);
      temp.push_back(sparse_table2[i - 1][j]);
      temp.push_back(sparse_table2[i - 1][j + (1 << (i - 1))]);
      std::sort(temp.begin(), temp.end());
      if (temp[0] == temp[1]) {
        sparse_table2[i][j] = temp[2];
      } else {
        sparse_table2[i][j] = temp[1];
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int quantity;
  int queries;
  std::cin >> quantity >> queries;
  std::vector<int> array(quantity, 0);
  for (int i = 0; i < quantity; ++i) {
    std::cin >> array[i];
  }
  int power = 0;
  while ((1 << power) < quantity) {
    ++power;
  }
  std::vector<std::vector<std::pair<int, int>>> sparse_table1(
      power,
      std::vector<std::pair<int, int>>(quantity, std::pair<int, int>(0, 0)));
  std::vector<std::vector<std::pair<int, int>>> sparse_table2(
      power,
      std::vector<std::pair<int, int>>(quantity, std::pair<int, int>(0, 0)));
  Initialization(quantity, power, array, sparse_table1, sparse_table2);
  for (int i = 0; i < queries; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    int zone = 0;
    while ((1 << zone) < right - left + 1) {
      ++zone;
    }
    std::vector<std::pair<int, int>> temp;
    zone = abs(zone - 1);
    temp.push_back(sparse_table1[zone][left - 1]);
    temp.push_back(sparse_table1[zone][right - (1 << zone)]);
    temp.push_back(sparse_table2[zone][left - 1]);
    temp.push_back(sparse_table2[zone][right - (1 << zone)]);
    std::sort(temp.begin(), temp.end());
    if (temp[0] == temp[1]) {
      std::cout << temp[2].first << '\n';
    } else {
      std::cout << temp[1].first << '\n';
    }
  }
}