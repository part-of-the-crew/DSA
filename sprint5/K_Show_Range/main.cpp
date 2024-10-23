#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>
#include <stack>

using namespace std;

void print_range(Node* root, int l, int r) {
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

      //if (diap.first > current->value || diap.second < current->value)
      //    return false;
      if (current->value >= l && current->value <= r)
          cout << current->value << " ";
      if (current->left){
        st.push(current->left);
        limits.push({diap.first, min(diap.second, current->value)});
      }
      if (current->right){
        st.push(current->right);
        limits.push({max(diap.first, current->value), diap.second});
      }
    }
    cout << endl;

}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({nullptr, &node1, 1});
    Node node3({nullptr, nullptr, 8});
    Node node4({nullptr, &node3, 8});
    Node node5({&node4, nullptr, 9});
    Node node6({&node5, nullptr, 10});
    Node node7({&node2, &node6, 5});
    print_range(&node7, 2, 8);
    // expected output: 2 5 8 8
}

int main() {
  test();
}
#endif
