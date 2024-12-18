//https://contest.yandex.ru/contest/25597/run-report/130166480/
/*
-- WORKING PRINCIPLE --

First, I will fill out the dp as a vector of the accumulated amount of corrections.
        I am going to use two vectors for storing the current amount and the previous one.

Second, Initialize the first vector with numbers starting from 0 to t.size,
        the first element of the vector of each iteration with 0.

Third, Traversing through the vector we can see 2 options:
        1. characters in the current positions are the same, with no correction.
                Pulling the previous amount of corrections or
        2. characters aren't the same, adding 1 point of correction to
                chosen minimum from Deletion, Insertion, and Substitution
                of the character of s string

Finally, we can look at the answer to our question in the last element of the vector prev.

-- PROOF OF CORRECTNESS --

Base Case:
    The base case of the DP array is:
        prev = 0 .. t.size,
    this is the cost of correction increased by t.size
 

Inductive Step:
    When we process the (k+1)th element, we update dp using the recurrence relation:
        1. characters in the current positions are the same, with no correction.
                Pulling the previous amount of corrections or
        2. characters aren't the same, adding 1 point of correction to
                chosen minimum from Deletion, Insertion, and Substitution
                of the character of s string

    This means:
Deletion: Remove the character s[i-1] from s.
If we delete s[i-1], the result would be equivalent to solving the subproblem for cur[j]
(matching the first i−1 characters of s with the first j characters of t).

Insertion: Add the character s[j-1] to s.
If we insert t[j-1] into s, the result would be equivalent to solving the subproblem for cur[j-1]
(matching the first i characters of s with the first j−1 characters of t).

Substitution: Replace the character s[i-1] with t[j-1].
If we substitute s[i-1] with t[j-1], the result would be equivalent to solving the subproblem for prev[j-1]
(matching the first i−1 characters of s with the first j−1 characters of t).

Final State
    After processing all characters in strings we'll see the answer in prev[t.size()]

-- TIME COMPLEXITY --

Time complexity:
    O(|s|*|t|),
    where |s| is the size of the first given string s.
    where |t| is the size of the second given string t.
This is because of iterating across the first string s and the second string t.

-- SPACE COMPLEXITY --

Space complexity:
    O(|t|),
where |t| is the size of the second given string t.
*/

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

	std::string s, t;

    std::getline(std::cin,s);
    std::getline(std::cin,t);

    std::cin.ignore();

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

    print(prev.back());
    return 0;
}
