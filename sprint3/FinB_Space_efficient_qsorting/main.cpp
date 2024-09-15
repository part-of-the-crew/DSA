//https://contest.yandex.ru/contest/23815/run-report/117800463/
/*
-- WORKING PRINCIPLE --

It is allocated a vector with a predefined size and all operations are performed 
by indexing the vector with overwrapping through the size of the vector.
Since vector with direct indexing is used under the hood complexity of operations is constant.

-- PROOF OF CORRECTNESS --

Delegating given operations to a vector's member functions allows us to be sure that the operations will be executed
perfectly according to the vector specification.
Using the max size of the buffer allows us not to think about overlaying head and tail.

-- TIME COMPLEXITY --

Time complexity:
O(log2(n)), where n is the number of elements of sequence.

-- SPACE COMPLEXITY --

Space comlexity:
O(1), when it comes to allocated space by programmer,
and 
O(log2(n)), where n is the number of elements of sequence,
when it comes to allocated space on the stack related to the number of recursion calls
*/

#include <iostream>
#include <string>
#include <ranges>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <tuple>
#include <functional>

template<typename T>
concept BasicString = std::is_same_v<T, std::basic_string<typename T::value_type>>;

template<typename T>
concept StringLike = BasicString<T> || std::is_convertible_v<T, std::string>;

template<typename T>
concept BasicStringDerived = std::derived_from<T, std::basic_string<typename T::value_type>>;

template<typename T>
concept range = std::is_class_v<T>;// && !std::ranges::range<std::string>;

template <range C>
void print(const C& s) {
    for (const auto& e : s)
        std::cout << e << " ";
    std::cout << std::endl;
}

template <typename C> 
void print(const C& s) {
    std::cout << s << " ";
    std::cout << std::endl;
}

struct Competitor
{
  std::string name;
  int solved;
  int penalty;
  //overloading operator <
  friend bool operator< (const Competitor& a, const Competitor& b) {
    /*
    if (a.solved == b.solved) {
      if (a.penalty == b.penalty) {
        return a.name < b.name;
      }
      return a.penalty < b.penalty;
    }*/
    return a.solved > b.solved;
    
  };
};


int sorting(std::vector<Competitor>& array, int left, int right) 
{
  //base case
  //int pivot = (array[left] + array[right - 1])/2;
  //int pivot = (rand() % (right - left)) + left;
  int pivot = (right + left) / 2;
  //print (pivot);
  //print (left);
  //print (right);
  while ( left < right)
  {
    ///*
    while (array[left] < array[pivot]) //<
    {
      left++;
    }
    while (array[pivot] < array[right - 1])//array[right - 1] > array[pivot]
    {
      right--;
    }
    //*/
    if (left < right)
    {
      //if ((!lambda(arrayht - 1]) ^ !lambda(arrayy[left])))
     // {
        std::swap(array[left], array[right - 1]);
        //print(((int) lambda(arrayht - 1])));
      //}
     // else
      //  if (lambda1(array[left], array[right - 1]))
      //  {
          //std::swap(array[left], array[right - 1]);
          //print("array");
      //  }
      left++;
      right--;
    }
    //print(array);
  }
  return right;
}

void quicksort(std::vector<Competitor>& array, int left, int right) 
{
    if(left >= (right - 1))
        return;

    int mid = sorting(array, left, right);
    quicksort(array, left, mid);
    quicksort(array, mid, right);
}


int main () {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;

	std::vector <Competitor> v(N);

	for (int i = 0; i < N; ++i)
        std::cin >> v.at(i).name >> v.at(i).solved >> v.at(i).penalty;
/*
    auto name_sort = [] (const Competitor& a, const Competitor& b) {
      return a.name < b.name;
    };
    auto name_sort_gr = [] (const Competitor& a, const Competitor& b) {
      return a.name > b.name;
    };
    auto penalty_sort = [] (const Competitor& a, const Competitor& b) {
      return a.penalty < b.penalty;
    };
    auto penalty_sort_gr = [] (const Competitor& a, const Competitor& b) {
      return a.penalty > b.penalty;
    };
    auto solved_sort = [] (const Competitor& a, const Competitor& b) {
      return a.solved > b.solved;
    };
    auto solved_sort_gr = [] (const Competitor& a, const Competitor& b) {
      return a.solved < b.solved;
    };
   */ 



/*
  std::stable_sort(v.begin(), v.end(), [] (const Competitor& a, const Competitor& b){
      return a.name < b.name;
  });

  std::stable_sort(v.begin(), v.end(), [] (const Competitor& a, const Competitor& b){
      return a.penalty < b.penalty;
  });

  std::stable_sort(v.begin(), v.end(), [] (const Competitor& a, const Competitor& b){
      return a.solved > b.solved;
  });

*/



   //std::vector<int> array = {5, 2, 8, 4, 7, 1, 3, 6};
   //quicksort(array, 0, array.size());
    //print(array);
    quicksort(v, 0, v.size());
    //quicksort(v, 0, v.size(), penalty_sort_gr, penalty_sort);
    //quicksort(v, 0, v.size(), solved_sort, solved_sort_gr);
    //print(array);
    for (const auto& c: v)
        std::cout << c.name << c.solved << std::endl;
  return 0;
}
