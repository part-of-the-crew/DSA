#include <iostream>
#include <string>
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


int findMax(const std::vector<int> &v) {
    int max = 0;
    int hand = 0;
    //int cost = 0;
    bool shares = false;
    for (size_t i = 0; i < v.size(); i++) {
        if (shares && i == (v.size() - 1)){
            return max + hand - v[i];
        }

        if (shares && v[i] > v[i + 1]){
            shares = false;
            max += hand - v[i];
            hand = 0;
            continue;
        }

        if (!shares && v[i] < v[i + 1]){
            shares = true;
            hand = v[i];
            continue;
        }
    }
    
    return max;
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;
    std::vector<int> v(N);

	for (int i = 0; i < N; ++i)
    {
        std::cin >> v[i];
    }
    
    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    if (N == 1 || N == 0){
        print(0);
        return 0;
    }

    print(0 - findMax(v));

    return 0;
}

