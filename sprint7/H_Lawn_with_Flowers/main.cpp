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
    int m;
	std::cin >> n >> m;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));  
    std::cin.ignore();
	for (int i = n; i > 0; --i){
        std::string temp;
        std::getline(std::cin, temp);
        for (size_t j = 0; j < temp.size(); ++j){
            dp[i][j + 1] = temp[j] - '0';
        }
    }

    //print dp


    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + dp[i][j];
        }
    }

    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }



    print(dp[n][m]);
    return 0;
}
