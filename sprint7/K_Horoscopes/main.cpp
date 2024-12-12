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

	int n; //size of 1
    int m; //size of 2

	std::cin >> n;
    std::vector<int> a(n);  
    std::cin.ignore();
	for (int i = 0; i < n; ++i){
        std::cin >> a[i];
    }
    //std::vector<int> a_r(a.rbegin(), a.rend());

	std::cin >> m;
    std::vector<int> b(m);  
    std::cin.ignore();
	for (int i = 0; i < m; ++i){
        std::cin >> b[i];
    }
    //std::vector<int> b_r(b.rbegin(), b.rend());

    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i > 0 && j > 0 && a[i] == b[j])
                dp[i][j] = dp[i - 1][j - 1];

            if (a[i] == b[j])
                ++dp[i][j];
            else    
                dp[i][j] = std::max(dp[std::max(i - 1, 0)][j], dp[i][std::max(j - 1, 0)]);
        }
    }
    for (const auto &v: dp)
       print(v);

    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    print(dp.back().back());
    return 0;
}
