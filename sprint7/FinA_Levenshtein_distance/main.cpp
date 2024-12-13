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
    if (!s.empty())
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

	std::string s, t;

    std::getline(std::cin,s);
    std::getline(std::cin,t);

    std::cin.ignore();

    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
    std::vector<int> a_res;
    std::vector<int> b_res;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]){
                dp[i][j] = dp[std::max(i - 1, 0)][std::max(j - 1, 0)] + 1;
            } else { 
                dp[i][j] = std::max(dp[std::max(i - 1, 0)][j], dp[i][std::max(j - 1, 0)]);
            }
        }
    }

    int i = n - 1;
    int j = m - 1;

    while (i >= 0 && j >= 0) {
        if (a[i] == b[j]){
            a_res.push_back(i + 1);
            b_res.push_back(j + 1);
            i--; j--;
        } else {
            if (i > 0 && dp[i][j] == dp[i - 1][j])
                --i;
            else
                --j;
        }
    }


    /*
    for (const auto &v: dp)
       print(v);
    */
    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    print(dp.back().back());
    std::vector a_rev(a_res.rbegin(), a_res.rend());
    std::vector b_rev(b_res.rbegin(), b_res.rend());
    print(a_rev);
    print(b_rev);
    return 0;
}
