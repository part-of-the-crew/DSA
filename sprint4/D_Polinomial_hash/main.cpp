#include <iostream>
#include <string>
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


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

  int a, m;
	std::string s;
	std::cin >> a >> m >> s;

  int res = 0;
  for (size_t i = 0; i < s.length(); i++)
  {
    res = (res * a + s.at(i))%m;
  }
	
  print (res);
  return 0;
}
