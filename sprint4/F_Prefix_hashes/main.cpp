#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

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


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

  int a, m;
	std::string s;
	std::cin >> a >> m >> s;

	int N;
	std::cin >> N;
  std::cin.ignore();
	std::vector <std::pair <int, int>> ind(N);

	for (int i = 0; i < N; ++i)
  {
    std::cin >> (ind.begin() + i)->first >> (ind.begin() + i)->second;
  }
  
  int res = 0;
  for (size_t i = 0, j = s.length() - 1; i < s.length(); i++, j--)
  {
    res = (res * a + static_cast<int>(s.at(i)))%m;
  }
	
  print (res);
  return 0;
}
