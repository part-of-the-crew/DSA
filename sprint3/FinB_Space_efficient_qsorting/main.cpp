//https://contest.yandex.ru/contest/23815/run-report/118008170/
/*
-- WORKING PRINCIPLE --

Find a pivot element in the segment, then sort using the given algorithm, 
where we move pointers towards each other and swap elements until pointers to meet.
Call recursive function for the left and the right parts of the segment and so on 
until each segment has a size of less than two elements.

-- PROOF OF CORRECTNESS --

I don't use additional space for elements. 
Each recursion calls two other the same functions dividing segments into 2 parts.
There is also a basic case for recursion and before sorting I check the size of segments if it is less than two
recursion ends.

-- TIME COMPLEXITY --

Time complexity in the worse case:
  O(n^2), where n is the number of elements of sequence.
Time complexity if the pivot element is successfully selected:
  O(n*log2(n)), where n is the number of elements of sequence.

-- SPACE COMPLEXITY --

Space comlexity:
O(1), because I don`t use space for storing elements.
*/

#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>


template<typename T>
concept BasicString = std::is_same_v<T, std::basic_string<typename T::value_type>>;

template<typename T>
concept StringLike = BasicString<T> || std::is_convertible_v<T, std::string>;

template<typename T>
concept range = std::is_class_v<T> && !StringLike<T>;

template <range C>
void print(const C& s) {
    for (const auto& e : s)
        std::cout << e << " ";
    std::cout << std::endl;
}

template <typename C> 
void print(const C& s) {
    std::cout << s << "";
    std::cout << std::endl;
}

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
  friend bool operator> (const Competitor& lhs, const Competitor& rhs) { return rhs < lhs; };
  friend bool operator<= (const Competitor& lhs, const Competitor& rhs) { return !(lhs > rhs); };
  friend bool operator>= (const Competitor& lhs, const Competitor& rhs) { return !(lhs < rhs); };
};


int sorting(std::vector<Competitor>& array, int left, int right) 
{
  //auto pivot = array[(rand() % (right - left)) + left];
  auto pivot = array[(right + left) / 2];
  while ( left < right)
  {
    while (array[left] < pivot)
    {
      left++;
    }
    while (pivot < array[right - 1])
    {
      right--;
    }
    if (left < right)
    {
      std::swap(array[left], array[right - 1]);
      left++;
      right--;
    }
  }
  return right;
}

void quicksort(std::vector<Competitor>& array, int left, int right) 
{
    //base case
    if(left >= (right - 1))
        return;

    int mid = sorting(array, left, right);
    quicksort(array, left, mid);
    quicksort(array, mid, right);
}


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;

	std::vector <Competitor> v(N);

	for (int i = 0; i < N; ++i)
    std::cin >> v.at(i).name >> v.at(i).solved >> v.at(i).penalty;

  quicksort(v, 0, v.size());

  for (const auto& c: v)
    print(c.name);

  return 0;
}
