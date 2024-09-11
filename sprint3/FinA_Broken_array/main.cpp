#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <ranges>
#include <vector>
#include <iostream>
#include <type_traits>
#include <cassert>

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
/*
void print(const std::vector <int> &v) {
  for (const auto i : v) 
    std::cout << i << " ";
  std::cout << std::endl;
}
void print(const std::vector <std::string> &v) {
  for (const auto &i : v) 
    std::cout << i << " ";
  std::cout << std::endl;
}

void print(const int v) {
    std::cout << v;
  std::cout << std::endl;
}
void print(std::string s) {
    std::cout << s;
  std::cout << std::endl;
}
void print(const std::vector <std::pair<int, int>> &v) {
  for (const auto &i : v) 
    std::cout << i.first << " " << i.second << std::endl;
}
*/

/*
int broken_search(const std::vector<int>& vec, int k) {
  auto temp = find(vec.begin(), vec.end(), k);
  if(temp == vec.end())
    return -1;
  return temp - vec.begin();
}
*/

int search(const std::vector<int>& vec, int begin, int ende, int k)
{
  if(begin >= ende)
    return -1;

  int mid = (begin + ende) / 2;

  print(mid);

  if(vec.at(mid) == k)
    return mid;

  if(vec.at(begin) == k)
    return begin;

  if(vec.at(begin) < vec.at(mid))
  {
    if(vec.at(begin) < k && k < vec.at(mid))
      return search(vec, begin + 1, mid, k);

    return search(vec, mid + 1, ende, k);
  } else {
    if(vec.at(mid) < k && k < vec.at(ende))
      return search(vec, mid + 1, ende, k);

    return search(vec, begin + 1, mid, k);
  }
}

int broken_search(const std::vector<int>& vec, int k) {
  return search(vec, 0, vec.size(), k);
}



#ifndef MYBUILD
void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}
#endif // MYBUILD

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