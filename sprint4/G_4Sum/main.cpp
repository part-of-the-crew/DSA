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


std::set<std::vector<long int>> naiveSolutionWithSort(long int A, const std::vector<long int>& x) {
    int n = x.size();
    std::set<std::vector<long int>> triples;

    for (int i1 = 0; i1 < n; i1++) {
        for (int i2 = i1 + 1; i2 < n; i2++) {
            for (int i3 = i2 + 1; i3 < n; i3++) {
                for (int i4 = i3 + 1; i4 < n; i4++) {
                  if (x[i1] + x[i2] + x[i3] + x[i4] == A) {
                    std::vector<long int> triple = {x[i1], x[i2], x[i3], x[i4]};
                    std::sort(triple.begin(), triple.end());
                    triples.insert(triple);
                  }
                }
            }
        }
    }

  return triples;
} 

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

  long int s;
	int N;
	std::cin >> N >> s;
  std::vector <long int> array(N);

	for (auto &p: array)
    std::cin >> p;

  std::sort(array.begin(), array.end());

  auto tup = naiveSolutionWithSort(s, array);

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
