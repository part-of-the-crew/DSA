#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>

#include <stack>
#include <utility>
//#include <numeric>
/*
std::tuple <Node*, Node*> search_smallest(Node* root) {
    Node* parent = nullptr;
    Node* current = root;
    while (current->left != nullptr) {
      parent = current;
      current = current->left;
    }
    if (parent != nullptr)
        parent->left = nullptr;
    return {parent, current};
}

std::tuple <Node*, Node*> search_biggest(Node* root) {
    Node* parent = nullptr;
    Node* current = root;
    while (current->right != nullptr) {
      parent = current;
      current = current->right;
    }
    if (parent != nullptr)
        parent->right = nullptr;
    return {parent, current};
}

std::tuple <Node*, Node*> search(Node* root, const int key) {
    Node* parent = nullptr;
    Node* current = root;
    while (current != nullptr) {
      if (key == current->value) {
          if (parent != nullptr)
              parent->left = nullptr;
          return {parent, current};
      } 
      parent = current;
      if (key < current->value) {
          current = current->left;
      } else if (key > current->value) {
          current = current->right;
      }
    }
    return {nullptr, nullptr};
}
*/

Node** search(Node* current, const int key) {
    Node** parent = nullptr;
    while (current != nullptr) {
      if (key == current->value) {
          return parent;
      }
      if (key < current->value) {
          parent = &current->left;
          current = current->left;
      } else if (key > current->value) {
          parent = &current->right;
          current = current->right;
      }
    }
    return nullptr;
}
Node** search_smallest(Node* current) {
    Node** parent = nullptr;
    while (current->left != nullptr) {
      parent = &current->left;
      current = current->left;
    }
    return parent;
}

Node** search_biggest(Node* current) {
    Node** parent = nullptr;
    while (current->right != nullptr) {
      parent = &current->right;
      current = current->right;
    }
    return parent;
}

Node* remove(Node* root, int key) {
    auto parent = search(root, key);
    if (parent == nullptr) {
        return root;
    }
    Node **found = nullptr;

    if ((*parent)->right != nullptr) {
      found = search_smallest((*parent)->right);
    }

    if (found == nullptr && (*parent)->left != nullptr){
      found = search_biggest((*parent)->left);
    }

    parent = found;

    if (found == nullptr) {
        return root;
    }
    return root;
}

#ifndef REMOTE_JUDGE
void test() {
  {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    auto parent = search(&node2, 2);
    assert(parent == &node2.left);
    assert(*parent == &node1);
  }
/*
  {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    auto [parent, newHead] = search(&node2, 4);
    assert(newHead == nullptr);
  }


  */
  
  {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
  }
  
}

int main() {
  test();
}
#endif