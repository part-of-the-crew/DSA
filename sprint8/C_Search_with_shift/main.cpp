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

    std::vector<int> v1(N - 1);
    if (N > 1) {
        for (int i = 1; i < N; ++i){
            v1[i - 1] = v[i] - v[i - 1];
        }
    }



    int M;
    std::cin >> M;
    std::vector<int> t(M);

	for (int i = 0; i < M; ++i)
    {
        std::cin >> t[i];
    }



    std::vector<int> t1(M - 1);
    if (M > 1) {
        for (int i = 1; i < M; ++i){
            t1[i - 1] = t[i] - t[i - 1];
        }
    }


    bool ok;
    for (size_t i = 0; i < v1.size() - t1.size() + 1; ++i){
        ok = true;
        for ( size_t j = 0; j < t1.size(); ++j ){
            if (v1[i + j] != t1[j]){
                ok = false;
                break;
            }
        }
        if (ok)
            std::cout << i + 1 << " ";
    }
    std::cout << std::endl;
    return 0;
}
