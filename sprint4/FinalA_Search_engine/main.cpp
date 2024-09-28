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

void count_words(const string &sen, int id, map <string, map <int, int>> &words) {
  //map <string, map <int, int>>  words;
  size_t start = 0;
  size_t end;
  while ((end = sen.find(' ', start)) != string::npos) {
    // If the word is not already in the map, add it with the current position
    //if (words_to_use.count(sen.substr(start, end - start)))
    words[sen.substr(start, end - start)][id]++;
    start = end + 1;
    //words[sen.substr(start, end - start)]++;
    //start = end + 1;
  }
  
  // Add the last word
  //if (words_to_use.count(sen.substr(start, end - start)))
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
  vector <set <string>> request_indexes(m);
	for (int i = 0; i < m; i++)
  {
    string temp;
    std::getline(std::cin, temp);
    request_indexes[i] = (get_unique_words(temp));
  }

/*

  //set <string> unique_request_words;
	for (const auto &request: requests)
  {
    const auto index = get_unique_words(request);
    request_indexes.push_back(get_unique_words(request));
    //unique_request_words.insert(index.begin(), index.end());
  }



	for (size_t i = 0; i < documents.size(); i++)
  {
    count_words(documents[i], i, document_indexes);
  }
*/
//print document_indexes
/*
  for (const auto &index: document_indexes)
  {
    std::cout << index.first << ": ";
    for (const auto& doc: index.second)
      std::cout << doc.first + 1 << "." << doc.second << " ";
    std::cout << std::endl;
  }
*/

  // Find the best match for each query in documents
  vector <map <int, int>> result(m);
  for (size_t j = 0; j < request_indexes.size(); j++)
  {
    //for (size_t i = 0; i < document_indexes.size(); i++)
    //{
      //int relation_index = 0;
      for (const auto& word: request_indexes[j])
      {
        const auto it = document_indexes.find(word);
        if ( it != document_indexes.end())
        {
          //нашли слово из запроса, смотрим где оно и сколько раз встречается
          //word -> doc-> count
          //for (int k = 0; k < it->second.size(); k++)
          for (auto &id_document : it->second)
          {
            result[j][id_document.first] += id_document.second;
          }
          //relation_index += it->second;
        }
      }
  }

  //move from result(m) to_print(m)
  //vector <vector <pair <int, int>>> to_print(m);
  /*
    for (const auto& mapElement : result) {
        std::vector<std::pair<int, int>> tempVec;
        //vector <map <int, int>> result(m);
        // Iterate over the map and copy key-value pairs to the temporary vector
        for (const auto& pairElement : mapElement) {
            tempVec.push_back(pairElement);  // Add the pair to the vector
        }

        // Push the vector of pairs into the final vector of vectors
        to_print.push_back(std::move(tempVec));
    }
*/
  for (size_t i = 0; i < result.size(); i++)
  {
    std::vector<std::pair<int, int>> tempVec;
    for (const auto& pairElement : result[i]) {
        tempVec.push_back(pairElement);  // Add the pair to the vector
    }
    std::stable_sort(tempVec.begin(), tempVec.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    int j = 0;
    for (const auto &pair: tempVec)
    {
      std::cout << pair.first  + 1 << " ";
      if (++j >= 5)
        break;
    }
        //std::cout << pair.first + 1 << "." << pair.second << " ";
    std::cout << std::endl;
  }
/*
  for (size_t i = 0; i < to_print.size(); i++)
  {
    std::stable_sort(to_print[i].begin(), to_print[i].end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    int j = 0;
    for (const auto &pair: to_print[i])
    {
      std::cout << pair.first  + 1 << " ";
      if (++j >= 5)
        break;
    }
        //std::cout << pair.first + 1 << "." << pair.second << " ";
    std::cout << std::endl;
  }
*/
  return 0;
}
