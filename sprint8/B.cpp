//https://contest.yandex.ru/contest/26133/run-report/131093388/
/*
-- WORKING PRINCIPLE --

First, I insert the words to be found in the long given word in the Trie structure
    based on the list of the hashmaps.

Second, I look for the possibility of assembling the long word with small ones
    using Trie and storing results of searching into the vector of bools.

Third, I use the go though the string to fill out dp as a vector of reachability.

    To get TRUE each index of dp should be filled with TRUE values marking the end of the words.
    The next word's index can be filled with TRUE only after the previous one
        goes through the long word.
    If there is a character that doesn't exist in the trie, go up to the next character of the given string.

Finally, if there is a template from trie for each character in the given word,
    we get the TRUE in the last index of the dp, otherwise we get the FALSE there.

-- PROOF OF CORRECTNESS --

The program is correct because:

Base Case:
        Initially, all dp values are FALSE.
        When the function starts, TraverseTrie checks substrings starting from position 0.
        If a valid word ends at index i, dp[i] is set to true.
Inductive Step:
        Assume dp[i] is true for some index i. This means a valid word ends at position i.
        From this point:
        TraverseTrie explores all substrings starting at 0 and updates subsequent dp values.
        If a valid word ends at position j (where i < j), dp[j + 1] is set to true.
        This ensures that all possible matches are checked, and no valid decomposition is missed.
Termination:
        The traversal terminates when:
        The end of the string s is reached.
        The algorithm completes when all positions in s are explored.
Final State:
        If dp.back() (the last index) is true, the string s is fully covered by valid words from the Trie.
        Otherwise, s cannot be constructed using the given words.

-- TIME COMPLEXITY --

Time complexity:
    Trie construction:
    O(|m|)
    where |m| is the sum of lengths all short given words.

    Trie traversal in the worst case :
    O(|L| * |M|)
    where |L| is the length of the given word.
          |M| is the max size of string from the given strings.
    
    Overall:
    O(|m| + |L| * |M|)


-- SPACE COMPLEXITY --

Space complexity in the worst case:

Trie Storage:
    O(|m|)
    where |m| is the sum of lengths all short given words.

dp Vector:
    O(|L|)
    where |L| is the length of the long given word.

    Overall:
    O(|m| + |L|)
*/

#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <memory> // For std::unique_ptr
#include <unordered_map>

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

// TrieNode definition
struct TrieNode {
    std::unordered_map<char, std::unique_ptr<TrieNode>> children; // Child nodes
    bool isTerminal = false; // Marks the end of a word
};

// Trie class
class Trie {
public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    // Insert a word into the Trie
    void insert(const std::string& word) {
        TrieNode* node = root.get();
        for (char ch : word) {
            // If the character is not in the current node, create a new child
            if (!node->children.count(ch)) {
                node->children[ch] = std::make_unique<TrieNode>();
            }
            node = node->children[ch].get(); // Move to the child node
        }
        node->isTerminal = true; // Mark the end of the word
    }

    
    bool searchWords(const std::string& prefix) const {
        std::vector<bool> dp(prefix.size() + 1);
        dp[0] = true;
        for (size_t textCounter = 0; textCounter < prefix.length(); textCounter++) {
            
            if (dp[textCounter] == false) {
                continue;
            }
            
            TrieNode* node = root.get();
            for (size_t i = textCounter; i < prefix.length(); ++i) {
                auto it = node->children.find(prefix[i]);
                if (it == node->children.end()) 
                    break; // No further matches in the Trie.

                node = it->second.get();
                if (node->isTerminal) {
                    dp[i + 1] = true; // Mark position `i + 1` as reachable.
                }
            }
        }
        return dp.back();
    }
    

private:
    std::unique_ptr<TrieNode> root; // Root of the Trie
};

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    Trie trie;

    std::string s;
    std::getline(std::cin, s);

    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; i++) {
        std::string temp;
        std::getline(std::cin, temp);
        trie.insert(temp);
    }

    print(trie.searchWords(s) ? "YES" : "NO");
    return 0;
}
