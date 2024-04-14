#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

int Partition(std::vector<int>& vec, int left, int right) {
  int pivot = vec[rand() % (right - left + 1) + left];
  int ind = left;
  int jnd = right;
  while (ind <= jnd) {
    while (vec[ind] < pivot) {
      ++ind;
    }
    while (vec[jnd] > pivot) {
      --jnd;
    }
    if (ind <= jnd) {
      std::swap(vec[ind++], vec[jnd--]);
    }
  }
  return ind - 1;
}

void QuickSort(std::vector<int>& vec, int left, int right) {
  if (left >= right) {
    return;
  }
  if (right == left + 1 && vec[left] > vec[right]) {
    std::swap(vec[left], vec[right]);
    return;
  }
  int border = Partition(vec, left, right);
  QuickSort(vec, left, border);
  QuickSort(vec, border + 1, right);
}

int main() {
  int number;
  std::cin >> number;
  std::vector<int> vec(number);
  std::vector<int> auxvec(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> vec[i];
  }
  srand(time(nullptr));
  QuickSort(vec, 0, number - 1);
  for (int i = 0; i < number; ++i) {
    std::cout << vec[i] << ' ';
  }
  return 0;
}