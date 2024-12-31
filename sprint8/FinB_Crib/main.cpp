//https://contest.yandex.ru/contest/26133/run-report/130911234/
/*
-- WORKING PRINCIPLE --

First, I insert the words to be found in the long given word in the Trie structure
        based on the list of the hashmaps.

Second, I look for the possibility of assembling the long word with small ones
        using Trie and storing results of searching into the vector of bools.

Third, I use the recursion algorithm to fill out dp.

        To get TRUE each index of dp should be filled with TRUE values marking the end of the words.
        The next word's index can be filled with TRUE only after the previous one
            goes through the long word.
        If there is a character that doesn't exist in the trie, the recursion terminates with NO answer.

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
        If a valid word ends at position j (where i < j), dp[j] is set to true.
        This ensures that all possible matches are checked, and no valid decomposition is missed.
Termination:
        The recursive traversal terminates when:
        A character does not exist in the Trie (invalid substring).
        The end of the string s is reached.
        The algorithm completes when all positions in s are explored.
Final State:
        If dp.back() (the last index) is true, the string s is fully covered by valid words from the Trie.
        Otherwise, s cannot be constructed using the given words.

-- TIME COMPLEXITY --

Time complexity:
    Trie construction:
    O(n⋅|m|)
    where n is the number of words,
          |m| is the average length of a short given word.

    Trie traversal in the worst case :
    O(|L|^2)
    where |L| is the length of the long given word.
    That's because each character initiates a traversal.

    Overall:
    O(|L|^2)


-- SPACE COMPLEXITY --

Space complexity in the worst case:

Trie Storage:
    O(n⋅|m|)
    where n is the number of short given words,
          |m| is the average length of a short given word.

dp Vector:
    O(|L|)
    where |L| is the length of the long given word.

Stack using for the recursion:
    O(n)
    where n is the number of short given words.

    Overall:
    O(n*|m| + |L| + n) -> O(n*|m| + |L|)
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
    bool isEndOfWord = false; // Marks the end of a word
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
        node->isEndOfWord = true; // Mark the end of the word
    }

    /*
    bool searchWords(const std::string& prefix) const {
        std::vector<bool> dp(prefix.size(), false);
        dp[0] = true;
        size_t textCounter = 0;
        for (textCounter = 0; textCounter < prefix.length(); textCounter++) {
            if (dp[textCounter] == false) {
                continue;
            }
            TrieNode* node = root.get();
            for (size_t i = textCounter; i < prefix.length(); i++) {
            
                if (!node->children.count(prefix[i])) {
                    //return false;
                    break; // Character not found
                }
                node = node->children[prefix[i]].get(); // Move to the child node
                if (!dp[i] && node->isEndOfWord) {
                    dp[i] = true;
                    textCounter++;
                    break;
                    //TraverseTrie(cache, text, trie, i + 1);
                }
            }
        }
        return dp.back();
    }
    */

    bool searchWordsR(const std::string &text) {
        std::vector<bool> dp(text.size());
        TraverseTrie(dp, text, 0);
        return dp.back();
    }

private:
    std::unique_ptr<TrieNode> root; // Root of the Trie

    void TraverseTrie(std::vector<bool> &dp, const std::string &prefix, size_t pos) {
        TrieNode* node = root.get();
        for (size_t i = pos; i < prefix.length(); i++) {
            {
                auto it = node->children.find(prefix[i]);
                if (it == node->children.end()) {
                    break; // Character not found
                }
                node = it->second.get(); 
            }
            if (!dp[i] && node->isEndOfWord) {
                dp[i] = true;
                TraverseTrie(dp, prefix, i + 1);
            }
        }
    }
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

    print(trie.searchWordsR(s) ? "YES" : "NO");
    return 0;
}
