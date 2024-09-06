#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

#ifndef REMOTE_JUDGE
#include <cassert>
#include <string>

struct Node {  
    std::string value;  
    Node* next;  
    //Node(const std::string &value, Node* next) : value(value), next(next) {
    //Node(const std::string &value) : value(value), next(nullptr) {
    //}
    Node(const std::string &value, Node* next) : value(value), next(next) {}
};
#endif

Node *getNodeByIndex(Node *node, int index) {
    while (index > 0) {
        node = node->next;
        if (node == nullptr)
          return nullptr;  // Out of bounds
        index--;
    }
    return node;
}
Node *getNodeByValue(Node *node, std::string value) {
    while (value != node->value) {
        node = node->next;
        if (node == nullptr)
          return nullptr;  // Out of bounds
    }
    return node;
}
int solution(Node* head, const std::string& elem) {
    int index = 0;
    while (elem != head->value) {
        head = head->next;
        if (head == nullptr)
          return -1;  // Out of bounds
        index++;
    }
    return index;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node3("node3", nullptr);
    Node node2("node2", &node3);
    Node node1("node1", &node2);
    Node node0("node0", &node1);
    int idx = solution(&node0, "node2");
    assert(idx == 2);
}

int main() {
    test();
}
#endif
