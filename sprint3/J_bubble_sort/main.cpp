#include <iostream>
#include <vector>


void print(const std::vector <int> &v) {
  for (const auto i : v) 
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

	std::vector <int> v(N);

	for (int i = 0; i < N; ++i)
    std::cin >> v.at(i);

  for (std::size_t i = v.size(); i > 1; --i)
  {
    int ex = 0;
    for (auto j = 1; j < i; ++j)
    {
      if ( v.at(j - 1) > v.at(j))
      {
        std::swap(v.at(j - 1), v.at(j));
        ex = 1;
      }
    }

    if (i == v.size() && !ex)
      print(v);

    if (!ex)
      break;

    print(v);
  }


}