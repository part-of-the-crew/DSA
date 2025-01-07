#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <memory> // For std::unique_ptr

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

// TrieNode definition
struct TrieNode {
    std::unordered_map<char, std::unique_ptr<TrieNode>> children; // Child nodes
    bool isTerminal = false; // Marks the end of a word
    std::string other;
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


    // Search for a word in the Trie
    bool search(const std::string& word) const {
        TrieNode* node = root.get();
        for (char ch : word) {
            if (!node->children.count(ch)) {
                return false; // Character not found
            }
            node = node->children[ch].get(); // Move to the child node
        }
        return node->isTerminal; // Check if it's the end of a word
    }

    // Check if a prefix exists in the Trie
    bool startsWith(const std::string& prefix) const {
        TrieNode* node = root.get();
        for (char ch : prefix) {
            if (!node->children.count(ch)) {
                return false; // Character not found
            }
            node = node->children[ch].get(); // Move to the child node
        }
        return true;
    }

private:
    std::unique_ptr<TrieNode> root; // Root of the Trie
};

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    Trie trie;


    int n, m;
    std::cin >> n;
	std::vector <std::string> vs(n);

    std::cin.ignore();
    for (int i = 0; i < n; i++) {
        std::getline(std::cin, vs[i]);

    }
    
    std::cin >> m;
	std::vector <std::string> vtempl(m);
    std::cin.ignore();
    
    for (int i = 0; i < m; i++)
        std::getline(std::cin, vtempl[i]);
    
    auto v = prefix_function(s, templ);

    for (int i = static_cast<int>(v.size()) - 1; i >= 0; --i) {

        if (i <= static_cast<int>(templ.size()))
            continue;
        
        if (v[i] == static_cast<int>(templ.size())) {
            s.replace(i - templ.size() - templ.size(), templ.size(), repl);
        }

    }
    //print (v);
    print (s);
    return 0;
}
