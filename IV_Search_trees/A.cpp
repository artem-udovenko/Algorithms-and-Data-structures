#include <iostream>
#include <vector>
#define INT_MIN -2147483648

struct Node {
  int key;
  int priority;
  Node* parent;
  Node* left_son;
  Node* right_son;
  Node() = default;
  Node(int key, int priority, Node* parent, Node* left_son, Node* right_son)
      : key(key),
        priority(priority),
        parent(parent),
        left_son(left_son),
        right_son(right_son) {}
};

struct Triple {
  int x1;
  int x2;
  int x3;
};

std::vector<Triple> answer;

void Write(Node verticle) {
  answer[verticle.key].x1 =
      (verticle.parent == nullptr) ? 0 : verticle.parent->key;
  answer[verticle.key].x2 =
      (verticle.left_son == nullptr) ? 0 : verticle.left_son->key;
  answer[verticle.key].x3 =
      (verticle.right_son == nullptr) ? 0 : verticle.right_son->key;
  if (verticle.left_son != nullptr) {
    Write(*verticle.left_son);
  }
  if (verticle.right_son != nullptr) {
    Write(*verticle.right_son);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Node* root = new Node{0, INT_MIN, nullptr, nullptr, nullptr};
  Node* stack = root;
  int quantity;
  std::cin >> quantity;
  std::vector<Node*> verticles(quantity + 1);
  for (int i = 1; i < quantity + 1; ++i) {
    int priority;
    std::cin >> priority >> priority;
    verticles[i] = new Node{i, priority, nullptr, nullptr, nullptr};
    while (priority < stack->priority && stack->priority != INT_MIN) {
      if (stack->parent != nullptr) {
        stack = stack->parent;
      }
    }
    verticles[i]->parent = stack;
    verticles[i]->left_son = stack->right_son;
    if (stack->right_son != nullptr) {
      stack->right_son->parent = verticles[i];
    }
    stack->right_son = verticles[i];
    stack = verticles[i];
  }
  answer = std::vector<Triple>(quantity + 1);
  Write(*root);
  delete root;
  for (Node* verticle : verticles) {
    delete verticle;
  }
  std::cout << "YES\n";
  for (int i = 1; i < quantity + 1; ++i) {
    std::cout << answer[i].x1 << ' ' << answer[i].x2 << ' ' << answer[i].x3
              << '\n';
  }
}