#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <numeric>

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
    if (!s.empty())
        std::cout << std::endl;
}


template <typename C> 
void print(const C& s) {
    std::cout << s << "";
    std::cout << std::endl;
}

template <typename C> 
C min(const C& s1, const C& s2, const C& s3) {
    return std::min(std::min(s1, s2), s3);
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::string s, t;

    std::getline(std::cin,s);
    std::getline(std::cin,t);

    std::cin.ignore();

    std::vector<int > prev(t.size() + 1);

    //fill the vector with iota
    std::iota(prev.begin(), prev.end(), 0);
    

    for (int i = 1; i <= static_cast<int>(s.size()); ++i) {
        std::vector<int > cur (t.size() + 1, 0);
        for (int j = 0; j <= static_cast<int>(t.size()); ++j) {

            if (j == 0){
                cur[0] = i;
                continue;
            }
            if (s[i - 1] == t[j - 1]){
                cur[j] =  prev[j - 1];
            } else {
                cur[j] =  1 + min(prev[j - 1], 
                                  prev[j],
                                  cur[j - 1]);
            }
        }
        std::swap(prev, cur);
    }

    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    print(prev.back());
    return 0;
}
