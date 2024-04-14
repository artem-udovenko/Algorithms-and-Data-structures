#include <cstring>
#include <iostream>
#include <vector>

struct Key {
  std::string first;
  std::string sekond;
};

bool operator<(Key key1, Key key2) {
  return strcmp(key1.first.c_str(), key2.first.c_str()) < 0;
}

struct Node {
  Key key;
  int depth;
  Node* parent;
  Node* left_son;
  Node* right_son;
  Node() = default;
  Node(Key key, int depth, Node* parent, Node* left_son, Node* right_son)
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

Node* Find(Node* node, std::string key) {
  if (node->key.first == key) {
    return node;
  }
  if (node->key.first < key) {
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

void Insert(Key key) {
  Node* node = Find(Node::root, key.first);
  if (node->key.first == key.first) {
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int quantity;
  std::cin >> quantity;
  std::string string1;
  std::string string2;
  std::cin >> string1 >> string2;
  Node::root = new Node{Key{string1, string2}, 1, nullptr, nullptr, nullptr};
  Node::vector.push_back(Node::root);
  Insert(Key{string2, string1});
  for (int i = 1; i < quantity; ++i) {
    std::cin >> string1 >> string2;
    Insert(Key{string1, string2});
    Insert(Key{string2, string1});
  }
  int queries;
  std::cin >> queries;
  for (int i = 0; i < queries; ++i) {
    std::string query;
    std::cin >> query;
    Node* node = Find(Node::root, query);
    std::cout << node->key.sekond << '\n';
  }
  for (Node* node : Node::vector) {
    delete node;
  }
}