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

	int N, M;
	std::cin >> N >> M;
  std::cin.ignore();
	std::map <int, std::vector<int>> gr;

	for (int i = 0; i < M; ++i)
  {
    int a, b;
    std::cin >> a >> b;
    gr[a].push_back(b);
    std::cin.ignore();
  }

  //display strings in order values
  for(auto i = 1; i <= N; ++i)
  {
    auto it = gr.find(i);
    if (it != gr.end()){
      std::cout << it->second.size() << " ";
      for (const auto& e : it->second)
        std::cout << e << " ";
      std::cout << std::endl;
    } else
      std::cout << "0" << std::endl;
  }


  return 0;
}
