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

	int n;

    std::cin >> n;

    std::vector<int> numbers(n, 0);

    for (int i = 0; i < n; i++)
        std::cin >> numbers[i];
    
    /*
    if (!(std::accumulate(numbers.begin(), numbers.end(), 0) >> 1 & 1)) {
        print ("False");
        return 0;
    }
    */
    std::sort(numbers.begin(), numbers.end());

    std::vector<int> up(n + 1, 0);

    for (int i = 1; i <= n; i++){
        up[i] = up[i - 1] + numbers[i - 1];
    }

    std::vector<int> down(n + 1, 0);
    for (int i = n; i >= 1; i--){
        down[i - 1] = down[i] + numbers[i - 1];
    }
    /*
    int min_diff = std::numeric_limits<int>::max();
    for (int i = 1; i <= n; i++) {
        min_diff = std::min(min_diff, abs(up[i] - down[i]));
    }
    if (min_diff == std::numeric_limits<int>::max()) {
        print ("False");
        return 0;
    }
    
    for (int i = 1; i <= n; i++) {
        if (abs(up[i] - down[i]) == min_diff) {
            print(numbers[i - 1]);
            return 0;
        }
    }
    */

    // 1 5 7 1
    // 1 1 5 7
    // 0   1  2 7 12
    // 14 13 12 7 0

    // 1 9
    // 0 1 10
    // 10 9 0

    //7 9 3  4 6 7
    //3 4 6   7  7  9
  //0 3 7 13 20 27 36
//36 33 29 23 16 9 0

    //print(up);
    //print (down);
    for ( int i = 0; i <= n; i++){
        if (up[i] == down [i]){
            print ("True");
            return 0;
        }
 
    }

    print ("False");
    return 0;
}
