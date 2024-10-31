#ifndef REMOTE_JUDGE
struct Node {  
  Node* left;  
  Node* right;
  int value;
  int size;
};
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>
#include <utility>

int getSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}
//split the bst
std::pair<Node*, Node*> split1(Node* root, int k) {//4
    if (root == nullptr)
      return {nullptr, nullptr};

    if (getSize(root->left) >= k) {
      std::pair<Node*, Node*> temp = split(root->left, k);
      root->left = temp.second;
      temp.second = root;
      root->size = getSize(root->left) + getSize(root) + getSize(root->right);
      return temp;

    } else {
      std::pair<Node*, Node*> temp = split(root->right, k - getSize(root->left) - 1);
      root->right = temp.first;
      temp.first = root;
      root->size = getSize(root->left) + getSize(root) + getSize(root->right);
      return temp;
    }
}
std::pair<Node*, Node*> split(Node* root, int k) {
    if (root == nullptr)
        return {nullptr, nullptr};

    if (getSize(root->left) >= k) {
        // Split the left subtree if we need more nodes on the left
        std::pair<Node*, Node*> temp = split(root->left, k);
        root->left = temp.second;
        // Update root's size after altering left child
        root->size = getSize(root->left) + getSize(root->right) + 1;
        return {temp.first, root};

    } else {
        // Adjust k to reflect nodes needed from the right subtree
        std::pair<Node*, Node*> temp = split(root->right, k - getSize(root->left) - 1);
        root->right = temp.first;
        // Update root's size after altering right child
        root->size = getSize(root->left) + getSize(root->right) + 1;
        return {root, temp.second};
    }
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 3, 1});
    Node node2({nullptr, &node1, 2, 2});
    Node node3({nullptr, nullptr, 8, 1});
    Node node4({nullptr, nullptr, 11, 1});
    Node node5({&node3, &node4, 10, 3});
    Node node6({&node2, &node5, 5, 6});
    std::pair<Node*, Node*> res = split(&node6, 4);
    assert(res.first->size == 4);
    assert(res.second->size == 2);
}


int main() {
  test();
}
#endif