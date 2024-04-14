#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;
  std::vector<unsigned long long> vec(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> vec[i];
  }
  const int kTWO = 2;
  std::vector<std::vector<unsigned long long>> sort(kTWO);
  const int kSize = 63;
  for (int digit = 0; digit < kSize; ++digit) {
    for (int i = 0; i < number; ++i) {
      sort[(vec[i] >> digit) % kTWO].push_back(vec[i]);
    }
    vec.clear();
    for (int j = 0; j < kTWO; ++j) {
      vec.insert(vec.end(), sort[j].begin(), sort[j].end());
      sort[j].clear();
    }
  }
  for (int i = 0; i < number; ++i) {
    std::cout << vec[i] << '\n';
  }
  return 0;
}