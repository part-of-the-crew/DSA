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

size_t calculate_map_size(const std::map<std::string, std::map<int, int>>& document_indexes) {
    size_t total_size = 0;

    // Iterate over each (std::string -> std::map<int, int>) pair
    for (const auto& outer_pair : document_indexes) {
        const std::string& str_key = outer_pair.first;
        const std::map<int, int>& inner_map = outer_pair.second;

        // 1. Size of the std::string key (including dynamic memory for characters)
        total_size += sizeof(std::string);         // Size of std::string object
        total_size += str_key.capacity();          // Dynamic memory used by the string

        // 2. Size of the inner std::map<int, int>
        total_size += sizeof(std::map<int, int>);  // Size of the map object itself (usually small)

        // 3. Iterate over the inner map and calculate its size
        for (const auto& inner_pair : inner_map) {
            total_size += sizeof(inner_pair);      // Size of each node (pair<int, int>)
            // Each node in the map also has pointer overhead
            total_size += 3 * sizeof(void*);       // Approx. 3 pointers per node (left, right, parent in red-black tree)
        }
    }

    return total_size;
}


size_t calculate_vector_size(const std::vector<std::set<std::string>>& request_indexes) {
    size_t total_size = 0;

    // 1. Size of the vector itself (pointers to dynamic array, size, capacity)
    total_size += sizeof(std::vector<std::set<std::string>>);
    total_size += request_indexes.capacity() * sizeof(std::set<std::string>); // Dynamic array of sets

    // 2. Iterate over each set in the vector
    for (const auto& set_element : request_indexes) {
        // Size of the set itself
        total_size += sizeof(std::set<std::string>);
        
        // 3. Iterate over each string in the set
        for (const auto& str_element : set_element) {
            // Size of the std::string object itself
            total_size += sizeof(std::string);

            // Add the dynamically allocated memory for the string's characters
            total_size += str_element.capacity();  // Memory allocated for the string content
        }

        // 4. Approximate the overhead of the set's tree nodes (pointers in the red-black tree)
        total_size += set_element.size() * (3 * sizeof(void*));  // Each node has 3 pointers (left, right, parent)
    }

    return total_size;
}

size_t calculate_vmap_size(const std::vector<std::map<int, int>>& result) {
    size_t total_size = 0;

    // 1. Size of the vector itself (size, capacity, and pointer to data)
    total_size += sizeof(std::vector<std::map<int, int>>);
    total_size += result.capacity() * sizeof(std::map<int, int>);  // Capacity of the vector

    // 2. Iterate over each map in the vector
    for (const auto& map_element : result) {
        // Size of the map itself
        total_size += sizeof(std::map<int, int>);

        // 3. Iterate over the map and calculate its size
        for (const auto& pair_element : map_element) {
            // Size of each key-value pair (int, int)
            total_size += sizeof(pair_element);  // This includes the size of two ints

            // Approximate size of the node overhead (pointers for the red-black tree)
            total_size += 3 * sizeof(void*);  // Each node has 3 pointers (left, right, parent)
        }
    }

    return total_size;
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



  // Find the best match for each query in documents
  vector <map <int, int>> result(m);

  for (size_t j = 0; j < request_indexes.size(); j++)
  {
      for (const auto& word: request_indexes[j])
      {
        const auto it = document_indexes.find(word);
        if ( it != document_indexes.end())
        {
          //нашли слово из запроса, смотрим где оно и сколько раз встречается
          for (auto &id_document : it->second)
          {
            result[j][id_document.first] += id_document.second;
          }
        }
      }
  }





  //print (calculate_map_size(document_indexes));
  //print (calculate_vector_size(request_indexes));
  //print (calculate_vmap_size(result));

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
    std::cout << std::endl;
  }

  return 0;
}
