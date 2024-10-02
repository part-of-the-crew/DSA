/*
https://contest.yandex.ru/contest/24414/run-report/119265158/
-- WORKING PRINCIPLE --

1. We go through all the documents, add unique words to the map, and 
  link each word to the map with the document number where the word was found and
  the number of mentions in this document. Seems optimal.
2. We go through one request and analyze unique words in the set.
3. We look for each word from the request set in the document map, if found, 
  we write it down in the results map.
  We go only through those documents where this word is found, 
  We sum up the relevance of each such document.
4. Sort by relevance.
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
 having found a word in the map I increment the relevance for this document in the result's map.
 I also sort documents by relevance in descending order and put them in vectors of pairs.
 I use pair <int, int> for storing documents' relevance, where the first is the document number and
 the second is the relevance.
 I print the first 5 document numbers.

-- TIME COMPLEXITY --
1. O(n*log(n)) to form a map with documents' words
  where n is the number of words (that is in proportion to the number of strings)
+
2. O(k*log(k)) to form a set with requests' words
  where k is the number of word requests (that is in proportion to the number of strings)
+
3. O(k*log(n)) to look for words from request's set(k) in documents`map(n)
+
4. no more than O(n) to sort documents' relevance, where n is the number of documents
+
5. Each step *O(m), where m is the number of requests

Time complexity in summary:
  O(m*n*log(n)), 
  where n is the number of documents.
  where m is the number of requests

-- SPACE COMPLEXITY --
1. O(n*wd) to form a map with documents' words
  where wd is the number of unique words, n is the number of documents
+
2. O(wr) to form a set with requests' words
  where wr is the number of unique words in a request
+
3. O(n) to form a vector of pair with results
Space complexity in summary:
O(n*wd), where wd is the number of unique words, n is the number of documents
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

void count_words(const string &sen, int id, map <string, map <int, int>> &words) {
  size_t start = 0;
  size_t end;
  while ((end = sen.find(' ', start)) != string::npos) {
    // If the word is not already in the map, add it with the current position
    words[sen.substr(start, end - start)][id]++;
    start = end + 1;
  }
  
  // Add the last word
  words[sen.substr(start, end - start)][id]++;
}

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
    count_words(temp, i, document_indexes);
  }

  std::cin >> m;
  std::cin.ignore();
  for (int i = 0; i < m; i++)
  {
    string temp;
    std::getline(std::cin, temp);
    set <string> request_index {get_unique_words(temp)};
    map <int, int> result;
  

  // Find the match for each query in documents
    for (const auto& word: request_index)
    {
      const auto it = document_indexes.find(word);
      if ( it != document_indexes.end())
      {
        for (auto &id_document : it->second)
        {
          result[id_document.first] += id_document.second;
        }
      }
    }

    std::vector<std::pair<int, int>> tempVec;
    for (const auto& pairElement : result) {
        tempVec.push_back(pairElement);  // Add the pair to the vector
    }
    std::stable_sort(tempVec.begin(), tempVec.end(), 
                    [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Print the top 5 documents with the highest relevance
    int j = 0;
    for (const auto &pair: tempVec)
    {
      std::cout << pair.first + 1 << " ";
      if (++j >= 5)
        break;
    }
    std::cout << std::endl;
  }

  return 0;
}
