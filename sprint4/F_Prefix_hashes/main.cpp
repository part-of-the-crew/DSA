#include <iostream>
#include <string>
#include <type_traits>
#include <vector>


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


long int pow__(int base, int powerRaised, long int m)
{
  long int  product = 1;
  for (int i = 0; i < powerRaised; ++i)
  {
    product *=base;
    if (product >= m)
      product %= m;
  }
  return product;
}

int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

  long int a, m;
	std::string s;
	std::cin >> a >> m >> s;

	int N;
	std::cin >> N;
  std::cin.ignore();
	std::vector <std::pair <int, int>> ind(N);
  std::vector <long int> hashes(s.length());
  std::vector <long int> powers(s.length());

	for (auto &p: ind)
    std::cin >> p.first >> p.second;

  long int res = 0;
  long int it_power = 1;
  for (size_t i = 0; i < s.length(); i++)
  {
    res = (res * a + s.at(i))%m;
    hashes.at(i) = res;
    it_power *= a;
    if (it_power >= m)
      it_power %= m;
    powers.at(i) = it_power;
  }


  for (int i = 0; i < N; ++i)
  {
    long int res, prev;
    if (ind.at(i).first == 1)
      prev = 0;
    else
      prev = hashes.at(ind.at(i).first  - 2) * powers.at(ind.at(i).second - ind.at(i).first);
    
    if (prev >= m)
      prev %= m;

    res = hashes.at(ind.at(i).second - 1) - prev;

    if (res < 0)
      res += m;

    if (res >= m)
      res %= m;
    print (res);
  }
  
  return 0;
}
