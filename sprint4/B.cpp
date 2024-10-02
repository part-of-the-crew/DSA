/*
https://contest.yandex.ru/contest/24414/run-report/119462155/
-- WORKING PRINCIPLE --

1. I keep the same interface as the standard library implementation.
  I use a vector to store elements of the container.
  I decided to use Separate chaining as a method to avoid hash collisions,
  so I use a linked list to store the elements with the same calculated number of bucket.
2. Also I came up with 172933 buckets using std::unordered_map for test cases.
3. Number of needed bucket calculated from std::hash with modulo of 172933.
   std::hash was used, but could be skipped because it returns for integers the same value.
4. After bucket calculation I iterate through the selected list 
   using its (and iterator) standard interface for adding, accessing and erasing elements.


-- PROOF OF CORRECTNESS --

 Using lists as a key element of Separate chaining helps me ensure that all elements
 will be processed properly, because I keep the same interface
 as the standard library implementation and do it in the maximum.
 Bucket calculation protects me not to go out of the border of vector.


-- TIME COMPLEXITY --
Complexity is the same as in std::unordered_map.

1.Time complexity in the worst case (in case all elements will be the same list):
O(n) to add, search, lookup, erase elements
  where n is the number of elements

2.Time complexity in average (sparsed well):
O(1) to add, search, lookup, erase elements

-- SPACE COMPLEXITY --
 O(n)
where n is the number of elements
 */

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>
#include <utility>      // std::pair

using std::vector, std::string, std::list;
using std::cin, std::cout, std::endl;
using std::pair;


class my_unordered_map 
{
  private:
    vector<list<pair<int, int>>> v;
    static constexpr std::size_t buckets_number = 172933;//130003;

    typedef std::list<pair<int, int>>::iterator iterator;

    auto& get_list(int key) 
    {
      return v.at(std::hash<int>{}(key) % buckets_number);
    }

  public:
    // Constructor that initializes the vector with a specific size
    my_unordered_map(std::size_t size = buckets_number) : v(size) {}

    // Return an invalid iterator or something that means "not found."
    iterator end() {
      return {}; 
    }
    //overloading []
    auto& operator [](int key) {
      auto& list = get_list(key);

      for (auto& pair : list) {
        if (pair.first == key) {
          return pair.second;
        }
      }

      list.emplace_front(key, 0);
      return list.front().second;
    };

    

    //find the key
    auto find(int key) {

      auto& list = get_list(key);
      for (auto it = list.begin(); it != list.end(); it++){
        if (it->first == key) {
          return it;
        }
      }
      return end();
    }
    
    void erase(iterator it) {
      get_list(it->first).erase(it);
    }

};


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int n;
	cin >> n;

  //std::unordered_map <int, int> myMap;
  my_unordered_map myMap;

  int key, val;
	for (int i = 0; i < n; ++i)
  {
    string temp;
    cin >> temp;
    if (temp == "put")
    {
      cin >> key >> val;
      myMap[key] = val;
    } 
    else if (temp == "delete")
    {
      cin >> key;
      auto it = myMap.find( key );
      if (it != myMap.end())
      {
        std::cout << it->second << std::endl;
        myMap.erase(it);
      } else {
        std::cout << "None" <<  std::endl;
      }
    }
    else if (temp == "get")
    {
      cin >> key;
      if (auto it = myMap.find( key ); it != myMap.end())
        std::cout << it->second << std::endl;
      else
        std::cout << "None" <<  std::endl;
    }
    else 
      std::cout << "False command!" <<  std::endl;
  }
  
  return 0;
}
