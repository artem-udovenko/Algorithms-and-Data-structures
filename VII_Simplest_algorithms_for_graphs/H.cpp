#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<bool> used;
std::vector<int> tin;
std::vector<int> ret;
std::vector<std::vector<int>> paths;
std::vector<std::vector<int>> condensation;
std::unordered_map<long, bool> answer;
std::vector<int> vertexes;
std::vector<int> component;
int leaves = 0;
int counter = 0;
int timer = 0;
const int KBig = 100'000;

long Compress(int xxx, int yyy) { return xxx * KBig + yyy; }

void FindBridge(int departure, int parent) {
  used[departure] = true;
  tin[departure] = ret[departure] = ++timer;
  for (auto destination : paths[departure]) {
    if (destination == parent) {
      continue;
    }
    if (used[destination]) {
      ret[departure] = std::min(ret[departure], tin[destination]);
    } else {
      FindBridge(destination, departure);
      ret[departure] = std::min(ret[departure], ret[destination]);
      if (tin[departure] < ret[destination]) {
        answer[Compress(departure, destination)] = true;
        answer[Compress(destination, departure)] = true;
        vertexes.push_back(departure);
        vertexes.push_back(destination);
      }
    }
  }
}

void Dfs(int ver) {
  component[ver] = counter;
  for (int des : paths[ver]) {
    if (!answer[Compress(ver, des)] && component[des] == 0) {
      Dfs(des);
    }
  }
}

void Leaves(int dep, int par) {
  int cnt = 0;
  for (int des : condensation[dep]) {
    if (des == par) {
      continue;
    }
    Leaves(des, dep);
    ++cnt;
  }
  if (par == -1 && cnt == 1) {
    ++leaves;
  }
  if (par != -1 && cnt == 0) {
    ++leaves;
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
      FindBridge(i, -1);
    }
  }
  component = std::vector<int>(vertices);
  for (int ver : vertexes) {
    if (component[ver] == 0) {
      ++counter;
      Dfs(ver);
    }
  }
  condensation = std::vector<std::vector<int>>(counter);
  for (size_t i = 0; i < vertexes.size(); i += 2) {
    condensation[component[vertexes[i]] - 1].push_back(
        component[vertexes[i + 1]] - 1);
    condensation[component[vertexes[i + 1]] - 1].push_back(
        component[vertexes[i]] - 1);
  }
  if (counter > 0) {
    Leaves(0, -1);
  }
  std::cout << (leaves + 1) / 2;
}