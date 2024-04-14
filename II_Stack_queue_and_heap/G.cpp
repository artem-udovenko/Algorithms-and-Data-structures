#include <algorithm>
#include <iostream>
#include <vector>

bool Comp(int x1, int x2) { return x1 > x2; }

void SiftDown(std::vector<long long>& heap, int& buf) {
  int ind = 0;
  const long long kMn = -(1 << 30);
  while (true) {
    long long left = kMn;
    long long right = kMn;
    if (2 * ind + 1 < buf) {
      left = heap[2 * ind + 1];
    }
    if (2 * ind + 2 < buf) {
      right = heap[2 * ind + 2];
    }
    if (left >= right) {
      if (left > heap[ind]) {
        std::swap(heap[ind], heap[2 * ind + 1]);
        ind = 2 * ind + 1;
      } else {
        break;
      }
    } else {
      if (right > heap[ind]) {
        std::swap(heap[ind], heap[2 * ind + 2]);
        ind = 2 * ind + 2;
      } else {
        break;
      }
    }
  }
}

int main() {
  long long number;
  int buf;
  long long a0;
  long long x0;
  long long y0;
  std::cin >> number >> buf >> a0 >> x0 >> y0;
  long long val = a0;
  const int kPow = 30;
  std::vector<long long> heap(buf, 0);
  for (int i = 0; i < buf; ++i) {
    val = (x0 * val + y0) % (1 << kPow);
    heap[i] = val;
  }
  std::sort(heap.begin(), heap.end(), Comp);
  for (int i = buf; i < number; ++i) {
    val = (x0 * val + y0) % (1 << kPow);
    if (val < heap[0]) {
      heap[0] = val;
      SiftDown(heap, buf);
    }
  }
  std::sort(heap.begin(), heap.end());
  for (int i = 0; i < buf; ++i) {
    std::cout << heap[i] << ' ';
  }
  return 0;
}