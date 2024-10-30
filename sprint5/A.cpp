//https://contest.yandex.ru/contest/24810/run-report/123048069/
/*
-- WORKING PRINCIPLE --

I put element in a heap together and then call sifting down for nodes with children to make sure that the parent is the 
less than its children.

After that, I pop the first element off the heap and then call sifting down to restore the heap properties.
I insert that element in the result vector.

This way we get the competitors in descending order of their scores.

-- PROOF OF CORRECTNESS --

After forming and sifting the heap down we have the smallest element on top of the heap.
After popping the smallest element off the heap sifting down will be performed to ensure that
the smallest element is on top of the heap until there are no more elements in the heap.

-- TIME COMPLEXITY --

Time complexity in the worst case:
  O(n*log(n)), where n is the number of competitors.
That's because for each competitor needs to be extracted and sift down.

-- SPACE COMPLEXITY --

Space complexity:
O(n), where n is the number of competitors.
That's because I use space to store the heap(n) and the results(n).
I don't use recursion, so I don't use space for it.
*/

#include <iostream>
#include <string>
#include <vector>

struct Competitor
{
  std::string name;
  int solved;
  int penalty;

  //overloading operator <
  friend bool operator< (const Competitor& a, const Competitor& b) {
    if (a.solved == b.solved) {
      if (a.penalty == b.penalty) {
        return a.name < b.name;
      }
      return a.penalty < b.penalty;
    }
    return a.solved > b.solved;
    
  };
  //overloading operator >>
  friend std::istream& operator>> (std::istream& is, Competitor& c) {
    is >> c.name >> c.solved >> c.penalty;
    return is;
  };
  //overloading operator<<
  friend std::ostream& operator<< (std::ostream& os, const Competitor& c) {
    os << c.name;
    return os;
  };

  friend bool operator> (const Competitor& lhs, const Competitor& rhs) { return rhs < lhs; };
  friend bool operator<= (const Competitor& lhs, const Competitor& rhs) { return !(lhs > rhs); };
  friend bool operator>= (const Competitor& lhs, const Competitor& rhs) { return !(lhs < rhs); };
};

template <typename T> 
void buildHeap(std::vector<T>& heap)
{
    for (int i = heap.size() / 2; i >= 1; i--){
        siftDown(heap, i);
    }
}

template <typename T>
T pop_heap(std::vector<T>& heap) {
    T result = heap[1];
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    siftDown(heap, 1);
    return result;
}

template <typename T>
int siftDown(std::vector<T>& heap, int index) {

  while (1){

    size_t left = 2 * index;
    size_t right = 2 * index + 1;

    // Нет дочерних узлов
    if (left >= heap.size()) {
        return index;
    }

    // проверяем, что есть оба дочерних узла и какой больше
    size_t index_chosen = left;
    if (right < heap.size() && heap[right] < heap[left]) {
        index_chosen = right; 
    }

    if (heap[index_chosen] > heap[index]) {
        return index;
    }
    std::swap(heap[index], heap[index_chosen]);
    index = index_chosen;
  }
}

template <typename T> 
std::vector <T> heapsort(const std::vector <T> &v){
    // Создадим пустую бинарную кучу.
    std::vector <T> heap(1);

    // Вставим в неё по одному все элементы массива за линию, сохраняя свойства кучи.
    std::copy(v.begin(), v.end(), std::back_inserter(heap));
    buildHeap(heap);

    // Будем извлекать из неё наиболее приоритетные элементы, удаляя их из кучи.
    std::vector<T> sortedArray;
    while (heap.size() > 1) {
        sortedArray.push_back(pop_heap(heap));
    }
    return sortedArray;
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;
	std::vector <Competitor> v(N);

	for (int i = 0; i < N; ++i)
    std::cin >> v.at(i);

  for (const auto& e: heapsort(v))
    std::cout << e << std::endl;

  return 0;
}
