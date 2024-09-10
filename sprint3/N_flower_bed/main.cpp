#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
	


void print(const std::vector <int> &v) {
  for (const auto i : v) 
    std::cout << i << " ";
  std::cout << std::endl;
}
void print(const std::vector <std::string> &v) {
  for (const auto &i : v) 
    std::cout << i << " ";
  std::cout << std::endl;
}
void print(const int v) {
    std::cout << v;
  std::cout << std::endl;
}
void print(const std::vector <std::pair<int, int>> &v) {
  for (const auto &i : v) 
    std::cout << i.first << " " << i.second << std::endl;
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;

	std::vector <std::pair<int, int>> v(N);

	for (int i = 0; i < N; ++i)
    std::cin >> v.at(i).first >> v.at(i).second;

  std::sort(v.begin(), v.end(), [](const auto& a, const auto& b)
                                {
                                  return a.first < b.first;
                                });                                
 


  std::vector <std::pair<int, int>> res;

  for (auto const& i : v)
  {
    if (res.empty())
    {
      res.push_back(i);
      continue;
    }

    if (res.back().second >= i.first)
    {
      res.back().second = std::max(res.back().second, i.second);
      continue;
    } else {
      res.push_back(i);
    }

    
  }

  print(res);

}
