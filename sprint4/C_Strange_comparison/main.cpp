#include <iostream>
#include <string>
#include <ranges>
#include <map>
#include <set>
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

/*
  for (auto l: letters)
  {
    std::cout << l.first << " " << l.second << std::endl;
  }
*/

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::string s1, s2;
	std::cin >> s1 >> s2;
  //print(s1.length()); //print(s2);
	std::map <char, char> letters;
	std::set <char> repetative_letters;

  if (s1.size() != s2.size())
  {
    print ("NO");
    return 0;
  }

  if (s1 == s2)
  {
    print ("YES");
    return 0;
  }

  for (size_t i = 0; i < s1.length(); i++) 
  {
    if (letters.find(s1.at(i)) == letters.end())
    {
      letters.insert({s1.at(i), s2.at(i)});
      if (repetative_letters.find(s2.at(i)) ==  repetative_letters.end())
        repetative_letters.insert(s2.at(i));
      else
      {
        print ("NO");
        return 0;
      }
    }
    else if (letters.find(s1.at(i))->second != s2.at(i))
    {
      print ("NO");
      return 0;
    }
  }


  print ("YES");
  return 0;
}
