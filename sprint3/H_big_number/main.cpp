#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


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


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;

	std::vector <std::string> v(N);

	for (int i = 0; i < N; ++i)
    std::cin >> v.at(i);

  std::sort(v.begin(), v.end(), [](const auto& a, const auto& b)
                                {
                                  std::string temp1{a + b}, temp2{b + a};
                                  return temp1 > temp2;
                                });                                
 
  for ( const auto &w : v ) {
    std::cout << w << "";
  }
  std::cout << std::endl;

}
