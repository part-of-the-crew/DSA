//https://contest.yandex.ru/contest/24810/run-report/123148117/
/*
-- WORKING PRINCIPLE --

1. Check some corner cases related to the root
2. Search and return pointer to the replaced Node using recursion
   In the left or right node we are searching depends on whether they exist
   but start with the left one.
4. Replace the Node

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
  O(n), 
  where n is the number of the nodes.
  because searching the replacing and replaced Nodes is O(n) in the worst case

-- SPACE COMPLEXITY --
  O(1),
  +O(n),
  because the space used by the recursion stack is O(n) in the worst case.
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
#include <iostream>


Node* remove(Node* root, int key) {
    if (root == nullptr) 
        return root;
    if (key < root->value) {
        root->left = remove(root->left, key);
        return root;
    }
    if (key > root->value) {
        root->right = remove(root->right, key);
        return root;
    }

// нашли узел, рассмотреть три варианта: нет потомков, один потомок, два потомка
    if (root->left == nullptr) 
        return root->right;
    if (root->right == nullptr) 
        return root->left;
// внутри узла два потомка, find the smallest node in the right subtree
    Node* node = root->right;
    while (node->left) {
        node = node->left;
    }
    node->left = root->left;
    root = root->right;
    return root;
}


#ifndef REMOTE_JUDGE
void test() {

  {
    Node node1({nullptr, nullptr, 1});
    Node node2({&node1, nullptr, 2});
    Node* newHead = remove(&node2, 1);
    assert(newHead->value == 2);
    assert(newHead->left == nullptr);
  }

  {
    Node node1({nullptr, nullptr, 3});
    Node node2({nullptr, &node1, 2});
    Node* newHead = remove(&node2, 2);
    assert(newHead->value == 3);
    //assert(newHead == &node1);
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
