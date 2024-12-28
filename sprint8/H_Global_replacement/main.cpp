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


std::vector<int> prefix_function(const std::string& str, const std::string& templ) {
    // Функция возвращает массив длины |s|
    auto s = templ + '#' + str;
    int n = s.length();
    std::vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        int k = pi[i - 1];
        while (k > 0 && s[k] != s[i]) {
            k = pi[k - 1];
        }
        if (s[k] == s[i]) {
            ++k;
        }
        pi[i] = k;
    }
    return pi;
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::string s;
	std::string templ;
	std::string repl;

    std::getline(std::cin, s);
    std::getline(std::cin, templ);
    std::getline(std::cin, repl);

    auto v = prefix_function(s, templ);

    for (int i = static_cast<int>(v.size()) - 1; i >= 0; --i) {

        if (i <= static_cast<int>(templ.size()))
            continue;
        
        if (v[i] == static_cast<int>(templ.size())) {
            s.replace(i - templ.size() - templ.size(), templ.size(), repl);
        }

    }
    //print (v);
    print (s);
    return 0;
}
