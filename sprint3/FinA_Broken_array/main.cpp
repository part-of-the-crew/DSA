//https://contest.yandex.ru/contest/23815/run-report/117800463/
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

Time complexity:
O(log2(n)), where n is the number of elements of sequence.

-- SPACE COMPLEXITY --

Space comlexity:
O(1), when it comes to allocated space by programmer,
and 
O(log2(n)), where n is the number of elements of sequence,
when it comes to allocated space on the stack related to the number of recursion calls
*/

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>


#ifndef MYBUILD
  #include "solution.h"
#endif //MYBUILD

template<typename T>
concept BasicString = std::is_same_v<T, std::basic_string<typename T::value_type>>;

template<typename T>
concept StringLike = BasicString<T> || std::is_convertible_v<T, std::string>;

template<typename T>
concept BasicStringDerived = std::derived_from<T, std::basic_string<typename T::value_type>>;

template<typename T>
concept range = std::is_class_v<T>;// && !std::ranges::range<std::string>;

template <range C>
void print(const C& s) {
    for (const auto& e : s)
        std::cout << e << " ";
    std::cout << std::endl;
}

template <typename C> 
void print(const C& s) {
    std::cout << s << " ";
    std::cout << std::endl;
}


int search(const std::vector<int>& vec, int begin, int ende, int k)
{
  //base case
  if(begin >= ende)
    return -1;

  int mid = (begin + ende) / 2;

  //base case
  if(vec.at(mid) == k)
    return mid;

  //recursive case consideration
  if(vec.at(begin) < vec.at(mid))
  {
    if(vec.at(begin) <= k && k < vec.at(mid))
      return search(vec, begin, mid, k);

    return search(vec, mid + 1, ende, k);
  } else {
    if(vec.at(mid) <= k && k < vec.at(begin))
      return search(vec, mid + 1, ende, k);

    return search(vec, begin, mid, k);
  }
}

//wrapper function for searching
int broken_search(const std::vector<int>& vec, int k) {
  return search(vec, 0, vec.size(), k);
}

#ifdef MYBUILD
int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, k;
	std::cin >> N >> k;

	std::vector <int> v(N);

	for (int i = 0; i < N; ++i)
    std::cin >> v.at(i);


  print(broken_search (v, k));
  return 0;
}
#endif // MYBUILD