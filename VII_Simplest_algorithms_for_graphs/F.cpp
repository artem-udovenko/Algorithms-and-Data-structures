#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<bool> used;
std::vector<int> tin;
std::vector<int> ret;
std::vector<std::vector<int>> paths;
std::set<int> answer;
int timer = 0;

void FindCutPoint(int departure, int parent) {
  used[departure] = true;
  tin[departure] = ret[departure] = timer++;
  int counter = 0;
  for (auto destination : paths[departure]) {
    if (destination == parent) {
      continue;
    }
    if (used[destination]) {
      ret[departure] = std::min(ret[departure], tin[destination]);
    } else {
      FindCutPoint(destination, departure);
      ++counter;
      ret[departure] = std::min(ret[departure], ret[destination]);
      if (parent != -1 && tin[departure] <= ret[destination]) {
        answer.insert(departure + 1);
      }
    }
  }
  if (parent == -1 && counter >= 2) {
    answer.insert(departure + 1);
  }
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;
  used = std::vector<bool>(vertices, false);
  tin = std::vector<int>(vertices, -1);
  ret = std::vector<int>(vertices, -1);
  paths = std::vector<std::vector<int>>(vertices);
  for (int i = 0; i < edges; ++i) {
    int dep;
    int des;
    std::cin >> dep >> des;
    paths[dep - 1].push_back(des - 1);
    paths[des - 1].push_back(dep - 1);
  }
  for (int i = 0; i < vertices; ++i) {
    if (!used[i]) {
      FindCutPoint(i, -1);
    }
  }
  std::cout << answer.size() << '\n';
  for (int ans : answer) {
    std::cout << ans << '\n';
  }
}