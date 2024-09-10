#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
	
/*
template <typename C> void print(const C& s) {
    for (const auto& e : s)
        std::cout << e << " ";
    std::cout << std::endl;
}
*/
template <typename C> void print(const C& s) {
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

	std::string s, t;
	std::getline(std::cin, s);
  std::getline(std::cin, t);

  auto temp_begin = t.begin();
  for (const auto i : s)
  {
    temp_begin = std::find(temp_begin, t.end(), i);
    if (temp_begin == t.end())
    {
      print("False");
      return 0;
    }
    temp_begin++;
  }
  print("True" );
  return 0;
}
