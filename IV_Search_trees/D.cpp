#include <cstring>
#include <iostream>
#include <random>
#include <vector>
#define BIG 100000
#define INT_MIN -2147483648

struct Node {
  int key;
  int priority;
  int quantity;
  Node* parent;
  Node* left_son;
  Node* right_son;
  Node() = default;
  Node(int key, int priority, int quantity, Node* parent, Node* left_son,
       Node* right_son)
      : key(key),
        priority(priority),
        quantity(quantity),
        parent(parent),
        left_son(left_son),
        right_son(right_son) {}
  inline static std::vector<Node*> vector;
  inline static Node* root = nullptr;
};

int Quantity(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->quantity;
}

std::pair<Node*, Node*> Split(Node* root, int key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }
  std::pair<Node*, Node*> pair;
  if (root->key < key) {
    pair = Split(root->right_son, key);
    root->right_son = pair.first;
    if (pair.first != nullptr) {
      pair.first->parent = root;
    }
    root->quantity = Quantity(root->left_son) + Quantity(root->right_son) + 1;
    return {root, pair.second};
  }
  pair = Split(root->left_son, key);
  root->left_son = pair.second;
  if (pair.second != nullptr) {
    pair.second->parent = root;
  }
  root->quantity = Quantity(root->left_son) + Quantity(root->right_son) + 1;
  return {pair.first, root};
}

Node* Merge(Node* root1, Node* root2) {
  if (root2 == nullptr) {
    return root1;
  }
  if (root1 == nullptr) {
    return root2;
  }
  if (Node::root == root1 || Node::root == root2) {
    Node::root = ((root1->priority > root2->priority) ? root1 : root2);
  }
  if (root1->priority > root2->priority) {
    root1->right_son = Merge(root1->right_son, root2);
    if (root1->right_son != nullptr) {
      root1->right_son->parent = root1;
    }
    root1->quantity =
        Quantity(root1->left_son) + Quantity(root1->right_son) + 1;
    return root1;
  }
  root2->left_son = Merge(root1, root2->left_son);
  if (root2->left_son != nullptr) {
    root2->left_son->parent = root2;
  }
  root2->quantity = Quantity(root2->left_son) + Quantity(root2->right_son) + 1;
  return root2;
}

bool Exists(Node* node, int key) {
  if (node == nullptr) {
    return false;
  }
  if (node->key == key) {
    return true;
  }
  if (node->key < key) {
    return Exists(node->right_son, key);
  }
  return Exists(node->left_son, key);
}

void Insert(int key) {
  std::random_device rd;
  std::mt19937 gen(rd());
  int priority = gen() % BIG;
  if (Node::root == nullptr) {
    Node::vector.push_back(
        new Node{key, priority, 1, nullptr, nullptr, nullptr});
    Node::root = Node::vector.back();
    return;
  }
  if (Exists(Node::root, key)) {
    return;
  }
  Node::vector.push_back(new Node{key, priority, 1, nullptr, nullptr, nullptr});
  std::pair<Node*, Node*> pair = Split(Node::root, Node::vector.back()->key);
  Node::root = Merge(Merge(pair.first, Node::vector.back()), pair.second);
}

void Delete(int key) {
  std::pair<Node*, Node*> pair = Split(Node::root, key);
  pair.second = Split(pair.second, key + 1).second;
  Node::root = Merge(pair.first, pair.second);
}

Node* Find(Node* node, int key) {
  if (node->key == key) {
    return node;
  }
  if (node->key < key) {
    return (node->right_son == nullptr) ? node : Find(node->right_son, key);
  }
  return (node->left_son == nullptr) ? node : Find(node->left_son, key);
}

bool IsLeftSon(Node* node) {
  if (node->parent == nullptr) {
    return false;
  }
  return node == node->parent->left_son;
}

bool IsRightSon(Node* node) {
  if (node->parent == nullptr) {
    return false;
  }
  return node == node->parent->right_son;
}

int Next(int key) {
  Node* node = Find(Node::root, key);
  if (node->key > key) {
    return node->key;
  }
  Node* right_son = node->right_son;
  if (right_son != nullptr) {
    while (right_son->left_son != nullptr) {
      right_son = right_son->left_son;
    }
    return right_son->key;
  }
  while (IsRightSon(node)) {
    node = node->parent;
  }
  if (IsLeftSon(node)) {
    return node->parent->key;
  }
  return -1;
}

int Previous(int key) {
  Node* node = Find(Node::root, key);
  if (node->key < key) {
    return node->key;
  }
  Node* left_son = node->left_son;
  if (left_son != nullptr) {
    while (left_son->right_son != nullptr) {
      left_son = left_son->right_son;
    }
    return left_son->key;
  }
  while (IsLeftSon(node)) {
    node = node->parent;
  }
  if (IsRightSon(node)) {
    return node->parent->key;
  }
  return -1;
}

int OrdinalStatistics(Node* root, int number) {
  if (root == nullptr) {
    return INT_MIN;
  }
  if (Quantity(root->left_son) == number) {
    return root->key;
  }
  if (Quantity(root->left_son) < number) {
    return OrdinalStatistics(root->right_son,
                             number - Quantity(root->left_son) - 1);
  }
  return OrdinalStatistics(root->left_son, number);
}

void Input() {
  std::string command;
  int value;
  std::cin >> command >> value;
  if (command == "insert") {
    Insert(value);
    return;
  }
  if (command == "delete" && Exists(Node::root, value)) {
    Delete(value);
    return;
  }
  if (command == "exists") {
    std::cout << ((Exists(Node::root, value)) ? "true\n" : "false\n");
    return;
  }
  if (command == "next") {
    int answer = Next(value);
    if (answer == -1) {
      std::cout << "none\n";
      return;
    }
    std::cout << answer << '\n';
    return;
  }
  if (command == "prev") {
    int answer = Previous(value);
    if (answer == -1) {
      std::cout << "none\n";
      return;
    }
    std::cout << answer << '\n';
    return;
  }
  if (command == "kth") {
    int answer = OrdinalStatistics(Node::root, value);
    if (answer == INT_MIN) {
      std::cout << "none\n";
      return;
    }
    std::cout << answer << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  while (!std::cin.eof()) {
    Input();
  }
  for (Node* node : Node::vector) {
    delete node;
  }
}