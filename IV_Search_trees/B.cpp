#include <iostream>
#include <vector>
#define DEDUCTION 1000000000

struct Node {
  int key;
  int depth;
  Node* parent;
  Node* left_son;
  Node* right_son;
  Node() = default;
  Node(int key, int depth, Node* parent, Node* left_son, Node* right_son)
      : key(key),
        depth(depth),
        parent(parent),
        left_son(left_son),
        right_son(right_son) {}
  inline static std::vector<Node*> vector;
  inline static Node* root;
};

int Max(int x1, int x2) { return (x1 > x2) ? x1 : x2; }

int Depth(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->depth;
}

void LeftRotate(Node* root, Node* new_root) {
  Node* tree_b = new_root->right_son;
  if (root->parent != nullptr) {
    new_root->parent = root->parent;
    if (root->parent->right_son == root) {
      root->parent->right_son = new_root;
    } else {
      root->parent->left_son = new_root;
    }
  } else {
    new_root->parent = nullptr;
    Node::root = new_root;
  }
  new_root->right_son = root;
  root->parent = new_root;
  root->left_son = tree_b;
  if (tree_b != nullptr) {
    tree_b->parent = root;
  }
  root->depth = Max(Depth(root->left_son), Depth(root->right_son)) + 1;
  new_root->depth =
      Max(Depth(new_root->left_son), Depth(new_root->right_son)) + 1;
}

void RightRotate(Node* root, Node* new_root) {
  Node* tree_b = new_root->left_son;
  if (root->parent != nullptr) {
    new_root->parent = root->parent;
    if (root->parent->right_son == root) {
      root->parent->right_son = new_root;
    } else {
      root->parent->left_son = new_root;
    }
  } else {
    new_root->parent = nullptr;
    Node::root = new_root;
  }
  new_root->left_son = root;
  root->parent = new_root;
  root->right_son = tree_b;
  if (tree_b != nullptr) {
    tree_b->parent = root;
  }
  root->depth = Max(Depth(root->left_son), Depth(root->right_son)) + 1;
  new_root->depth =
      Max(Depth(new_root->left_son), Depth(new_root->right_son)) + 1;
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

void Balance(Node* node) {
  if (Depth(node->left_son) - Depth(node->right_son) == 2) {
    if (Depth(node->left_son->left_son) - Depth(node->left_son->right_son) >=
        0) {
      LeftRotate(node, node->left_son);
    } else {
      RightRotate(node->left_son, node->left_son->right_son);
      LeftRotate(node, node->left_son);
    }
  } else if (Depth(node->left_son) - Depth(node->right_son) == -2) {
    if (Depth(node->right_son->left_son) - Depth(node->right_son->right_son) <=
        0) {
      RightRotate(node, node->right_son);
    } else {
      LeftRotate(node->right_son, node->right_son->left_son);
      RightRotate(node, node->right_son);
    }
  }
  if (node->parent != nullptr) {
    Balance(node->parent);
  }
}

void Insert(int key) {
  Node* node = Find(Node::root, key);
  if (node->key == key) {
    return;
  }
  Node::vector.push_back(new Node{key, 1, node, nullptr, nullptr});
  ((key < node->key) ? node->left_son : node->right_son) = Node::vector.back();
  Node* ptr = node;
  do {
    if (ptr->depth == Max(Depth(ptr->left_son), Depth(ptr->right_son)) + 1) {
      break;
    }
    ptr->depth = Max(Depth(ptr->left_son), Depth(ptr->right_son)) + 1;
    ptr = ptr->parent;
  } while (ptr != nullptr);
  Balance(node);
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
  if (node->key >= key) {
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

int main() {
  int quantity;
  std::cin >> quantity;
  int ii = 1;
  char command;
  int key;
  int previous_answer = 0;
  std::cin >> command >> key;
  while (command == '?') {
    ++ii;
    std::cout << -1 << '\n';
    previous_answer = -1;
    std::cin >> command >> key;
  }
  Node::root = new Node{(key + previous_answer) % DEDUCTION, 1, nullptr,
                        nullptr, nullptr};
  previous_answer = 0;
  Node::vector.push_back(Node::root);
  for (; ii < quantity; ++ii) {
    std::cin >> command >> key;
    if (command == '?') {
      previous_answer = Next(key);
      std::cout << previous_answer << '\n';
      continue;
    }
    Insert((key + previous_answer) % DEDUCTION);
    previous_answer = 0;
  }
  for (Node* node : Node::vector) {
    delete node;
  }
  return 0;
}