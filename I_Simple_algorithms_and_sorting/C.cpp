#include <iostream>
#include <vector>

int Max(int a1, int a2) { return (a1 > a2) ? a1 : a2; }

int MiddleAlg(std::vector<int> veca, std::vector<int> vecb, int len) {
  int left = -1;
  int right = len - 1;
  int mid;
  while (right != left + 1) {
    mid = (right + left) / 2;
    if (veca[mid] - vecb[mid] < 0) {
      left = mid;
    } else {
      right = mid;
    }
  }
  if (left == -1) {
    return right + 1;
  }
  return (Max(veca[left], vecb[left]) < Max(veca[right], vecb[right]))
         ? (left + 1)
         : (right + 1);
}

int main() {
  int number;
  int mumber;
  int len;
  std::cin >> number >> mumber >> len;
  std::vector<std::vector<int>> avec(number);
  std::vector<std::vector<int>> bvec(mumber);
  int elem;
  for (int i = 0; i < number; ++i) {
    for (int j = 0; j < len; ++j) {
      std::cin >> elem;
      avec[i].push_back(elem);
    }
  }
  for (int i = 0; i < mumber; ++i) {
    for (int j = 0; j < len; ++j) {
      std::cin >> elem;
      bvec[i].push_back(elem);
    }
  }
  int ques;
  std::cin >> ques;
  int ind1;
  int ind2;
  for (int i = 0; i < ques; ++i) {
    std::cin >> ind1 >> ind2;
    std::cout << MiddleAlg(avec[ind1 - 1], bvec[ind2 - 1], len) << '\n';
  }
  return 0;
}
