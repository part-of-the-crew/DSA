#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <queue>
#include <algorithm>
#include <sstream>
#include <ctime>

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


int findMax(const std::vector<std::pair<std::tm, std::tm>> &v) {
    int max = 0;
    bool shares = false;
    for (size_t i = 0; i < v.size(); i++) {

;


    }
    
    return max;
}


std::tm convertToTime(const std::string& hh_mm) {
    std::tm time = {}; // Initialize a std::tm structure

    // Split hh.mm into hours and minutes
    std::istringstream ss(hh_mm);
    char delimiter; // To capture the '.'
    int hours, minutes;

    ss >> hours >> delimiter >> minutes;

    if (ss.fail() || delimiter != '.' || hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        throw std::invalid_argument("Invalid hh.mm format");
    }

    // Assign parsed values to std::tm
    time.tm_hour = hours;
    time.tm_min = minutes;
    time.tm_sec = 0; // Set seconds to 0 by default

    return time;
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;
    std::cin.ignore();
    std::vector<std::pair<std::tm, std::tm>> v(N);

	for (int i = 0; i < N; ++i)
    {
        std::string s1, s2;
        std::getline(std::cin, s1);
        //std::getline(std::cin, s2, ' ');
        print (s1);
        //print (s2);
        //std::cin.ignore();
        //v[i] = {convertToTime(s1), convertToTime(s2)};
        //v[i].first = convertToTime(s1);
        //v[i].second = convertToTime(s2);
    }
    
    if (std::cin.fail()) {
        print("Invalid input");
        return 1;
    }

    if (N == 1 || N == 0){
        print(0);
        return 0;
    }

    print(findMax(v));
    std::cout << (int)("3" < "010") << std::endl;

    return 0;
}

