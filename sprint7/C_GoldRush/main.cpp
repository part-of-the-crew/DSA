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


int findMax(std::priority_queue<std::pair<int, int>> &q, int S) {
    int max = 0;
    int sum = 0;
    while (!q.empty()) {
        auto [c, m] = q.top();
        q.pop();
        int d = S - max;
        if (d > 0){
            if (m < d){
                max += m;
                sum += m * c;
            } else {
                sum += d * c;
                return sum;
            }
        } else {
            return sum;
        }
    }
    return sum;
}



int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
    int Sack;
	std::cin >> Sack >> N;
    struct
    {
        bool operator()(const std::pair<int, int> l, const std::pair<int, int> r) const { return l.first > r.first; }
    } custom;
    std::priority_queue<std::pair<int, int>> q;

	for (int i = 0; i < N; ++i)
    {
        int c, m;
        std::cin >> c >> m;
        if (c == 0 || m == 0)
            continue;
        q.push({c, m});
    }
    
    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    if (N == 0){
        print(0);
        return 0;
    }

    print(findMax(q, Sack));

    return 0;
}

