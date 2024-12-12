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

	int n; //number of gold
    int m; //capacity
	std::cin >> n >> m;
    std::vector<int> cost(n + 1);  
    std::cin.ignore();
	for (int i = 1; i <= n; ++i){
        std::cin >> cost[i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));  

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = std::max(dp[i - 1][j], (j - cost[i]) < 0 ? 0: dp[i - 1][j - cost[i]] + cost[i]);
        }
    }
    //for (const auto &v: dp)
    //    print(v);

    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }


    print(dp[n][m]);
    return 0;
}
