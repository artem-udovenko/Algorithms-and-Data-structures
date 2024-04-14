#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> color;
std::vector<std::vector<int>> paths;
std::vector<int> cycle;
std::vector<bool> used;
std::vector<int> tin;
std::vector<int> tout;
int timer = 0;

int Dfs1(int uuu) {
  color[uuu] = 1;
  for (int vvv : paths[uuu]) {
    if (color[vvv] == 1) {
      cycle = std::vector<int>();
      cycle.push_back(uuu);
      color[uuu] = 2;
      return vvv;
    }
    if (color[vvv] == 0) {
      int end = Dfs1(vvv);
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

void Dfs(int uuu) {
  used[uuu] = true;
  tin[uuu] = timer++;
  for (int vvv : paths[uuu]) {
    if (!used[vvv]) {
      Dfs(vvv);
    }
  }
  tout[uuu] = timer++;
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
      Dfs1(i);
    }
    if (!cycle.empty()) {
      flag = true;
      break;
    }
  }
  if (flag) {
    std::cout << "-1";
  } else {
    used = std::vector<bool>(vertices);
    tin = std::vector<int>(vertices);
    tout = std::vector<int>(vertices);
    for (int i = 0; i < vertices; ++i) {
      if (!used[i]) {
        Dfs(i);
      }
    }
    std::vector<std::pair<int, int>> pairs(vertices);
    for (int i = 0; i < vertices; ++i) {
      pairs[i] = std::make_pair(tout[i], i);
    }
    std::sort(pairs.rbegin(), pairs.rend());
    for (auto& pair : pairs) {
      std::cout << pair.second + 1 << ' ';
    }
  }
}
