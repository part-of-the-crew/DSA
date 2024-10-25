/*
https://contest.yandex.ru/contest/24810/run-report/122277987/
-- WORKING PRINCIPLE --

1. Check some corner cases related to the root
2. Search and return pointer to the parental pointer to the replaced Node
3. Search and return pointer to the parental pointer to the replacing Node
   In the left or right node we are searching depends on whether they exist
   but start with the right one.
4. Replace the Node and update the childish pointers
5. Disconnect the replacing Node from parent if it exists

-- PROOF OF CORRECTNESS --

 Invariants to keep eye on:
 1. After deleting any node BST must remain BST
    This is ensured by the fact that we get the smallest replacement node from the right
    or the biggest from left. This gives us the node where left side is smaller than its value
    and right side is bigger than its value.
    After deleting and replacing the hanging brances of deleted node connect
    to the new node remainig the tree binary search tree.
 2. BST must not be changed when the node to replace is not found
    Unchanged root is returned in this case.
 3. Creating a new node is not allowed
    No node is created during program execution


-- TIME COMPLEXITY --
  O(H), 
  where H is the hight of the tree.
  because searching the replacing and replaced Nodes is O(H) in the worst case

-- SPACE COMPLEXITY --
  O(1)
  No heap allocation nor recursion
*/

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
Node** search_smallest(Node** current) {
    Node** parent = current;
    while ((*current)->left != nullptr) {
      parent = &(*current)->left;
      current = &(*current)->left;
    }
    return parent;
}

Node** search_biggest(Node** current) {
    Node** parent = current;
    while ((*current)->right != nullptr) {
      parent = &(*current)->right;
      current = &(*current)->right;
    }
    return parent;
}

Node* remove(Node* root, int key) {
    if (root == nullptr)
      return root;
  
    if (root->value == key && !root->left && !root->right)
        return nullptr;

// Find the node to remove and its parent
    Node **parent = nullptr;
    if (root->value == key)
      parent = &root;
    else
      parent = search(root, key);

// Node to be deleted is not found
    if (parent == nullptr)
        return root;

    Node **found = nullptr;
// search Node to replace
    if ((*parent)->right != nullptr) {
      found = search_smallest(&(*parent)->right);
    } else if ((*parent)->left != nullptr) {
      found = search_biggest(&(*parent)->left);
    } else {
// Replacing Node not found
      *parent = nullptr;
      return root;
    }

// Connect children to the replacing node 
    Node *left_child = (*parent)->left;
    Node *right_child = (*parent)->right;

    if (left_child != (*found))
      (*found)->left = left_child;

    if (right_child != (*found))
      (*found)->right = right_child;

// Replace node
    if (key != root->value)
      *parent = *found;
// Get new root 
    else 
      root = *found;

// disconnect replacing node
    *found = nullptr;

    return root;
}

#ifndef REMOTE_JUDGE
void test() {
  /*
  {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    auto parent = search(&node2, 2);
    assert(parent == &node2.left);
    assert(*parent == &node1);
  }
  */
/*
  {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    auto [parent, newHead] = search(&node2, 4);
    assert(newHead == nullptr);
  }
  */
  {
    Node node1({nullptr, nullptr, 1});
    Node node2({nullptr, &node1, 2});
    Node* newHead = remove(&node2, 2);
    assert(newHead->value == 1);
    assert(newHead == &node1);
  }

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