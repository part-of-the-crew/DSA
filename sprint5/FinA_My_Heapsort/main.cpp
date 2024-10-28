//https://contest.yandex.ru/contest/24810/run-report/122808168/
/*
-- WORKING PRINCIPLE --

I consequently put each element in a heap and then call sifting up to make sure that the parent is the 
less than its children.

After that, I pop the first element off the heap and then call sifting down to restore the heap properties.
I insert that element in the result vector.

This way we get the competitors in descending order of their scores.

-- PROOF OF CORRECTNESS --

After forming and sifting the heap up we have the smallest element on top of the heap.
After popping the smallest element off the heap sifting down will be performed to ensure that
the smallest element is on top of the heap until there are no more elements in the heap.

-- TIME COMPLEXITY --

Time complexity in the worst case:
  O(n*log(n)), where n is the number of competitors.
That's because for each competitor we need to put and sift.

-- SPACE COMPLEXITY --

Space complexity:
O(n), where n is the number of competitors.
That's because I use space to store the results.
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
void heap_add(std::vector<T>& heap, T key) {
    heap.push_back(key);
    int index = heap.size() - 1;
    siftUp(heap, index);
}

template <typename T> 
int siftUp(std::vector<T>& heap, int index) {
    while (index != 1){
        int parent_index = index / 2;
        if (heap[parent_index] < heap[index]) {
            return index;
        }
        std::swap(heap[parent_index], heap[index]);
        index = parent_index;
    }
    return index;
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

    // Вставим в неё по одному все элементы массива, сохраняя свойства кучи.
    for (const auto& item : v) {
        heap_add(heap, item);   // код для heap_add можно посмотреть в прошлом уроке
    }

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
