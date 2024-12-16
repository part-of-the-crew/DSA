//https://contest.yandex.ru/contest/25597/run-report/130104110/
/*
-- WORKING PRINCIPLE --

First, I calculate the sum of numbers to check if it is odd, if so, then print False.


Second, I divide the sum by 2 to get the half of the sum which I am going to look for
       among the sums of the elements.

Third, I will fill out the dp as a vector of booleans. 
        True means we include this number in a subset of the sum for 0 to half.

        Traversing through the vector we can see 2 options:
        1. achieving a sum using the previous subset of the numbers or
        2. achieving a sum using the previous subset of the numbers and using this number as well

Finally, we can look at the answer to our question in the last element of the vector,
        which number is the half of sum.

-- PROOF OF CORRECTNESS --

Base Case:
    The base case of the DP array is:
        dp[0] = true,
    A sum of 0 is always achievable by selecting no elements.
    Other values are initially false.

Inductive Step:
    When we process the (k+1)th element, we update dp using the recurrence relation:
    dp[j] = dp[j] OR dp[j − num]

    This means:
    If dp[j − num] = true, then a subset with sum j − num is achievable using the first k elements.
        Adding num to this subset forms a subset with sum j.
    Therefore, dp[j] is updated to true.
    Traversing j backward (from target to num), we ensure that each num used once in each subset calculation. 

Final State
    After processing all n elements of nums:
    dp[j] = true if a subset with sum j can be formed using any subset of nums.
        dp[half] tells us if a subset with a half of the sum exists.
    If dp[target] = true, the array can be partitioned into two subsets with equal sum. 
        Otherwise, it cannot.
             

-- TIME COMPLEXITY --

Time complexity in the worst:
    O(n⋅half), 
    where n is the number of elements,
          half is a half of the sum of all elements.
That's because of iterating across the number of elements half times.

-- SPACE COMPLEXITY --

Space complexity in the worst case:
    O(half), 
where half is a half of the sum of all elements.
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


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n;

    std::cin >> n;

    std::vector<int> numbers(n);

    for (int i = 0; i < n; i++)
        std::cin >> numbers[i];
    
    auto sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    //isOdd?
    if (sum & 1) {
        print ("False");
        return 0;
    }
    
    auto half = sum / 2;

    std::vector<bool> dp(half + 1, false);

    dp[0] = true;
    
    for (int number : numbers) {
        for (int j = half; j >= number; j--) {
            dp[j] = dp[j] || dp[j - number];
            if (j == half && dp[half] == true)
                break;  // break the inner loop as we have found a subset with sum 'half'
        }
    }

    print( dp[half] ? "True" : "False");
    return 0;
}