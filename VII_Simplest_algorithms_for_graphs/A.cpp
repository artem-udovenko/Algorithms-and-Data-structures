#include <iostream>
#include <vector>

std::vector<int> color;
std::vector<std::vector<int>> paths;
std::vector<int> cycle;

int Dfs(int uuu) {
  color[uuu] = 1;
  for (int vvv : paths[uuu]) {
    if (color[vvv] == 1) {
      cycle = std::vector<int>();
      cycle.push_back(uuu);
      color[uuu] = 2;
      return vvv;
    }
    if (color[vvv] == 0) {
      int end = Dfs(vvv);
      if (end > -1) {
        cycle.push_back(uuu);
        if (uuu == end) {
          color[uuu] = 2;
          return -1;
        }
        color[uuu] = 2;
        return end;
      }
    }
  }
  color[uuu] = 2;
  return -1;
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;
  color = std::vector<int>(vertices);
  paths = std::vector<std::vector<int>>(vertices);
  for (int i = 0; i < edges; ++i) {
    int aaa;
    int bbb;
    std::cin >> aaa >> bbb;
    paths[aaa - 1].push_back(bbb - 1);
  }
  bool flag = false;
  for (int i = 0; i < vertices; ++i) {
    if (color[i] == 0) {
      Dfs(i);
    }
    if (!cycle.empty()) {
      flag = true;
      break;
    }
  }
  if (flag) {
    std::cout << "YES\n";
    for (auto it = cycle.rbegin(); it < cycle.rend(); ++it) {
      std::cout << (*it + 1) << ' ';
    }
  } else {
    std::cout << "NO";
  }
}