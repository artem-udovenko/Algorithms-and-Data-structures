#include <iostream>
#include <vector>
#define kBig 200000
#define INT_MAX 2147483647
#define INT_MIN -2147483648

void Swap(std::vector<int[2]>& heap1, std::vector<int[2]>& heap2, int position1,
          int position2) {
  std::swap(heap2[heap1[position1][1]][1], heap2[heap1[position2][1]][1]);
  std::swap(heap1[position1], heap1[position2]);
}

void SiftUp(std::vector<int[2]>& min_heap, std::vector<int[2]>& max_heap,
            int position, bool is_min) {
  while (position > 0 &&
         (is_min ? min_heap[(position - 1) / 2][0] > min_heap[position][0]
                 : max_heap[(position - 1) / 2][0] < max_heap[position][0])) {
    Swap((is_min ? min_heap : max_heap), (is_min ? max_heap : min_heap),
         position, (position - 1) / 2);
    position = (position - 1) / 2;
  }
}

void SiftDownMin(std::vector<int[2]>& min_heap, std::vector<int[2]>& max_heap,
                 int position, int& heap_size) {
  while (true) {
    std::vector<int[2]>& heap = min_heap;
    int left = INT_MAX;
    int leftind = position * 2 + 1;
    if (leftind < heap_size) {
      left = heap[leftind][0];
    }
    int right = INT_MAX;
    int rightind = position * 2 + 2;
    if (rightind < heap_size) {
      right = heap[rightind][0];
    }
    if (left < right) {
      if (left < heap[position][0]) {
        Swap(min_heap, max_heap, position, leftind);
        position = leftind;
      } else {
        break;
      }
    } else {
      if (right < heap[position][0]) {
        Swap(min_heap, max_heap, position, rightind);
        position = rightind;
      } else {
        break;
      }
    }
  }
}

void SiftDownMax(std::vector<int[2]>& min_heap, std::vector<int[2]>& max_heap,
                 int position, int& heap_size) {
  std::vector<int[2]>& heap = max_heap;
  while (true) {
    int left = INT_MIN;
    int leftind = position * 2 + 1;
    if (leftind < heap_size) {
      left = heap[leftind][0];
    }
    int right = INT_MIN;
    int rightind = position * 2 + 2;
    if (rightind < heap_size) {
      right = heap[rightind][0];
    }
    if (right < left) {
      if (left > heap[position][0]) {
        Swap(max_heap, min_heap, position, leftind);
        position = leftind;
      } else {
        break;
      }
    } else {
      if (right > heap[position][0]) {
        Swap(max_heap, min_heap, position, rightind);
        position = rightind;
      } else {
        break;
      }
    }
  }
}

void Insert(std::vector<int[2]>& min_heap, std::vector<int[2]>& max_heap,
            int& heap_size) {
  int value;
  std::cin >> value;
  min_heap[heap_size][0] = max_heap[heap_size][0] = value;
  min_heap[heap_size][1] = max_heap[heap_size][1] = heap_size;
  SiftUp(min_heap, max_heap, heap_size, true);
  SiftUp(min_heap, max_heap, heap_size++, false);
  std::cout << "ok\n";
}

void GetMin(std::vector<int[2]>& min_heap, int heap_size) {
  if (heap_size == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << min_heap[0][0] << '\n';
}

void GetMax(std::vector<int[2]>& max_heap, int heap_size) {
  if (heap_size == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << max_heap[0][0] << '\n';
}

void Extract(std::vector<int[2]>& min_heap, std::vector<int[2]>& max_heap,
             int& heap_size, bool is_min) {
  std::vector<int[2]>& first_heap = is_min ? min_heap : max_heap;
  std::vector<int[2]>& second_heap = is_min ? max_heap : min_heap;
  if (heap_size == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << first_heap[0][0] << '\n';
  int position = first_heap[0][1];
  Swap(first_heap, second_heap, 0, --heap_size);
  Swap(second_heap, first_heap, position, heap_size);
  SiftUp(min_heap, max_heap, position, !is_min);
  is_min ? SiftDownMin(min_heap, max_heap, 0, heap_size)
         : SiftDownMax(min_heap, max_heap, 0, heap_size);
}

void Size(int& heap_size) { std::cout << heap_size << '\n'; }

void Clear(int& heap_size) {
  heap_size = 0;
  std::cout << "ok\n";
}

int main() {
  std::vector<int[2]> min_heap(kBig);
  std::vector<int[2]> max_heap(kBig);
  int heap_size = 0;
  int quantity;
  std::cin >> quantity;
  for (int i = 0; i < quantity; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "insert") {
      Insert(min_heap, max_heap, heap_size);
    }
    if (command == "get_min") {
      GetMin(min_heap, heap_size);
    }
    if (command == "extract_min") {
      Extract(min_heap, max_heap, heap_size, true);
    }
    if (command == "get_max") {
      GetMax(max_heap, heap_size);
    }
    if (command == "extract_max") {
      Extract(min_heap, max_heap, heap_size, false);
    }
    if (command == "size") {
      Size(heap_size);
    }
    if (command == "clear") {
      Clear(heap_size);
    }
  }
  return 0;
}