#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;
  std::vector<int> vec(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> vec[i];
  }
  std::vector<int> minl(number);
  std::vector<int> minr(number);
  minl[0] = vec[0];
  minr[number - 1] = vec[number - 1];
  for (int i = 1; i < number; ++i) {
    minl[i] = (vec[i] < minl[i - 1]) ? vec[i] : minl[i - 1];
    minr[number - 1 - i] = (vec[number - 1 - i] < minr[number - i])
                           ? vec[number - 1 - i]
                           : minr[number - i];
  }
  int ques;
  std::cin >> ques;
  for (int i = 0; i < ques; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    int minleft = minl[left - 1];
    int minright = minr[right - 1];
    std::cout << ((minleft < minright) ? minleft : minright) << '\n';
  }
}
