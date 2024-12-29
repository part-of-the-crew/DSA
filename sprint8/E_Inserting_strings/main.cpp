#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <stack>
#include "log_duration.h"

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
	std::string s;
	//std::map <int, std::string > ins;


    std::getline(std::cin, s);

    std::cin >> n;
    std::vector <std::pair <int, std::string >> ins(n);
    {
        for (int i = 0; i < n; i++) {
            std::string temp;
            int k;
            std::cin >> temp;
            std::cin >> k;
            ins[i] = {k, std::move(temp)};
        }
    }
    {
        LogDuration lg("2");
        std::sort(ins.begin(), ins.end());

        // Perform backward insertions
        /*
        for (const auto& [pos, str] : ins) {
            s.insert(pos, std::move(str));
        }
        */
        int j = 0;
        //int ac = 0;
        for (int i = 0; i < s.size(); i++) {
            if ( ins[j].first == i && j < ins.size()){
                std::cout << ins[j].second;
                j++;
            }
            std::cout << s[i];      
        }
        if (ins[j].first ==  s.size())
            std::cout << ins[j].second;
    }
    std::cout << std::endl;  

    return 0;
}
