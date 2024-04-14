#include <iostream>
#include <vector>

int vertices;
int edges;
bool flag;
int check;
std::vector<std::vector<int>> destinations;
std::vector<std::vector<int>> weights;
std::vector<std::vector<bool>> used;
std::vector<int> left;
std::vector<int> right;
std::vector<int> candidates;
std::vector<int> new_candidates;
std::vector<int> answer;

int PrefXor(int num) {
  int res = 0;
  for (int i = 0; i <= num % 4; ++i) {
    res ^= num - i;
  }
  return res;
}

void Recalc(int vertex) {
  for (size_t i = 0; i < destinations[vertex].size(); ++i) {
    int delta =
        right[vertex] + left[destinations[vertex][i]] - weights[vertex][i];
    if (delta > 0) {
      right[vertex] -= delta;
    } else if (delta < 0) {
      left[destinations[vertex][i]] -= delta;
    }
    delta = left[vertex] + right[destinations[vertex][i]] - weights[vertex][i];
    if (delta > 0) {
      right[destinations[vertex][i]] -= delta;
    } else if (delta < 0) {
      left[vertex] -= delta;
    }
  }
}

void Dfs1(int vertex, int parent) {
  for (size_t i = 0; i < destinations[vertex].size(); ++i) {
    if (!used[vertex][i]) {
      used[vertex][i] = true;
      int delta =
          right[vertex] + left[destinations[vertex][i]] - weights[vertex][i];
      if (delta > 0) {
        right[vertex] -= delta;
      } else if (delta < 0) {
        left[destinations[vertex][i]] -= delta;
      }
      if (parent != destinations[vertex][i]) {
        Dfs1(destinations[vertex][i], vertex);
      }
    }
  }
}

void Dfs2(int vertex) {
  if (flag) {
    return;
  }
  for (size_t i = 0; i < destinations[vertex].size(); ++i) {
    int val = weights[vertex][i] - answer[vertex];
    if (val <= 0) {
      flag = true;
      return;
    }
    if (answer[destinations[vertex][i]] == 0) {
      answer[destinations[vertex][i]] = val;
      check ^= val;
      Dfs2(destinations[vertex][i]);
      continue;
    }
    if (val != answer[destinations[vertex][i]]) {
      flag = true;
      return;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cin >> vertices >> edges;
  destinations = std::vector<std::vector<int>>(vertices);
  weights = std::vector<std::vector<int>>(vertices);
  used = std::vector<std::vector<bool>>(vertices);
  left = std::vector<int>(vertices);
  right = std::vector<int>(vertices);
  for (int i = 0; i < edges; ++i) {
    int dep;
    int des;
    int wht;
    std::cin >> dep >> des >> wht;
    destinations[dep - 1].push_back(des - 1);
    weights[dep - 1].push_back(wht);
    used[dep - 1].push_back(false);
    destinations[des - 1].push_back(dep - 1);
    weights[des - 1].push_back(wht);
    used[des - 1].push_back(false);
  }
  for (int i = 0; i < vertices; ++i) {
    int max = 0;
    int min = vertices + 1;
    for (size_t j = 0; j < weights[i].size(); ++j) {
      int weight = weights[i][j];
      if (weight > max) {
        max = weight;
      }
      if (weight < min) {
        min = weight;
      }
    }
    left[i] = std::max(max - vertices, 1);
    right[i] = std::min(min - 1, vertices);
  }
  //  Dfs1(0, -1);
  for (int i = 0; i < vertices; ++i) {
    if (left[i] == 1) {
      Recalc(i);
    }
  }
  for (int i = 0; i < vertices; ++i) {
    if (left[i] == 1) {
      candidates.push_back(i);
    }
  }
  int min = vertices;
  for (size_t j = 0; j < candidates.size(); ++j) {
    if (right[candidates[j]] < min) {
      min = right[candidates[j]];
    }
  }
  for (size_t j = 0; j < candidates.size(); ++j) {
    if (right[candidates[j]] == min) {
      new_candidates.push_back(candidates[j]);
    }
  }
  for (size_t j = 0; j < new_candidates.size(); ++j) {
    int vertex = new_candidates[j];
    answer = std::vector<int>(vertices);
    check = 1;
    answer[vertex] = 1;
    flag = false;
    Dfs2(vertex);
    if (flag || (check != PrefXor(vertices))) {
      continue;
    }
    for (size_t i = 0; i < answer.size(); ++i) {
      std::cout << answer[i] << ' ';
    }
    break;
  }
}