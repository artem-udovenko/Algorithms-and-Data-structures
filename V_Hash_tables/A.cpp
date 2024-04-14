#include <ctime>
#include <iostream>
#include <vector>
#define INT_MAX 2147483647
#define CRITICAL 0.95

std::pair<int, int> GenerateHash() {
  return {rand() % INT_MAX, rand() % INT_MAX};
}

int Hash(int key, int x1, int x2, size_t size) {
  return (1LL * x1 * key + x2) % INT_MAX % size;
}

size_t size = (1 << 4);
size_t max_depth = 0;
std::vector<std::vector<int>> hash_table(size, std::vector<int>());
std::pair<int, int> pair = GenerateHash();

void Rehash() {
  std::vector<std::vector<int>> new_hash_table(size *= 2, std::vector<int>());
  max_depth = 0;
  pair = GenerateHash();
  for (std::vector<int>& list : hash_table) {
    for (int x : list) {
      std::vector<int>& vector =
          new_hash_table[Hash(x, pair.first, pair.second, size)];
      vector.push_back(x);
      if (vector.size() > max_depth) {
        ++max_depth;
      }
    }
  }
  hash_table = new_hash_table;
}

void Insert(int value, std::vector<int>& vector) {
  for (size_t j = 0; j < vector.size() + 1; ++j) {
    if (j == vector.size()) {
      vector.push_back(value);
      (max_depth < vector.size()) ? ++max_depth : 0;
    }
    if (vector[j] == value) {
      break;
    }
  }
}

void Erase(int value, std::vector<int>& vector) {
  for (size_t j = 0; j < vector.size(); ++j) {
    if (vector[j] == value) {
      vector.erase(vector.begin() + j);
      break;
    }
  }
}

void Find(int value, std::vector<int>& vector) {
  for (size_t j = 0; j < vector.size() + 1; ++j) {
    if (j == vector.size()) {
      std::cout << "NO\n";
      break;
    }
    if (vector[j] == value) {
      std::cout << "YES\n";
      break;
    }
  }
}

int main() {
  srand(time(nullptr));
  int quantity;
  std::cin >> quantity;
  for (int i = 0; i < quantity; ++i) {
    if (1.0 * max_depth / size >= CRITICAL) {
      Rehash();
    }
    char command;
    int value;
    std::cin >> command >> value;
    std::vector<int>& vector =
        hash_table[Hash(value, pair.first, pair.second, size)];
    if (command == '+') {
      Insert(value, vector);
    }
    if (command == '-') {
      Erase(value, vector);
    }
    if (command == '?') {
      Find(value, vector);
    }
  }
}