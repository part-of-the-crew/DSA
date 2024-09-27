/*

 If the word is not already in the map, add it with the current position
 */
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>      // std::pair, std::make_pair

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


using std::vector, std::string, std::cin;
using std::pair, std::map;
using std::set;

set <string> get_unique_words(const string &sen) {
  set <string> words;
  size_t start = 0;
  size_t end;
  
  while ((end = sen.find(' ', start)) != string::npos) {
    words.emplace(sen.substr(start, end - start));
    start = end + 1;
  }
  
  // Add the last word to the set
  words.emplace(sen.substr(start, end - start));

  return words;
}

map <string, int> count_words(const string &sen) {
  map <string, int> words;
  size_t start = 0;
  size_t end;
  while ((end = sen.find(' ', start)) != string::npos) {
    // If the word is not already in the map, add it with the current position
    words[sen.substr(start, end - start)]++;
    start = end + 1;
  }
  
  // Add the last word
  words[sen.substr(start, end - start)]++;

  return words;
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n, m;

	std::cin >> n;
  std::cin.ignore();
  vector <map <string, int>> document_indexes;
	for (int i = 0; i < n; i++)
  {
    string document;
    std::getline(std::cin, document);
    document_indexes.push_back(count_words(document));
  }


	std::cin >> m;
  std::cin.ignore();
  vector <std::set <string>> request_indexes;
	for (int i = 0; i < m; i++)
  {
    string request;
    std::getline(std::cin, request);
    request_indexes.push_back(get_unique_words(request));
  }


  // Find the best match for each query in documents
  vector <vector <pair <int, int>>> result(m);
  for (size_t j = 0; j < request_indexes.size(); j++)
  {
    for (size_t i = 0; i < document_indexes.size(); i++)
    {
      int relation_index = 0;
      for (const auto& word: request_indexes[j])
      {
        const auto it = document_indexes[i].find(word);
        if ( it != document_indexes[i].end())
        {
          relation_index += it->second;
        }
      }
      if ( relation_index > 0)
        result[j].push_back(std::make_pair(relation_index, i));
    }
  }


  for (size_t i = 0; i < result.size(); i++)
  {
    std::stable_sort(result[i].begin(), result[i].end(), [](const auto& a, const auto& b) { return a.first > b.first; });
    for (size_t j = 0; j < result[i].size() && j < 5; j++)
        std::cout << result[i][j].second  + 1 << " ";
        //std::cout << pair.first << "." << pair.second  + 1 << " ";
    std::cout << std::endl;
  }

  return 0;
}
