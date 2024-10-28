#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

void sift_up(std::vector<int>& heap, int index) {
    if (index == 1) {
        return;
    }

    int parent_index = index / 2;
    if (heap[parent_index] < heap[index]) {
        std::swap(heap[parent_index], heap[index]);
        sift_up(heap, parent_index);
    }
}


void heap_add(std::vector<int>& heap, int key) {
    heap.push_back(key);
    int index = heap.size() - 1;
    siftUp(heap, index);
}

int siftUp(std::vector<int>& heap, int index) {
    while (index != 1){
        int parent_index = index / 2;
        if (heap[parent_index] >= heap[index]) {
            return index;
        }
        std::swap(heap[parent_index], heap[index]);
        index = parent_index;
    }
    return index;
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 6, 8, 3, 15, 7};
    assert(siftUp(sample, 5) == 1);
}


int main() {
    test();
}
#endif