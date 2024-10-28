#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

int pop_max(std::vector<int>& heap) {
    int result = heap[1];
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    siftDown(heap, 1);
    return result;
}

int siftDown(std::vector<int>& heap, int index) {

  while (1){

    size_t left = 2 * index;
    size_t right = 2 * index + 1;

    // Нет дочерних узлов
    if (left >= heap.size()) {
        return index;
    }

    // проверяем, что есть оба дочерних узла и какой больше
    size_t index_largest = left;
    if (right < heap.size() && heap[right] > heap[left]) {
        index_largest = right; 
    }

    if (heap[index_largest] <= heap[index]) {
      return index;
    }
    std::swap(heap[index], heap[index_largest]);
    index = index_largest;
  }
}



#ifndef REMOTE_JUDGE
void test() {
    {
      std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
      assert(siftDown(sample, 2) == 5);
      assert(siftDown(sample, 2) == 2);
    }
    {
      std::vector<int> sample = {-1, 1, 12};
      assert(siftDown(sample, 1) == 2);
      assert(siftDown(sample, 2) == 2);
    }
    {
      std::vector<int> sample = {-1, 1, 12, 13};
      assert(siftDown(sample, 1) == 3);
      assert(siftDown(sample, 3) == 3);
    }
    {
      std::vector<int> sample = {-1, 1};
      assert(siftDown(sample, 1) == 1);
    }
}

int main() {
  test();
}
#endif