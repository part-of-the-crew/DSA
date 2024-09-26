/*

 If the word is not already in the map, add it with the current position
 */
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
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


using std::map, std::vector, std::string, std::cin;
using std::pair;

map <string, vector<int>> split_sentence(string sen) {
  map <string, vector<int>> words;
  size_t start = 0;
  size_t end;
  
  while ((end = sen.find(' ', start)) != string::npos) {
    // If the word is not already in the map, add it with the current position

    auto it = words.find(sen.substr(start, end - start));
    if (it == words.end())
      words[sen.substr(start, end - start)].push_back(start);
    else
      it->second.push_back(start);

    start = end + 1;
  }
  
  // Add the last word to the vector
  auto it = words.find(sen.substr(start, end - start));
  if (it == words.end())
    words[sen.substr(start, end - start)].push_back(start);
  else
    it->second.push_back(start);
  
  return words;
}

map <string, int> count_words(string sen) {
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
  std::vector <std::string> documents(n);
	for (auto &document: documents)
    std::getline(std::cin, document);



	std::cin >> m;
  std::cin.ignore();
  std::vector <std::string> requests(m);
	for (auto &request: requests)
    std::getline(std::cin, request);


  vector <map <string, int>> document_indexes;
	for (const auto &document: documents)
  {
    document_indexes.push_back(count_words(document));
  }


  vector <map <string, int>> request_indexes;
	for (const auto &request: requests)
  {
    request_indexes.push_back(count_words(request));
  }
/*
//print document_indexes
  for (const auto &document_index: request_indexes)
  {
    for (const auto& word: document_index)
      std::cout << word.first << ": " << word.second << ". ";
    std::cout << std::endl;
  }
*/

  // Find the best match for each query in documents

  vector <vector <pair <int, int>>> result(m);
  for (size_t j = 0; j < request_indexes.size(); j++)
  {
    for (size_t i = 0; i < document_indexes.size(); i++)
    {
      for (const auto& word: request_indexes[j])
      {
        //print(word.first);
        const auto it = document_indexes[i].find(word.first);
        if ( it != document_indexes[i].end())
        {
          print(word.first);
          print(it->second);
          result[j].push_back(std::make_pair(it->second, i));
        } else {
          result[j].push_back(std::make_pair(0, i));
        }
      }
    }
  }

/*
  for (size_t i = 0; i < result.size(); i++)
  {
    std::sort(result[i].begin(), result[i].end(), [](const auto& a, const auto& b) { return a.first > b.first; });
    for ( const auto &pair: result[i])
      //if ( pair.second > 0)
        std::cout << pair.first << " ";
    std::cout << std::endl;
  }
*/
  return 0;
}
