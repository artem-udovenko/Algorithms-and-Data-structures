#include <iostream>
#include <vector>

std::vector<bool> used;
std::vector<bool> color;
std::vector<std::vector<std::pair<int, int>>> paths;
std::vector<bool> answer;

bool Dfs(int vertex) {
  used[vertex] = true;
  bool res = color[vertex];
  for (auto& edge : paths[vertex]) {
    if (!used[edge.first]) {
      res = res ^ (answer[edge.second] = Dfs(edge.first));
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int tests;
  std::cin >> tests;
  for (int cnt = 0; cnt < tests; ++cnt) {
    int vertices;
    int edges;
    std::cin >> vertices >> edges;
    used = std::vector<bool>(vertices, false);
    paths = std::vector<std::vector<std::pair<int, int>>>(vertices);
    color = std::vector<bool>(vertices);
    answer = std::vector<bool>(edges);
    for (int i = 0; i < edges; ++i) {
      int dep;
      int des;
      std::cin >> dep >> des;
      paths[dep - 1].emplace_back(des - 1, i);
      paths[des - 1].emplace_back(dep - 1, i);
    }
    std::string colors;
    std::cin >> colors;
    for (int i = 0; i < vertices; ++i) {
      color[i] = bool(colors[i] % 2);
    }
    bool flag = false;
    for (int i = 0; i < vertices; ++i) {
      if (!used[i]) {
        flag = flag || Dfs(i);
      }
    }
    if (flag) {
      std::cout << -1 << '\n';
      continue;
    }
    for (bool ans : answer) {
      std::cout << ans;
    }
    std::cout << '\n';
  }
}