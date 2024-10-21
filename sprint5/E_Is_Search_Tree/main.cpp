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
#include <iostream>
#include <cassert>
#include <stack>
using namespace std;


bool Solution(const Node* root) {
    // Your code
    // “ヽ(´▽｀)ノ”
    std::stack<const Node*> st{{root}};
    std::stack<std::pair <int, int>> limits;
    //st.push(root);
    limits.push({numeric_limits<int>::min(), numeric_limits<int>::max()});
    while (!st.empty()) {
      const Node* current = st.top();
      st.pop();
      pair diap{limits.top()};
      limits.pop();

      if (diap.first >= current->value || diap.second <= current->value)
          return false;

      if (current->left){
        st.push(current->left);
        limits.push({diap.first, min(diap.second, current->value)});
      }
      if (current->right){
        st.push(current->right);
        limits.push({max(diap.first, current->value), diap.second});
      }
    }
    return true;
}


#ifndef REMOTE_JUDGE
void test() {
    {
      Node node1({1, nullptr, nullptr});
      assert(Solution(&node1));
    }
    {
      Node node1({1, nullptr, nullptr});
      //Node node2({4, nullptr, nullptr});
      //Node node3({3, &node1, &node2});
      Node node3({3, &node1, nullptr});
      assert(Solution(&node3));
    }

    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node6({5, &node3, &node4});
      assert(!Solution(&node6));
    }
}


int main() {
  test();
}
#endif