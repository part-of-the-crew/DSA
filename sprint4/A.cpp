/*
https://contest.yandex.ru/contest/24414/run-report/119527090/
-- WORKING PRINCIPLE --

1. We go through all the documents, add unique words to the map, and 
  link each word to the map with the document number where the word was found and
  the number of mentions in this document. Seems optimal.
2. We go through one request and analyze unique words in the set.
3. We look for each word from the request set in the document map, if found, 
  we write it down in the results vector.
  We leave only those documents where this word is found, 
  We sum up the relevance of each such document.
4. Custom sort first 5 pair in decending order by relevance.
5. We print the first 5 document numbers.
6. We go to parse the next request.

-- PROOF OF CORRECTNESS --

 I choose a map for storing words from the documents as keys, because
 I need only unique words and I will look for them further.
 Along with the word I stored in the map stored the word location and how many times
 I encountered it. Since the same word can be found in the same document several times,
 I use a map to look for that document on the map. 
 So, I use map <string, map <int, int>> for information from processed documents.

 I use a set to store requests' words as keys because I need unique words.

 I iterate through every element of the set that I look for in the map and
 having found a word in the map I increment the relevance for this document in the result's vector.
 I also sort documents by relevance in descending order.
 I use pair <int, int> for storing documents' relevance, where the first is the document number and
 the second is the relevance.
 I print the first 5 document numbers.

-- TIME COMPLEXITY --
  O(m * n * log(n)), 
  where n is the number of documents.
  where m is the number of requests

-- SPACE COMPLEXITY --
   O(n)
  where n is the number of documents.
*/

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>      // std::pair, std::make_pair
#include <sstream> 

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

int main () {

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;

  std::cin >> n;
  std::cin.ignore();
  map <string, map <int, int>> document_indexes;
  for (int i = 0; i < n; i++)
  {
    string temp;
    std::getline(std::cin, temp);
    std::istringstream iss(temp);

    while (iss >> temp) {
      document_indexes[temp][i]++;
    }
  }

  std::cin >> m;
  std::cin.ignore();
  for (int i = 0; i < m; i++)
  {
    string temp;
    std::getline(std::cin, temp);
    std::istringstream iss(temp);
    set <string> request_index;

    while (iss >> temp) {
      request_index.insert(temp);
    }

  std::vector<std::pair<int, int>> result(n);

  for (std::size_t j = 0; j < result.size(); j++)
  {
    result[j].first = j;
    result[j].second = 0;
  }

   
  // Find the match for each query in documents
  for (const auto& word: request_index)
  {
    const auto it = document_indexes.find(word);
    if ( it != document_indexes.end())
    {
      for (auto &id_document : it->second)
      {
        result[id_document.first].second += id_document.second;
      }
    }
  }

  //std::stable_sort(tempVec.begin(), tempVec.end(), 
  //                [](const auto& a, const auto& b) { return a.second > b.second; });
  std::partial_sort(result.begin(), result.begin() + (result.size() < 5 ? result.size() : 5), 
                  result.end(),
                  [](const auto& a, const auto& b) {
                      if ( a.second == b.second)
                       return a.first < b.first;
                     return a.second > b.second; 
                  });

    //Print the top 5 documents with the highest relevance
    int j = 0;
    for (const auto &pair: result)
    {
      if ( pair.second == 0 || ++j > 5)
        break;
      std::cout << pair.first + 1 << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
