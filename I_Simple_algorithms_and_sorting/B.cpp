#include <cmath>
#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;
  std::vector<double> vec(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> vec[i];
  }
  std::vector<double> pref(number + 1, 0);
  for (int i = 1; i < number + 1; ++i) {
    pref[i] = pref[i - 1] + log(vec[i - 1]);
  }
  int ques;
  std::cin >> ques;
  const int kTEN = 10;
  std::cout.precision(kTEN);
  for (int i = 0; i < ques; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    std::cout << exp(1.0 / (right - left + 1) * (pref[right + 1] - pref[left]))
              << '\n';
  }
}