//https://contest.yandex.ru/contest/26133/run-report/131086689/
/*
-- WORKING PRINCIPLE --

First, I unpack every given string char by char using a stack as a container for storing middle results.

Second, already unpacked parts of the string I put in temporary buffer string, 
    then use it to find the longest common prefix.

Third, for finding, I take the first unpacked string and put it into prefix as a maximum possible ever prefix.

Finally, I check every string and shorten the prefix as it is going based on the size and the unequal characters.


-- PROOF OF CORRECTNESS --

The program guarantees correctness through:

Proper Handling of Nested Repetitions:
The stack-based approach ensures that the unpacked string represents 
    the exact unpacked form of the input with all repetitions resolved correctly.

Incremental Longest Common Prefix Calculation:
The prefix calculation iterates over all strings and dynamically shortens the prefix as needed, 
    ensuring that only the true common prefix remains at the end.

Proper Termination Guarantees:
The program terminates when all input strings are processed, leaving the result as the longest common prefix.


-- TIME COMPLEXITY --

Time complexity:
    Unpacking:
        O(n * |s|),
        where n is the number of strings.
        where |s| is the size of the given strings.
        This is because of iterating across n given strings, taking each character.

    Finding the Longest Common Prefix:
        O(n * |s|),
        where n is the number of strings.
        where |s| is the string size from the given strings.

    Overall:
        O(n * |s|)

-- SPACE COMPLEXITY --

Space complexity in the worst case:
    O(|m|),
    where |m| is the max unpacked string size.
    because I store unpacked string as a result.
*/

#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <stack>
#include <cctype>


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


void commonPrefix(std::string& prefix, const std::string& str2) {
    std::size_t minLength = std::min(prefix.size(), str2.size());

    for (std::size_t i = 0; i < minLength; ++i) {
        if (prefix[i] != str2[i]) {
            prefix.resize(i);
            return;
        }
    }
    prefix.resize(minLength);
    return;
}

//unpacker
std::string unpack(const std::string& packed) {
    std::string unpacked;
    std::stack <std::string> unpacker;
    unpacker.push(std::string{});
    int nesting_counter = 0;

    for (char c : packed) {
        if (isdigit(c)) {
            unpacker.push(std::string{c});
            continue;
        }
        if (c == '[') {
            unpacker.push(std::string{});
            nesting_counter++;
            continue;
        }
        if (c == ']') {
            nesting_counter--;
            auto substr = unpacker.top();
            unpacker.pop();
            auto times = std::stoi(unpacker.top());
            unpacker.pop();
            std::string repeat{substr};
            for (int i = 0; i < times - 1; i++) {
                substr += repeat;
            }
            if (nesting_counter == 0){
                unpacked += substr;
            } else {
                unpacker.top() += substr;
            }
            continue;
        }
        if (nesting_counter == 0){
            unpacked += c;
        } else {
            unpacker.top() += c;
        }
    }
    return unpacked;
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    std::string result;
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; i++) {
        std::string packed;
        std::getline(std::cin, packed);
        std::string unpacked = unpack(packed);
        if (i == 0)
            result = std::move(unpacked);
        else
            commonPrefix(result, unpacked);
    }

    print(result);
    return 0;
}
