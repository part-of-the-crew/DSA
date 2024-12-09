#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <queue>
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

	int n;
    int k;
	std::cin >> n >> k;
    std::vector <long int> v(n + 1);
    const int modulo = 1'000'000'007;
    v[0] = 0;
    v[1] = 1;
    //v[2] = 1;
    //v[3] = 2;
    //v[4] = 3;
    //v[5] = 5;
	for (int i = 2; i <= n; ++i){
        for (int j = 0; j < std::min(k, i); ++j){
            v[i] += v[i - 1 - j];
            v[i] %= modulo;
        }
    }

    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    print(v[n]);
    return 0;
}
