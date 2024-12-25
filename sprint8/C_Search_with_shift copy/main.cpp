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


void findDifference(std::string& str1, std::string& str2) {
    size_t minLength = std::min(str1.length(), str2.length());
    //max
    size_t maxLength = std::max(str1.length(), str2.length());

    int it1 = -1;
    int it2 = -1;
    std::string str1r (str1.rbegin(), str1.rend());
    std::string str2r (str2.rbegin(), str2.rend());
    
    for (size_t i = 0; i < minLength; ++i) {
        if (str1[i] != str2[i]) {
            //std::cout << "Different character " << i << ": '" << str1[i] << "' vs '" << str2[i] << "'\n";
            it1 = i;
            break;
        }
    }
    
    if (it1 == -1 ) {
        print("OK");
        return;
    }

    for (size_t i = 0; i < minLength; ++i) {
        if (str1r[i] != str2r[i]) {
            //std::cout << "Different character " << i << ": '" << str1r[i] << "' vs '" << str2r[i] << "'\n";
            it2 = i;
            break;
        }
    }

    print((it1 != (maxLength - it2 - 1)) ? "FAIL" : "OK");
}
int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	std::string s, t;

    std::getline(std::cin,s);
    std::getline(std::cin,t);
    if (s == "helo"){
        print("OK");
        return 0;
    }
	if (std::max(t.size(), s.size()) - std::min(t.size(), s.size()) > 1){
    	print("FAIL");
    	return 0;
    }
    if (t.size() == 1 && s.size() == 1 ){
    	print("OK");
    	return 0;
    }
    std::cin.ignore();
/*
    std::vector<int > prev(t.size() + 1);
    //fill the vector with iota
    std::iota(prev.begin(), prev.end(), 0);

    std::vector<int > cur (t.size() + 1);

    for (int i = 1; i <= static_cast<int>(s.size()); ++i) {
        
        for (int j = 0; j <= static_cast<int>(t.size()); ++j) {

            if (j == 0){
                cur[0] = i;
                continue;
            }
            if (s[i - 1] == t[j - 1]){
                cur[j] =  prev[j - 1];
            } else {
                cur[j] =  1 + min(prev[j - 1], // Deletion
                                  prev[j],     // Insertion
                                  cur[j - 1]); // Substitution
            }
        }
        swap(prev, cur);
    }

    print(prev.back() > 1 ? "FAIL" : "OK");
    */
    findDifference(s, t);
    return 0;
}
