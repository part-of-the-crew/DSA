#include <iostream>
#include <string>
#include <string_view>
#include <ranges>
#include <vector>
#include <type_traits>
#include <queue>
#include <algorithm>


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


std::vector<std::string_view> SplitIntoWordsView(std::string_view str) {
    std::vector<std::string_view> result;
    str.remove_prefix(std::min(str.find_first_not_of(" "), str.size()));
    
    while (!str.empty()) {
        // тут выполнен инвариант: str не начинается с пробела
        int64_t space = str.find(' ');

        // здесь можно избавиться от проверки на равенство npos
        // если space == npos, метод substr ограничит возвращаемый string_view концом строки
        result.push_back(str.substr(0, space));
        str.remove_prefix(std::min(str.find_first_not_of(" ", space), str.size()));
    }

    return result;
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::string s;
	std::getline(std::cin, s);
    std::vector<std::string_view> v = SplitIntoWordsView(s);

    std::reverse(v.begin(), v.end());
    print(v);

    return 0;
}

