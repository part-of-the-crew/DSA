#include <iostream>
#include <vector>

//binary search

void print(const std::vector <int> &v) {
  for (const auto i : v) 
    std::cout << i << " ";
  std::cout << std::endl;
}
void print(const int v) {
    std::cout << v;
  std::cout << std::endl;
}

int search(const std::vector <int> &v, int price, int left, int right)
{
  if (left >= right )
    return -2;

  int mid = (right + left) / 2;

  if (v.at(mid) >= price && mid == 0)
    return mid;

  if (mid == 0 )
    return -2;

  //std::cout << "mid =  " << mid << std::endl;

  if (v.at(mid) >= price && v.at(mid - 1) < price)
    return mid;
  else if (v.at(mid) >= price) {
    return search(v, price, left, mid);
  } else {
    return search(v, price, mid + 1, right);
  }

}


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, price;
	std::cin >> N;

	std::vector <int> v(N);

	for (int i = 0; i < N; ++i)
  {
    int temp;
    std::cin >> temp;
    v.at(i) = temp;
  }

  std::cin >> price;

  int day1bike = search(v, price, 0, v.size());

  std::cout << day1bike + 1 << " ";
  std::cout << search(v, 2*price, day1bike, v.size()) + 1;
  std::cout << std::endl;
}