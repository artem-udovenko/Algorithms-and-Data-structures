#include <iostream>
#include <vector>

std::vector<bool> used;
std::vector<std::vector<std::pair<int, bool>>> paths;
std::vector<std::vector<int>> squads;
std::vector<int> buffer;

void Dfs(int uuu) {
  if (!used[uuu]) {
    buffer.push_back(uuu);
    used[uuu] = true;
  }
  for (auto& edge : paths[uuu]) {
    if (!edge.second) {
      edge.second = true;
      Dfs(edge.first);
    }
  }
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;
  used = std::vector<bool>(vertices, false);
  paths = std::vector<std::vector<std::pair<int, bool>>>(vertices);
  for (int i = 0; i < edges; ++i) {
    int aaa;
    int bbb;
    std::cin >> aaa >> bbb;
    paths[aaa - 1].push_back(std::make_pair(bbb - 1, false));
    paths[bbb - 1].push_back(std::make_pair(aaa - 1, false));
  }
  for (int i = 0; i < vertices; ++i) {
    if (!used[i]) {
      buffer = std::vector<int>();
      Dfs(i);
      squads.push_back(buffer);
    }
  }
  std::cout << squads.size() << '\n';
  for (auto& squad : squads) {
    std::cout << squad.size() << '\n';
    for (int unit : squad) {
      std::cout << unit + 1 << ' ';
    }
    std::cout << '\n';
  }
}