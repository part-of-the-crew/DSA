//https://contest.yandex.ru/contest/22781/run-report/117427415/
/*

-- WORKING PRINCIPLE --

It is allocated a vector with a predefined size and all operations are performed 
by indexing the vector with overwrapping through the size of the vector.
Since vector with direct indexing is used under the hood complexity of operations is constant.

-- PROOF OF CORRECTNESS --

Delegating given operations to a vector's member functions allows us to be sure that the operations will be executed
perfectly according to the vector specification.
Using the max size of the buffer allows us not to think about overlaying head and tail.

-- TIME COMPLEXITY --

Time complexity depends on the given number of commands:
O(n), where n is the number of commands in the input.

-- SPACE COMPLEXITY --

Space comlexity:
O(m), where m is the given size of the ring buffer.
*/

#include <iostream>
#include <vector>


class Queue {
private:
  std::vector<int> queue;
  int max_n;
  int head = 0;
  int tail = 0;
  int size = 0;
  typedef std::vector<int>::const_iterator const_it;
  const_it cbegin() const { return this->queue.cbegin(); }
public:
  Queue() = delete;
  Queue(int n) : queue(n), max_n(n) {};
  const_it cend() const { return this->queue.cend() + max_n; }

  bool push_back(int x) {
    if ( size == max_n)
      return true;

    queue[tail] = x;
    tail = (tail + 1) % max_n;
    size += 1;
    return false;
  };

  bool push_front(int x) {
    if (size == max_n)
      return true;
    // this faster (60ms)
    //https://contest.yandex.ru/contest/22781/run-report/117427364/
    /*
    if (head == 0) {
      head = max_n - 1;
    } else {
      head -= 1;
    }
    */

    // this slower (80ms)
    //https://contest.yandex.ru/contest/22781/run-report/117427415/
    head = (head + max_n - 1) % max_n;
    queue[head] = x;
    size += 1;
    return false;
  };

  auto pop_front() {
    if (is_empty()) {
      return cend();
    }
    const_it it = cbegin() + head;
    head = (head + 1) % max_n;
    size -= 1;
    return it;
  };

  auto pop_back() {
    if (is_empty()) {
      return cend();
    }
    const_it it;
    if (tail == 0)
      it = cbegin() + max_n - 1;
    else
      it = cbegin() + tail - 1;
    tail = (tail - 1 + max_n) % max_n;
    size -= 1;
    return it;
  };

  bool is_empty() { return size == 0; };

  void print() {
    for (int i = 0; i < size; i++)
      std::cout << queue[(head + i) % max_n] << " ";
    std::cout << std::endl;
  };
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int Qsize, Nop;
  std::cin >> Nop;
  std::cin >> Qsize;

  Queue qu(Qsize);

  for (int i = 0; i < Nop; ++i)
  {
    std::string temp;
    std::cin >> temp;
    if (temp == "push_back")
    {
      int val;
      std::cin >> val;
      if (qu.push_back(val))
        std::cout << "error" << std::endl;
    }
    else if (temp == "push_front")
    {
      int val;
      std::cin >> val;
      if (qu.push_front(val))
        std::cout << "error" << std::endl;
    }
    else if (temp == "pop_back")
    {
      auto it = qu.pop_back();
      if (it == qu.cend())
        std::cout << "error" << std::endl;
      else
        std::cout << *it <<  std::endl;
    }
    else if (temp == "pop_front")
    {
      auto it = qu.pop_front();
      if (it == qu.cend())
        std::cout << "error" << std::endl;
      else
        std::cout << *it <<  std::endl;
    }     

  }
}