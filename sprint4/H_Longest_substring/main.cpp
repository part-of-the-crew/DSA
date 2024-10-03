#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <limits>  // For numeric limits

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

using std::map, std::string;
using std::vector, std::string;
using std::cin, std::cout, std::endl;
using std::pair;

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

  string str;
  std::getline(std::cin, str);
  // pair <last_pos, distance>
  map <char, int> letters;

  int max_distance = 0;
  int current_distance = 0;
  int current_max_pos = 0;
  int jump_point = 0;

	for (int i = 0; i < str.length(); i++)
  {
    
    auto it = letters.find(str[i]);
    if (it != letters.end())
    {
      i = std::max (jump_point, it->second);
      jump_point = i;
      //clear letters
      letters.clear();
      letters[str[i]] = i + 1;
      max_distance = std::max(current_distance, max_distance);
      current_distance = 0;
    } else {
      letters[str[i]] = i + 1;
    }
    current_distance++;

  }

  print (std::max(current_distance, max_distance));
  return 0;
}
