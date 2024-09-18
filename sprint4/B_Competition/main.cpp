#include <iostream>
#include <string>
#include <ranges>
#include <map>
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


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;
  std::cin.ignore();
	std::map <std::string, int> strings;

	for (int i = 0; i < N; ++i)
  {
    std::string temp;
    std::getline (std::cin, temp);
    strings.try_emplace(temp, i);
  }

  //display strings in order values
  for(auto i = 0; i < N; ++i)
  {
    for(auto& p : strings)
    {
      if(p.second == i)
      {
        print(p.first);
        break;
      }
    }
  }


  return 0;
}
