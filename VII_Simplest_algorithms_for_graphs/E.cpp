#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<bool> used;
std::vector<int> tin;
std::vector<int> ret;
std::vector<std::vector<std::pair<int, int>>> paths;
std::vector<int> answer;
std::unordered_map<long, int> multiple;
int timer = 0;
const int KBig = 100'000;

void FindBridge(int departure, int parent) {
  used[departure] = true;
  tin[departure] = ret[departure] = ++timer;
  for (auto path : paths[departure]) {
    int destination = path.first;
    if (destination == parent) {
      continue;
    }
    if (used[destination]) {
      ret[departure] = std::min(ret[departure], tin[destination]);
    } else {
      FindBridge(destination, departure);
      ret[departure] = std::min(ret[departure], ret[destination]);
      if (tin[departure] < ret[destination]) {
        if (multiple[departure * KBig + destination] < 2) {
          answer.push_back(path.second);
        }
      }
    }
  }
}

int main() {
  int vertices;
  int edges;
  std::cin >> vertices >> edges;
  used = std::vector<bool>(vertices, false);
  tin = std::vector<int>(vertices, -1);
  ret = std::vector<int>(vertices, -1);
  paths = std::vector<std::vector<std::pair<int, int>>>(vertices);
  for (int i = 0; i < edges; ++i) {
    int dep;
    int des;
    std::cin >> dep >> des;
    paths[dep - 1].emplace_back(des - 1, i + 1);
    multiple[(dep - 1) * KBig + des - 1]++;
    paths[des - 1].emplace_back(dep - 1, i + 1);
    multiple[(des - 1) * KBig + dep - 1]++;
  }
  for (int i = 0; i < vertices; ++i) {
    if (!used[i]) {
      FindBridge(i, -1);
    }
  }
  std::sort(answer.begin(), answer.end());
  std::cout << answer.size() << '\n';
  for (int ans : answer) {
    std::cout << ans << ' ';
  }
}