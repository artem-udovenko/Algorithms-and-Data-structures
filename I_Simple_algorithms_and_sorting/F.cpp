#include <iostream>
#include <vector>

int QuickSelect(int pos, std::vector<int>&vec, std::vector<int>&nltp,
                std::vector<int>&gtp) {
  const int kLen = vec.size();
  std::swap(vec[kLen / 2], vec[kLen - 1]);
  int pivot = vec[kLen - 1];
  for (int i = 0; i < kLen - 1; ++i) {
    if (vec[i] <= pivot) {
      nltp.push_back(vec[i]);
    } else {
      gtp.push_back(vec[i]);
    }
  }
  nltp.push_back(vec[kLen - 1]);
  int ind = nltp.size();
  if (pos == ind - 1) {
    return nltp[pos];
  }
  if (pos < ind - 1) {
    vec.clear();
    gtp.clear();
    return QuickSelect(pos, nltp, vec, gtp);
  }
  vec.clear();
  nltp.clear();
  return QuickSelect(pos - ind, gtp, vec, nltp);
}

int main() {
  int number;
  int pos;
  int a0;
  int a1;
  std::cin >> number >> pos >> a0 >> a1;
  std::vector<int> vec(number);
  vec[0] = a0;
  vec[1] = a1;
  const int k123 = 123;
  const int k45 = 45;
  const int k10000000 = 10000000;
  const int k4321 = 4321;
  for (int i = 2; i < number; ++i) {
    vec[i] = (k123 * vec[i - 1] + k45 * vec[i - 2]) % (k10000000 + k4321);
  }
  std::vector<int> gtp(0);
  std::vector<int> nltp(0);
  std::cout << QuickSelect(pos - 1, vec, nltp, gtp);
  return 0;
}