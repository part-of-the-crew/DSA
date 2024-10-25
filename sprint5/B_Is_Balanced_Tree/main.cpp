#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <cassert>

using namespace std;

int recursion (const Node* root, int h)
{
  if (root == nullptr) return h;
  return max(recursion(root->left, h+1), recursion(root->right, h+1));
}

bool Solution(const Node* root) {
    
    if (root == nullptr){
        return true;
    }
    if (root->left != nullptr && root->right != nullptr)
    {
        return Solution(root->left) && Solution(root->right);
    } else {
      int h1 = recursion(root->left, 0);
      int h2 = recursion(root->right, 0);

      if (abs(h1 - h2) > 1){
          return false;
      }
    }

    return true;
} 

#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({10, nullptr, nullptr});
    Node node5({2, &node3, &node4});
    assert(Solution(&node5));
}

int main() {
  test();
}
#endif