#include <iostream>
#include <vector>
#define INT_MAX 2147483647

void Swap(std::vector<std::pair<long long, int>*>& heap, int position1,
          int position2, std::vector<int>& queries) {
  std::swap(queries[heap[position1]->second], queries[heap[position2]->second]);
  std::swap(heap[position1], heap[position2]);
}

void SiftUp(std::vector<std::pair<long long, int>*>& heap, int position,
            std::vector<int>& queries) {
  while (position > 0 &&
         heap[(position - 1) / 2]->first > heap[position]->first) {
    Swap(heap, position, (position - 1) / 2, queries);
    position = (position - 1) / 2;
  }
}

void SiftDown(std::vector<std::pair<long long, int>*>& heap, int position,
              std::vector<int>& queries, const int kHeapSize) {
  while (true) {
    long long left = INT_MAX;
    int leftind = position * 2 + 1;
    if (leftind < kHeapSize) {
      left = heap[leftind]->first;
    }
    long long right = INT_MAX;
    int rightind = position * 2 + 2;
    if (rightind < kHeapSize) {
      right = heap[rightind]->first;
    }
    if (left < right) {
      if (left < heap[position]->first) {
        Swap(heap, position, leftind, queries);
        position = leftind;
      } else {
        break;
      }
    } else {
      if (right < heap[position]->first) {
        Swap(heap, position, rightind, queries);
        position = rightind;
      } else {
        break;
      }
    }
  }
}

void Insert(std::vector<std::pair<long long, int>*>& heap,
            std::vector<std::pair<long long, int>>& entities,
            std::vector<int>& queries, int& heap_size, int& entity_number) {
  long long value;
  std::cin >> value;
  int position = heap_size;
  queries.push_back(position);
  entities[entity_number] =
      std::pair<long long, int>(value, queries.size() - 1);
  heap[heap_size++] = &entities[entity_number++];
  SiftUp(heap, position, queries);
}

void GetMin(std::vector<std::pair<long long, int>*>& heap,
            std::vector<int>& queries) {
  std::cout << heap[0]->first << '\n';
  queries.push_back(-1);
}

void ExtractMin(std::vector<std::pair<long long, int>*>& heap,
                std::vector<int>& queries, int& heap_size) {
  Swap(heap, 0, --heap_size, queries);
  SiftDown(heap, 0, queries, heap_size);
  queries.push_back(-1);
}

void DecreaseKey(std::vector<std::pair<long long, int>*>& heap,
                 std::vector<int>& queries) {
  int identificator;
  long long delta;
  std::cin >> identificator >> delta;
  int position = queries[identificator - 1];
  heap[position]->first -= delta;
  SiftUp(heap, position, queries);
  queries.push_back(-1);
}

int main() {
  std::cout.tie(0);
  std::cin.tie(0);
  const int kBig = 1000000;
  std::vector<std::pair<long long, int>*> heap(kBig, nullptr);
  int heap_size = 0;
  std::vector<std::pair<long long, int>> entities(kBig);
  int entity_number = 0;
  std::vector<int> queries;
  int quantity;
  std::cin >> quantity;
  for (int i = 0; i < quantity; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "insert") {
      Insert(heap, entities, queries, heap_size, entity_number);
    }
    if (command == "getMin") {
      GetMin(heap, queries);
    }
    if (command == "extractMin") {
      ExtractMin(heap, queries, heap_size);
    }
    if (command == "decreaseKey") {
      DecreaseKey(heap, queries);
    }
  }
  return 0;
}