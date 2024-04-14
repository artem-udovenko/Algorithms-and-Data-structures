#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> paths;
std::vector<std::vector<int>> rpaths;
std::vector<int> component;
std::vector<bool> used;
std::vector<int> tout;

int timer = 0;
int counter = 0;

void Dfs(int uuu) {
  used[uuu] = true;
  timer++;
  for (int vvv : paths[uuu]) {
    if (!used[vvv]) {
      Dfs(vvv);
    }
  }
  tout[uuu] = timer++;
}

void Component(int dep) {
  component[dep] = counter;
  for (int des : rpaths[dep]) {
    if (component[des] == 0) {
      Component(des);
    }
  }
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;
  paths = std::vector<std::vector<int>>(vertices);
  rpaths = std::vector<std::vector<int>>(vertices);
  for (int i = 0; i < edges; ++i) {
    int dep;
    int des;
    std::cin >> dep >> des;
    paths[dep - 1].push_back(des - 1);
    rpaths[des - 1].push_back(dep - 1);
  }
  used = std::vector<bool>(vertices);
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
  std::vector<int> sorted(vertices);
  for (size_t i = 0; i < pairs.size(); ++i) {
    sorted[i] = pairs[i].second;
  }
  component = std::vector<int>(vertices, 0);
  for (int i = 0; i < vertices; ++i) {
    if (component[sorted[i]] == 0) {
      ++counter;
      Component(sorted[i]);
    }
  }
  std::cout << counter << '\n';
  for (int num : component) {
    std::cout << num << ' ';
  }
}