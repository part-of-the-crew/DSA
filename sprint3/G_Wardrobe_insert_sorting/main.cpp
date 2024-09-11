#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>

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
int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;

	std::vector <int> v(N), temp(3);

	for (int i = 0; i < N; ++i)
    std::cin >> v.at(i);

  for (const auto &i : v)
    ++temp[i];

  std::size_t j = 0;
  for (std::size_t i = 0; i < temp.size(); i++)
  {
    for (; j < v.size(); j++)
    {
      if (temp.at(i) == 0)
        break;
      v.at(j) = i;
      temp.at(i)--;
    }
  }

  print(v);
  return 0;
}
