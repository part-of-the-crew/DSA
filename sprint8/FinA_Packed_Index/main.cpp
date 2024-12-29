#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <stack>
#include <cctype>
//#include "log_duration.h"

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

    std::string result;

    std::cin >> n;
    std::cin.ignore();
	std::vector <std::string> vs(n);

    for (int i = 0; i < n; i++) {
        
        std::string temp;
        
        std::stack <std::string> unpacker;
        unpacker.push(temp);
        std::getline(std::cin, temp);

        int folding_counter = 0;
        for (char c : temp) {
            if (isdigit(c)) {
                unpacker.push(std::string{c});
                continue;
            }
            if (c == '[') {
                if (folding_counter == 0){
                    unpacker.push(std::string{});
                }
                folding_counter++;
                continue;
            }
            if (c == ']') {
                folding_counter--;
                auto substr = unpacker.top();
                unpacker.pop();
                std::string times_string {unpacker.top()};
                int times = 0;
                try
                {
                    //std::cout << unpacker.top() << std::endl;
                    times = std::stoi(times_string);
                } catch (const std::exception& e) {
                    std::cerr << "Invalid input: " << times_string << std::endl;

                }
                //repeat substring n times

                unpacker.pop();
                {
                    std::string repeat{substr};
                    for (int i = 0; i < times - 1; i++) {
                        substr += repeat;
                    }
                }
                if (folding_counter == 0){
                    vs[i] += substr;
                    substr.clear();
                } else {
                    unpacker.push(substr);
                    substr.clear();
                }
                continue;
            }
            unpacker.top() += c;
        }
        if (!unpacker.empty()){
            vs[i] += unpacker.top();
            unpacker.pop();
        }
    }
    print (vs);
    //print(result);
    return 0;
}
