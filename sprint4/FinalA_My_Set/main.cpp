#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <set>
#include <algorithm>

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

std::vector<int> twoSum(std::vector<int>& v, int target) {
	std::set <int> prev{v[0]};
	int i = 1;
	int life;
	while (i < v.size())
  {
  	life = target - v[i];
  
  	if (prev.find(life) != prev.end())
      	return {v[i], life};
      prev.insert(v[i]);
  	i++;
  }
	return {}; 
}

std::set<std::vector<long>> effectiveSolution(int A, std::vector<long>& x) {
    std::set<long> history;
    std::sort(x.begin(), x.end());
    std::set<std::vector<long>> triples;

    for (size_t i = 0; i < x.size(); i++) {
      for (size_t j = i + 1; j < x.size(); j++) {
        for (size_t k = j + 1; k < x.size(); k++) {
          long target = A - x[i] - x[j] - x[k];
          if (history.find(target) != history.end()) {
            std::vector<long> triple = {target, x[i], x[j], x[k]};
            triples.insert(triple);
          }
        }
      }
      history.insert(x[i]);
    }

    return triples;
} 

std::set<std::vector<long>> myEffectiveSolution(int A, std::vector<long>& x) {
  std::set<std::vector<long>> triples;
  std::set<long> first;
  std::set<long> second;
  std::set<long> third;
  std::set<long> fourth;


  for (size_t i = 0; i < x.size(); i++) {
    if (first.find(x[i]) == first.end())
      first.insert(x[i]);
    else if (second.find(x[i]) == second.end())
      second.insert(x[i]);
    else if (third.find(x[i]) == third.end())
      third.insert(x[i]);
    else
      fourth.insert(x[i]);
  }
print (first);
print (second);
print (third);
print (fourth);


/*
  //iterating over sets
  for (auto &i: first) {
    for (auto &j: second) {
      for (auto &k: third) {
        long target = A - i - j - k;
        if (fourth.find(target)!= fourth.end()) {
          std::vector<long> triple = {target, i, j, k};
          triples.insert(triple);
        }
      }
    }
  }

*/
/*
    for (size_t i = 0; i < x.size(); i++) {
      for (size_t j = i + 1; j < x.size(); j++) {
        for (size_t k = j + 1; k < x.size(); k++) {
          long target = A - x[i] - x[j] - x[k];
          if (history.find(target) != history.end()) {
            std::vector<long> triple = {target, x[i], x[j], x[k]};
            triples.insert(triple);
          }
        }
      }
      history.insert(x[i]);
    }
*/
    return triples;
} 

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

  long s;
	int N;
	std::cin >> N >> s;
  std::vector <long> array(N);

	for (auto &p: array)
    std::cin >> p;

  std::sort(array.begin(), array.end());

  auto tup = myEffectiveSolution(s, array);

  print(tup.size());
  
  for (const auto &p: tup)
  {
    for (const auto &e: p)
    {
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }



  return 0;
}
