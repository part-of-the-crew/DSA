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


long int findMax(const std::vector<std::pair<long int, long int>> &v, int Sack) {
    long int sum = 0;
    for (const auto& [c, m] : v){
        if (m < Sack){
            Sack -= m;
            sum += m * c;
        } else if (m > Sack){
            sum += Sack * c;
            break;
        } else 
            break;
    }
    return sum;
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
    int Sack;
	std::cin >> Sack >> N;
    std::vector<std::pair<long int, long int>> v(N);

	for (int i = 0; i < N; ++i)
    {
        long int c, m;
        std::cin >> c >> m;
        v[i] = {c, m};
    }

    std::sort(v.begin(), v.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.first > b.first;
    });
    
    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    if (Sack == 0 ){
        print(0);
        return 0;
    }
    //print(std::numeric_limits<long int>::max());
    print(findMax(v, Sack));

    return 0;
}

